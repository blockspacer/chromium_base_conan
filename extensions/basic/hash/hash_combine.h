#pragma once

#include <cstdint>
#include <cstring>
#include <limits>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

#include <base/bit_cast.h>
#include <base/strings/string_piece.h>

#include <basic/hash/spooky_hash_v2.h>
#include <basic/hash/twang_hash.h>
#include <basic/hash/jenkins_hash.h>
#include <basic/portability/c_portability.h>
#include <basic/portability/traits.h>
#include <basic/portability/utility.h>

namespace basic {

namespace hash {

//  hash_128_to_64
//
//  The Hash128to64 function from Google's cityhash (under the MIT License).
//
//  We use it to reduce multiple 64 bit hashes into a single hash.
BASIC_DISABLE_UNDEFINED_BEHAVIOR_SANITIZER("unsigned-integer-overflow")
constexpr uint64_t hash_128_to_64(
    const uint64_t upper, const uint64_t lower) noexcept {
  // Murmur-inspired hashing.
  const uint64_t kMul = 0x9ddfea08eb382d69ULL;
  uint64_t a = (lower ^ upper) * kMul;
  a ^= (a >> 47);
  uint64_t b = (upper ^ a) * kMul;
  b ^= (b >> 47);
  b *= kMul;
  return b;
}

} // namespace hash

namespace detail {

template <typename I>
struct integral_hasher {
  using basic_is_avalanching =
      bool_constant<(sizeof(I) >= 8 || sizeof(size_t) == 4)>;

  size_t operator()(I const& i) const noexcept {
    static_assert(sizeof(I) <= 16, "Input type is too wide");
    /* constexpr */ if (sizeof(I) <= 4) {
      auto const i32 = static_cast<int32_t>(i); // impl accident: sign-extends
      auto const u32 = static_cast<uint32_t>(i32);
      return static_cast<size_t>(hash::jenkins_rev_mix32(u32));
    } else if (sizeof(I) <= 8) {
      auto const u64 = static_cast<uint64_t>(i);
      return static_cast<size_t>(hash::twang_mix64(u64));
    } else {
      auto const u = to_unsigned(i);
      auto const hi = static_cast<uint64_t>(u >> sizeof(I) * 4);
      auto const lo = static_cast<uint64_t>(u);
      return hash::hash_128_to_64(hi, lo);
    }
  }
};

template <typename F>
struct float_hasher {
  using basic_is_avalanching = std::true_type;

  size_t operator()(F const& f) const noexcept {
    static_assert(sizeof(F) <= 8, "Input type is too wide");

    if (f == F{}) { // Ensure 0 and -0 get the same hash.
      return 0;
    }

    uint64_t u64 = 0;
    memcpy(&u64, &f, sizeof(F));
    return static_cast<size_t>(hash::twang_mix64(u64));
  }
};

} // namespace detail

template <class Key, class Enable = void>
struct hasher;

struct Hash {
  template <class T>
  size_t operator()(const T& v) const noexcept(noexcept(hasher<T>()(v))) {
    return hasher<T>()(v);
  }

  template <class T, class... Ts>
  size_t operator()(const T& t, const Ts&... ts) const {
    return hash::hash_128_to_64((*this)(t), (*this)(ts...));
  }

  size_t operator()() const noexcept { return 0; }
};

// IsAvalanchingHasher<H, K> extends std::integral_constant<bool, V>.
// V will be true if it is known that when a hasher of type H computes
// the hash of a key of type K, any subset of B bits from the resulting
// hash value is usable in a context that can tolerate a collision rate
// of about 1/2^B.  (Input bits lost implicitly converting between K and
// the argument of H::operator() are not considered here; K is separate
// to handle the case of generic hashers like basic::Hash).
//
// If std::hash<T> or basic::hasher<T> is specialized for a new type T and
// the implementation avalanches input entropy across all of the bits of a
// std::size_t result, the specialization should be marked as avalanching.
// This can be done either by adding a member type basic_is_avalanching
// to the functor H that contains a constexpr bool value of true, or by
// specializing IsAvalanchingHasher<H, K>.  The member type mechanism is
// more convenient, but specializing IsAvalanchingHasher may be required
// if a hasher is polymorphic on the key type or if its definition cannot
// be modified.
//
// The standard's definition of hash quality is based on the chance hash
// collisions using the entire hash value.  No requirement is made that
// this property holds for subsets of the bits.  In addition, hashed keys
// in real-world workloads are not chosen uniformly from the entire domain
// of keys, which can further increase the collision rate for a subset
// of bits.  For example, std::hash<uint64_t> in libstdc++-v3 and libc++
// is the identity function.  This hash function has no collisions when
// considering hash values in their entirety, but for real-world workloads
// the high bits are likely to always be zero.
//
// Some hash functions provide a stronger guarantee -- the standard's
// collision property is also preserved for subsets of the output bits and
// for sub-domains of keys.  Another way to say this is that each bit of
// the hash value contains entropy from the entire input, changes to the
// input avalanche across all of the bits of the output.  The distinction
// is useful when mapping the hash value onto a smaller space efficiently
// (such as when implementing a hash table).
template <typename Hasher, typename Key>
struct IsAvalanchingHasher;

namespace detail {
template <typename Hasher, typename Void = void>
struct IsAvalanchingHasherFromMemberType : std::false_type {};

template <typename Hasher>
struct IsAvalanchingHasherFromMemberType<
    Hasher,
    void_t<typename Hasher::basic_is_avalanching>>
    : bool_constant<Hasher::basic_is_avalanching::value> {};
} // namespace detail

template <typename Hasher, typename Key>
struct IsAvalanchingHasher : detail::IsAvalanchingHasherFromMemberType<Hasher> {
};

// It's ugly to put this here, but basic::transparent isn't hash specific
// so it seems even more ugly to put this near its declaration
template <typename H, typename K>
struct IsAvalanchingHasher<basic::transparent<H>, K> : IsAvalanchingHasher<H, K> {};

template <typename K>
struct IsAvalanchingHasher<Hash, K> : IsAvalanchingHasher<hasher<K>, K> {};

template <>
struct hasher<bool> {
  using basic_is_avalanching = std::true_type;

  size_t operator()(bool key) const noexcept {
    // Make sure that all the output bits depend on the input.
    return key ? std::numeric_limits<size_t>::max() : 0;
  }
};
template <typename K>
struct IsAvalanchingHasher<hasher<bool>, K> : std::true_type {};

template <>
struct hasher<unsigned long long>
    : detail::integral_hasher<unsigned long long> {};

template <>
struct hasher<signed long long> : detail::integral_hasher<signed long long> {};

template <>
struct hasher<unsigned long> : detail::integral_hasher<unsigned long> {};

template <>
struct hasher<signed long> : detail::integral_hasher<signed long> {};

template <>
struct hasher<unsigned int> : detail::integral_hasher<unsigned int> {};

template <>
struct hasher<signed int> : detail::integral_hasher<signed int> {};

template <>
struct hasher<unsigned short> : detail::integral_hasher<unsigned short> {};

template <>
struct hasher<signed short> : detail::integral_hasher<signed short> {};

template <>
struct hasher<unsigned char> : detail::integral_hasher<unsigned char> {};

template <>
struct hasher<signed char> : detail::integral_hasher<signed char> {};

template <> // char is a different type from both signed char and unsigned char
struct hasher<char> : detail::integral_hasher<char> {};

#if BASIC_HAVE_INT128_T
template <>
struct hasher<signed __int128> : detail::integral_hasher<signed __int128> {};

template <>
struct hasher<unsigned __int128> : detail::integral_hasher<unsigned __int128> {
};
#endif

template <>
struct hasher<float> : detail::float_hasher<float> {};

template <>
struct hasher<double> : detail::float_hasher<double> {};

template <>
struct hasher<std::string> {
  using basic_is_avalanching = std::true_type;

  size_t operator()(const std::string& key) const {
    return static_cast<size_t>(
        hash::SpookyHashV2::Hash64(key.data(), key.size(), 0));
  }
};
template <typename K>
struct IsAvalanchingHasher<hasher<std::string>, K> : std::true_type {};

template <>
struct hasher<base::StringPiece> {
  using basic_is_avalanching = std::true_type;

  size_t operator()(const base::StringPiece key) const {
    return static_cast<size_t>(
        hash::SpookyHashV2::Hash64(key.data(), key.size(), 0));
  }
};
template <typename K>
struct IsAvalanchingHasher<hasher<base::StringPiece>, K> : std::true_type {};

template <typename T>
struct hasher<T, std::enable_if_t<std::is_enum<T>::value>> {
  size_t operator()(T key) const noexcept { return Hash()(to_underlying(key)); }
};

template <typename T, typename K>
struct IsAvalanchingHasher<
    hasher<T, std::enable_if_t<std::is_enum<T>::value>>,
    K> : IsAvalanchingHasher<hasher<std::underlying_type_t<T>>, K> {};

template <typename T1, typename T2>
struct hasher<std::pair<T1, T2>> {
  using basic_is_avalanching = std::true_type;

  size_t operator()(const std::pair<T1, T2>& key) const {
    return Hash()(key.first, key.second);
  }
};

template <typename... Ts>
struct hasher<std::tuple<Ts...>> {
  size_t operator()(const std::tuple<Ts...>& key) const {
    return apply(Hash(), key);
  }
};

template <typename T>
struct hasher<T*> {
  using basic_is_avalanching = hasher<std::uintptr_t>::basic_is_avalanching;

  size_t operator()(T* key) const {
    return Hash()(bit_cast<std::uintptr_t>(key));
  }
};

template <typename T>
struct hasher<std::unique_ptr<T>> {
  using basic_is_avalanching = typename hasher<T*>::basic_is_avalanching;

  size_t operator()(const std::unique_ptr<T>& key) const {
    return Hash()(key.get());
  }
};

template <typename T>
struct hasher<std::shared_ptr<T>> {
  using basic_is_avalanching = typename hasher<T*>::basic_is_avalanching;

  size_t operator()(const std::shared_ptr<T>& key) const {
    return Hash()(key.get());
  }
};

// combiner for multi-arg tuple also mixes bits
template <typename T, typename K>
struct IsAvalanchingHasher<hasher<std::tuple<T>>, K>
    : IsAvalanchingHasher<hasher<T>, K> {};
template <typename T1, typename T2, typename... Ts, typename K>
struct IsAvalanchingHasher<hasher<std::tuple<T1, T2, Ts...>>, K>
    : std::true_type {};

namespace hash {

// Simply uses std::hash to hash.  Note that std::hash is not guaranteed
// to be a very good hash function; provided std::hash doesn't collide on
// the individual inputs, you are fine, but that won't be true for, say,
// strings or pairs
class StdHasher {
 public:
  // The standard requires all explicit and partial specializations of std::hash
  // supplied by either the standard library or by users to be default
  // constructible.
  template <typename T>
  size_t operator()(const T& t) const noexcept(noexcept(std::hash<T>()(t))) {
    return std::hash<T>()(t);
  }
};

// This is a general-purpose way to create a single hash from multiple
// hashable objects. hash_combine_generic takes a class Hasher implementing
// hash<T>; hash_combine uses a default hasher StdHasher that uses std::hash.
// hash_combine_generic hashes each argument and combines those hashes in
// an order-dependent way to yield a new hash; hash_range does so (also in an
// order-dependent way) for items in the range [first, last);
// commutative_hash_combine_* hashes values but combines them in an
// order-independent way to yield a new hash.

template <class Hash, class Value>
uint64_t commutative_hash_combine_value_generic(
    uint64_t seed, Hash const& hasher, Value const& value) {
  auto const x = hasher(value);
  auto const y = IsAvalanchingHasher<Hash, Value>::value ? x : twang_mix64(x);
  // Commutative accumulator taken from this paper:
  // https://www.preprints.org/manuscript/201710.0192/v1/download
  return 3860031 + (seed + y) * 2779 + (seed * y * 2);
}

// hash_range combines hashes of items in the range [first, last) in an
// __order-dependent__ fashion. To hash an unordered container (e.g.,
// basic::dynamic, hash tables like std::unordered_map), use
// commutative_hash_combine_range instead, which combines hashes of items
// independent of ordering.
template <
    class Iter,
    class Hash = std::hash<typename std::iterator_traits<Iter>::value_type>>
uint64_t hash_range(
    Iter begin, Iter end, uint64_t hash = 0, Hash hasher = Hash()) {
  for (; begin != end; ++begin) {
    hash = hash_128_to_64(hash, hasher(*begin));
  }
  return hash;
}

template <class Hash, class Iter>
uint64_t commutative_hash_combine_range_generic(
    uint64_t seed, Hash const& hasher, Iter first, Iter last) {
  while (first != last) {
    seed = commutative_hash_combine_value_generic(seed, hasher, *first++);
  }
  return seed;
}

template <class Iter>
uint64_t commutative_hash_combine_range(Iter first, Iter last) {
  return commutative_hash_combine_range_generic(0, Hash{}, first, last);
}

namespace detail {
using c_array_size_t = size_t[];
} // namespace detail

// Never used, but gcc demands it.
template <class Hasher>
inline size_t hash_combine_generic(const Hasher&) noexcept {
  return 0;
}

template <class Hasher, typename T, typename... Ts>
size_t hash_combine_generic(
    const Hasher& h,
    const T& t,
    const Ts&... ts) noexcept(noexcept(detail::c_array_size_t{
    h(t), h(ts)...})) {
  size_t seed = h(t);
  if (sizeof...(ts) == 0) {
    return seed;
  }
  size_t remainder = hash_combine_generic(h, ts...);
  if /* constexpr */ (sizeof(size_t) == sizeof(uint32_t)) {
    return twang_32from64((uint64_t(seed) << 32) | remainder);
  } else {
    return static_cast<size_t>(hash_128_to_64(seed, remainder));
  }
}

template <typename Hash, typename... Value>
uint64_t commutative_hash_combine_generic(
    uint64_t seed, Hash const& hasher, Value const&... value) {
  // variadic foreach:
  uint64_t _[] = {
      0, seed = commutative_hash_combine_value_generic(seed, hasher, value)...};
  (void)_;
  return seed;
}

template <typename T, typename... Ts>
size_t hash_combine(const T& t, const Ts&... ts) noexcept(
    noexcept(hash_combine_generic(StdHasher{}, t, ts...))) {
  return hash_combine_generic(StdHasher{}, t, ts...);
}

template <typename... Value>
uint64_t commutative_hash_combine(Value const&... value) {
  return commutative_hash_combine_generic(0, Hash{}, value...);
}

} // namespace hash

// recursion
template <size_t index, typename... Ts>
struct TupleHasher {
  size_t operator()(std::tuple<Ts...> const& key) const {
    return hash::hash_combine(
        TupleHasher<index - 1, Ts...>()(key), std::get<index>(key));
  }
};

// base
template <typename... Ts>
struct TupleHasher<0, Ts...> {
  size_t operator()(std::tuple<Ts...> const& key) const {
    // we could do std::hash here directly, but hash_combine hides all the
    // ugly templating implicitly
    return hash::hash_combine(std::get<0>(key));
  }
};

} // namespace basic

// Custom hash functions.
namespace std {
// Hash function for pairs. Requires default hash functions for both
// items in the pair.
template <typename T1, typename T2>
struct hash<std::pair<T1, T2>> {
  using basic_is_avalanching = std::true_type;

  size_t operator()(const std::pair<T1, T2>& x) const {
    return basic::hash::hash_combine(x.first, x.second);
  }
};

// Hash function for tuples. Requires default hash functions for all types.
template <typename... Ts>
struct hash<std::tuple<Ts...>> {
 private:
  using FirstT = std::decay_t<std::tuple_element_t<0, std::tuple<Ts..., bool>>>;

 public:
  using basic_is_avalanching = basic::bool_constant<(
      sizeof...(Ts) != 1 ||
      basic::IsAvalanchingHasher<std::hash<FirstT>, FirstT>::value)>;

  size_t operator()(std::tuple<Ts...> const& key) const {
    basic::TupleHasher<
        sizeof...(Ts) - 1, // start index
        Ts...>
        hasher;

    return hasher(key);
  }
};
} // namespace std

namespace basic {

// std::hash<std::string> is avalanching on libstdc++-v3 (code checked),
// libc++ (code checked), and MSVC (based on online information).
// std::hash for float and double on libstdc++-v3 are avalanching,
// but they are not on libc++.  std::hash for integral types is not
// avalanching for libstdc++-v3 or libc++.  We're conservative here and
// just mark std::string as avalanching.  std::string_view will also be
// so, once it exists.
template <typename... Args, typename K>
struct IsAvalanchingHasher<std::hash<std::basic_string<Args...>>, K>
    : std::true_type {};

} // namespace basic
