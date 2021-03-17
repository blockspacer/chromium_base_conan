## About

Some usage examples.

See for details:

*

## FAQ

* How to print (format) time?

See `base/i18n/time_formatting.h`

```cpp
  TimeDelta delta = TimeDelta::FromSeconds(15 * 3600 + 0 * 60 + 30);
  EXPECT_EQ(ASCIIToUTF16("15 hours, 0 minutes, 30 seconds"),
            TimeDurationFormatWithSecondsString(delta, DURATION_WIDTH_WIDE));
  EXPECT_EQ(ASCIIToUTF16("15 hr, 0 min, 30 sec"),
            TimeDurationFormatWithSecondsString(delta, DURATION_WIDTH_SHORT));
  EXPECT_EQ(ASCIIToUTF16("15h 0m 30s"),
            TimeDurationFormatWithSecondsString(delta, DURATION_WIDTH_NARROW));
  EXPECT_EQ(ASCIIToUTF16("15:00:30"),
            TimeDurationFormatWithSecondsString(delta, DURATION_WIDTH_NUMERIC));
```
