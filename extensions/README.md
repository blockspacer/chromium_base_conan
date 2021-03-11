# About

Use `extensions` when you need to:
* patch original files in base - some files have too many modifications to be stored in git `.patch` files
* fix missing include paths - `base/extensions/` in public include directories

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
find $PWD/extensions/testing/gtest -type f -name "*.h" -exec bash -c 'replace_header_contents "$0"' {} \;
replace_header_contents () \
{ \
  echo "#pragma once" > $1; \
  echo "#include \"${1#$PWD/extensions/testing/gmock/include/}\" " >> $1 ; \
}
find $PWD/extensions/testing/gmock -type f -name "*.h" -exec bash -c 'replace_header_contents "$0"' {} \;
```

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
find $PWD/extensions/third_party/abseil-cpp/absl -type f -name "*" -exec bash -c 'replace_header_contents "$0"' {} \;
```
