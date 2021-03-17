# Notes

Before adding macros here make sure that similar functionality not present in googletest or googlemock, see:

* https://github.com/google/googletest/blob/release-1.10.0/googletest/docs/primer.md
* https://github.com/google/googletest/blob/release-1.10.0/googlemock/docs/cheat_sheet.md

Use `SCOPED_TRACE`, example `SCOPED_TRACE(base::StringPrintf("Callback Depth: %zu", expected_trace.size()));`

## MUST READ

* [Unit Testing in Blink](https://www.chromium.org/blink/unittesting)
