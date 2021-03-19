# About

Use `extensions` when you need to:
* patch original files in base - some files have too many modifications to be stored in git `.patch` files
* fix missing include paths - `base/extensions/` in public include directories
* replace folders in `base/third_party/` with conan packages

## How to upgrade double_conversion

```bash
mv base/third_party/double_conversion extensions/base/third_party/double_conversion
replace_header_contents () \
{ \
  echo "#pragma once" > $1; \
  echo "#include \"${1#$PWD/extensions/base/third_party/double_conversion/}\" " >> $1 ; \
}
export -f replace_header_contents
find $PWD/extensions/base/third_party/double_conversion -type f -name "*.h" -exec bash -c 'replace_header_contents "$0"' {} \;
```

## How to upgrade chromium/src/build

```bash
git clone https://chromium.googlesource.com/chromium/src/build
rm -rf build/.git
```

## How to upgrade chromium/src/testing

```bash
git clone https://chromium.googlesource.com/chromium/src/testing
rm -rf testing/.git
replace_header_contents () \
{ \
  echo "#pragma once" > $1; \
  echo "#include \"${1#$PWD/extensions/testing/gtest/include/}\" " >> $1 ; \
}
export -f replace_header_contents
find $PWD/extensions/testing/gtest -type f -name "*.h" -exec bash -c 'replace_header_contents "$0"' {} \;
replace_header_contents () \
{ \
  echo "#pragma once" > $1; \
  echo "#include \"${1#$PWD/extensions/testing/gmock/include/}\" " >> $1 ; \
}
export -f replace_header_contents
find $PWD/extensions/testing/gmock -type f -name "*.h" -exec bash -c 'replace_header_contents "$0"' {} \;
```

## How to upgrade `boostorg/preprocessor`

See https://github.com/boostorg/preprocessor/tree/boost-1.75.0

## How to upgrade Abseil

Download `absl` directory from https://github.com/abseil/abseil-cpp and place it into `extensions/third_party/abseil-cpp/`

```bash
rm -rf extensions/third_party/abseil-cpp/absl
mv absl extensions/third_party/abseil-cpp/absl
```

Delete all not-header files from `absl` directory

```bash
find $PWD/extensions/third_party/abseil-cpp/absl -type f ! -name '*.hpp' ! -name '*.h' ! -name '*.inc' -delete
```

Patch header files in `absl` directory

```bash
replace_header_contents () \
{ \
  echo "#pragma once" > $1; \
  echo "#include \"${1#$PWD/extensions/third_party/abseil-cpp/}\" " >> $1 ; \
}
export -f replace_header_contents
find $PWD/extensions/third_party/abseil-cpp/absl -type f -name "*" -exec bash -c 'replace_header_contents "$0"' {} \;
```

## How to upgrade linux-syscall-support

Download https://chromium.googlesource.com/linux-syscall-support/+archive/ddd5690e9af39e7cbd0c9a9dd35c0702b14b5a4c.tar.gz

Unpack into `extensions/third_party/lss/`

Delete all not-header files from `lss` directory

```bash
find $PWD/extensions/third_party/lss -type f ! -name '*.h' ! -name '*.hpp' ! -name '*.h' ! -name '*.inc' -delete
```

Patch header files in `lss` directory

```bash
replace_header_contents () \
{ \
  echo "#pragma once" > $1; \
  echo "#include \"${1#$PWD/extensions/third_party/lss/}\" " >> $1 ; \
}
export -f replace_header_contents
find $PWD/extensions/third_party/lss -type f -name "*" -exec bash -c 'replace_header_contents "$0"' {} \;
```


## How to upgrade openssl

Place headers into `third_party/boringssl/src/include/openssl/`

## How to upgrade perfetto

```bash
rm -rf extensions/third_party/perfetto
git clone https://github.com/google/perfetto
mv include extensions/third_party/perfetto/include
mv gen/protos extensions/third_party/perfetto/protos
```

Delete all not-header files from `perfetto` directory

```bash
find $PWD/extensions/third_party/perfetto/include -type f ! -name '*.h' ! -name '*.hpp' ! -name '*.h' ! -name '*.inc' -delete
```

Patch header files in `perfetto` directory

```bash
replace_header_contents () \
{ \
  echo "#pragma once" > $1; \
  echo "#include \"${1#$PWD/extensions/third_party/perfetto/include/}\" " >> $1 ; \
}
export -f replace_header_contents
find $PWD/extensions/third_party/perfetto/include -type f -name "*" -exec bash -c 'replace_header_contents "$0"' {} \;
#
replace_header_contents () \
{ \
  echo "#pragma once" > $1; \
  echo "#include \"${1#$PWD/extensions/third_party/perfetto/gen/}\" " >> $1 ; \
}
export -f replace_header_contents
find $PWD/extensions/third_party/perfetto/gen -type f -name "*" -exec bash -c 'replace_header_contents "$0"' {} \;
```
