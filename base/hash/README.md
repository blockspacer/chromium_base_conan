# Choosing A Hash Function

If a hash function with unchanging output is needed, please select from one of
the unchanging forever options below.

## Non-cryptographic

name                                         | input                       | output     | unchanging forever | notes
---------------------------------------------|-----------------------------|------------|--------------------|-------
[`Hash()`][hash]                             | overloaded                  | `uint32_t` | no                 |
[`PersistentHash()`][persistenthash]         | overloaded                  | `uint32_t` | yes                | Fairly weak but widely used for persisted hashes.
[`CityHash64()`][cityhash64]                 | `base::span<const uint8_t>` | `uint64_t` | yes (note 1)       | Version 1.0.3. Has some known weaknesses.
[`CityHash64WithSeed()`][cityhash64withseed] | `base::span<const uint8_t>` | `uint64_t` | yes (note 1)       | Version 1.0.3. Has some known weaknesses.

## Cryptographic

**There are no hashes in `base/hash` that provide cryptographic security.**

 name                          | input         | output        | unchanging forever | notes
-------------------------------|---------------|---------------|--------------------|-------
[`MD5String()`][md5string]     | `std::string` | `std::string` | yes                | **INSECURE**
[`SHA1HashString`][sha1string] | `std::string` | `std::string` | yes                | **INSECURE**
