# About

Place string related code here.

ColorModel

## FixedString

Inspired by `folly::FixedString` but without exceptions and uses `base::span`, `base::StringPiece`, etc.

Usage:

```cpp
struct ColorModel final {
  using Identifier = FixedString<10>;

  // Human readable identifier of the color model (e.g. `RGB`).
  Identifier identifier;

  // Number of independent color components in the color model (e.g. 3 for for
  // `RGB`).
  std::uint8_t numberOfColorComponents;
};

static constexpr auto Gray = ColorModel{"gray", 1};
static constexpr auto RGB = ColorModel{"rgb", 3};

std::cout << std::string(RGB.identifier) << std::endl;
```
