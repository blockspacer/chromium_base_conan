# About

Never friend std::make_unique to work around constructor access restrictions.
It will allow anyone to construct the class. Use base::WrapUnique in this case.

DON'T:

class Bad {
 public:
  std::unique_ptr<Bad> Create() { return std::make_unique<Bad>(); }
  // ...
 private:
  Bad();
  // ...
  friend std::unique_ptr<Bad> std::make_unique<Bad>();  // Lost access control
};
DO:

class Okay {
 public:
  // For explanatory purposes. If Create() adds no value, it is better just
  // to have a public constructor instead.
  std::unique_ptr<Okay> Create() { return base::WrapUnique(new Okay()); }
  // ...
 private:
  Okay();
  // ...
};
base::WrapUnique(new Foo) and base::WrapUnique(new Foo()) mean something different if Foo does not have a user-defined constructor. Don‘t make future maintainers guess whether you left off the ‘()’ on purpose. Use std::make_unique<Foo>() instead. If you’re intentionally leaving off the “()” as an optimization, please leave a comment.

auto a = base::WrapUnique(new A); // BAD: "()" omitted intentionally?
auto a = std::make_unique<A>();   // GOOD
// "()" intentionally omitted to avoid unnecessary zero-initialization.
// base::WrapUnique() does the wrong thing for array pointers.
auto array = std::unique_ptr<A[]>(new A[size]);
//
