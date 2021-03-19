# Bloom filters

A Bloom filter is a space-efficient probabilistic data structure that tests whether an element is a member of a set (if a value is ‘possibly in the set’ or ‘definitely not in the set’).

A Bloom filter keeps track of objects without actually storing them, it simply tracks whether it has seen an object before or not.

The basic bloom filter (not its variations) supports two operations: test and add (note: no remove operation!).

You must know the expected capacity of basic bloom filter (not its variations) in advance - if you guess too high, you’ll waste space.

Also bloom filter can not give you a list of all elements that are currently in your set.

If you really need to have a Removal functionality - use a variation of the bloom filter (‘Counting bloom filter’, etc.)

In other words, given a set of elements, bloom filter can tell you that:

A) given element is definitely not in the set, or

B) given element is maybe in the set.

It can give you a false positive: it can say that an element is in the set when it in fact is not.

But it will never give you a false negative: it will never say that an element is not in the set when in fact it is.

The classic example of using bloom filters is to reduce expensive disk (or network) lookups for non-existent keys.

If the element is not in the bloom filter, then we know for sure we don’t need to perform the expensive lookup.

See:
* https://vorbrodt.blog/2019/04/04/bloom-filters/
* https://daankolthof.com/2019/05/06/implementing-a-simple-high-performance-bloom-filter-in-c/
* https://hackernoon.com/probabilistic-data-structures-bloom-filter-5374112a7832
* https://medium.com/system-design-blog/bloom-filter-a-probabilistic-data-structure-12e4e5cf0638
* https://freecontent.manning.com/all-about-bloom-filters/
* https://onatm.dev/2020/08/10/let-s-implement-a-bloom-filter/
* https://bowenli86.github.io/2016/10/07/data%20structures%20and%20algorithms/bloom%20filter/Bloom-Filter-Introduction/
* https://llimllib.github.io/bloomfilter-tutorial/
* https://blog.gopheracademy.com/advent-2014/bloom-filters/
* https://github.com/chromium/chromium/blob/99314be8152e688bafbbf9a615536bdbb289ea87/components/rappor/bloom_filter.h
* https://github.com/chromium/chromium/blob/99314be8152e688bafbbf9a615536bdbb289ea87/components/optimization_guide/bloom_filter.h
* https://github.com/chromium/chromium/blob/99314be8152e688bafbbf9a615536bdbb289ea87/third_party/blink/renderer/platform/wtf/bloom_filter.h
* https://github.com/yugabyte/yugabyte-db/blob/7568877236ce8a3b72b7fd0f9083a31731018ea9/src/yb/rocksdb/util/dynamic_bloom.h
* https://github.com/yugabyte/yugabyte-db/blob/7568877236ce8a3b72b7fd0f9083a31731018ea9/src/yb/rocksdb/util/bloom.cc
* https://github.com/yugabyte/yugabyte-db/blob/7568877236ce8a3b72b7fd0f9083a31731018ea9/src/yb/util/bitmap.h
* book: C++ Data Structures and Algorithm Design https://github.com/TrainingByPackt/CPP-Data-Structures-and-Algorithm-Design-Principles/blob/04f2f9e5a31e3d95c5b71665a67169335725c97f/Lesson3/Exercise17/Exercise17.cpp#L4

## Here is a very nice visualization of how it works.

See:
* https://www.jasondavies.com/bloomfilter/

## How do giant sites like Facebook and Google check Username or Domain availability so fast?

See:
* https://www.hackerearth.com/blog/developers/how-websites-check-username-availability-quickly/

## Usage examples

Use Bloom filter if you want to detect previously stored data.

* Recomendation engine can use Bloom filter to avoid recommending articles a user has previously read (you check whether the combination of user_id + article_id is there). See https://blog.medium.com/what-are-bloom-filters-1ec2a50c68ff
* Databases use Bloom filters to reduce the disk lookups for non-existent rows or columns. Avoiding costly disk lookups considerably increases the performance of a database query operation
* Web browsers use Bloom filter to identify malicious URLs. Any URL was first checked against a local Bloom filter, and only if the Bloom filter returned a positive result was a full check of the URL performed (and the user warned, if that too returned a positive result). A bloom filter for all malicous URL's is small enough to be kept on your computer and even in memory. See https://stackoverflow.com/a/30247022 and https://stackoverflow.com/questions/18447874/google-chrome-usage-of-bloom-filter
* Archival storage system uses Bloom filters to detect previously stored data.
* Writing a full-text search engine using Bloom filters https://www.stavros.io/posts/bloom-filter-search-engine/
* Check for weak password list https://hackernoon.com/probabilistic-data-structures-bloom-filter-5374112a7832
* Instead of making a query to an SQL database to check if a user with a certain email exists, you could first use a bloom filter for an inexpensive lookup check. If the email doesn’t exist, great! If it does exist, you might have to make an extra query to the database. You can do the same to search for if a ‘Username is already taken’. https://www.geeksforgeeks.org/bloom-filters-introduction-and-python-implementation/
* You can also make a Spell-checker by using bloom filter to track the dictionary words. http://codekata.com/kata/kata05-bloom-filters/
* DDoS protection.
* Say you want to sync a hash graph, such as a Git repository, between two nodes https://martin.kleppmann.com/2020/12/02/bloom-filter-hash-graph-sync.html
* bitcoin uses bloom filter for wallet synchronization https://bitcoin.stackexchange.com/questions/30285/bip32-wallet-sync-with-bloom-filters

## Time complexity

Bloom filter has constant time complexity for both adding items and asking whether a key is present or not.

## Space complexity

Bloom filter requires very less space compared to the number of items you need to store and check.

## Memory access (cache locality)

Bloom filters optimize for memory usage, not for memory access.

## Bloom filter variants

Bloom filters are a good basic data structure that leave them ripe to variations, generally at the cost of more space.

### Counting Bloom filter

Counting Bloom Filters are poorly named; the name ‘counting’ sounds like you can query frequencies instead of just set membership.

In fact, the only additional feature a counting Bloom filter provides is the ability to delete entries. Removing entries from a traditional Bloom filter is not possible normally. Resetting bits to 1 might remove additional keys if there were any hash collisions. Instead of setting a single bit, a counting Bloom filter maintains a 4-bit counter, so that hash collisions increment the counters, and a removal just decrements. (The math shows that 4 bits is sufficient, with high probability.) Patrick Mylud has an implementation of a counting Bloom filter in pmylund/go-bloom.

### Scaling Bloom Filters

Another problem with Bloom filters is that you must know the expected capacity in advance. If you guess too high, you’ll waste space. If you guess too low, you’ll increase the rate of false positives before you’ve inserted all your items.

A scaling Bloom filter solve this by starting with a small Bloom filter and creating additional ones as needed. Jian Zhen has implemented scaling Bloom filters in dataence/bloom/scalable.

### Opposite of a Bloom Filter

A Bloom filter provides no false negatives only false positives. An interesting curiosity is “what’s a data structure that provides for only false negatives no false positives.” A list of keys that expires some entries has this policy: any item that the list reports as in the set is actually there, but an entry that is listed as “not present” may have simply been removed instead. Jeff Hodges has implemented this as jmhodges/opposite_of_a_bloom_filter

## FAQ

* Does Bloom filter has any drawbacks?

Random memory access is slow (think about cache locality).

See https://blog.cloudflare.com/when-bloom-filters-dont-bloom/ and https://www.reddit.com/r/programming/comments/fcc0zr/when_bloom_filters_dont_bloom/

* Are Bloom filters useful?

Bloom filters may be useful when both of the following conditions are met:

1. A False Negative is unacceptable (and false positive are acceptable)
2. Cost of lookup is expensive relative to the cost of lookup in a Bloom Filter

Bloom Filters help when you have limited capacity of low latency storage in front of high capacity high latency stage.

E.g. memory in front of spinning disk or spinning disk in front of tape.

If you put it simple in-memory Bloom filter in front of memory it will not help.

* Alternatives?

The Cuckoo filter is another variation of the bloom filter.

Cuckoo filters support adding and removing items dynamically while achieving even higher performance than Bloom filters.

See Cuckoo Filter paper https://www.cs.cmu.edu/~dga/papers/cuckoo-conext2014.pdf
