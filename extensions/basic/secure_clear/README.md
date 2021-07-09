# About

Sensitive data, like passwords or keying data,
should be cleared from memory as soon as they are not needed.

You should use special memory-clearing functions,
which can not be deleted by the compiler when it optimizes the code.

Inspired by "secure_clear" standard:

* http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/p1315r5.html.
* https://github.com/ojeda/secure_clear

## FAQ

* I need to go even further
  You can create functions that fill the array with pseudo-random values
  and have different running time to hinder attacks based on time measuring.

* Why you can not clear private data using memset() function.
  http://www.cplusplus.com/articles/ETqpX9L8/

* Why memset() function in release builds may work differently.
  The compiler assumes that there is no need to call a function erasing data since they are no longer in use.
  It is not an error; it is a legal choice of the compiler.
  Compilers tend to delete memset() calls for the sake of optimization working with both stack and dynamic memory of the application.

