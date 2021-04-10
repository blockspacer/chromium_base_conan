# About

Varints are a method of serializing integers using one or more bytes i.e. way of compressing down integers into a smaller space than is normally needed.

By default, computers use fixed length integers for reasons of hardware efficiency.

However, when transmitting or storing integers, it is important to compress them down in order to save bandwidth.

Varints are based on the idea that most numbers are not uniformly distributed.

Almost always, smaller numbers are more common in computing than larger ones.

The trade off that varints make is to spend more bits on larger numbers, and fewer bits on smaller numbers.

For example, a 64 bit integer that is almost always less than 256 would be wasting the top 56 bits of a fixed width representation.

The two common ways of encoding varints are length prefixed, and continuation bits.

Google Protobuf use the latter technique, using the top bit of each byte to indicate whether or not there are more bytes coming.

Google Protobuf uses zigzag encoding (also described there) for signed integer representation described at https://developers.google.com/protocol-buffers/docs/encoding

ZigZag encoding maps signed integers to unsigned integers so that numbers with a small absolute value (for instance, -1) have a small varint encoded value too.

It does this in a way that "zig-zags" back and forth through the positive and negative integers, so that -1 is encoded as 1, 1 is encoded as 2, -2 is encoded as 3, and so on.

In other words, each value n is ZigZag encoded using (n << 1) ^ (n >> 31).

UTF-8 encoding of characters makes use of the former encoding technique by prefixing a length to the number.

Encoding and decoding of varints is fast.

Because we know the prefix ahead of time, decoding can be implemented in terms of table look ups.

See:

* https://carlmastrangelo.com/blog/lets-make-a-varint
* https://developers.google.com/protocol-buffers/docs/encoding
* https://en.wikipedia.org/wiki/Variable-length_quantity
* https://golang.org/src/encoding/binary/varint.go
* https://www.slideshare.net/dxhuy88/story-writing-byte-serializer-in-golang
* https://developpaper.com/explain-the-principle-of-varint-coding-in-detail/
* https://hackernoon.com/encoding-base128-varints-explained-371j3uz8
* https://sqlite.org/src4/doc/trunk/www/varint.wiki
* https://github.com/stoklund/varint
* https://techoverflow.net/2013/01/25/efficiently-encoding-variable-length-integers-in-cc/
* https://www.boost.org/doc/libs/master/boost/beast/core/detail/varint.h
* https://golb.hplar.ch/2019/06/variable-length-int-java.html

Smaller numbers take a smaller number of bytes.

Each byte in a varint, except the last byte, has the most significant bit (msb) set - this indicates that there are further bytes to come.

The lower 7 bits of each byte are used to store the two's complement representation of the number in groups of 7 bits, least significant group first.

So, for example, here is the number 1 - it's a single byte, so the msb is not set:

0000 0001

And here is 300 - this is a bit more complicated:

1010 1100 0000 0010

How do you figure out that this is 300? First you drop the msb from each byte, as this is just there to tell us whether we've reached the end of the number (as you can see, it's set in the first byte as there is more than one byte in the varint):

   1010 1100 0000 0010
-> 010 1100  000 0010

You reverse the two groups of 7 bits because, as you remember, varints store numbers with the least significant group first. Then you concatenate them to get your final value:

    000 0010  010 1100
->  000 0010 ++ 010 1100
->  100101100
->  256 + 32 + 8 + 4 = 300

## NOTE

Variable width makes it impossible to access anything later in the message without parsing the varint.

Use varint if random-access is not important.

In theory you could design such a format that can tell the length based on the first byte i.e. length-prefixed varint.

See:

* https://groups.google.com/g/capnproto/c/Qxw7YSoPP18/m/HS06KchMpIQJ
* https://news.ycombinator.com/item?id=11656973

