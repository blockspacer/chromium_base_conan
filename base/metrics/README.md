# Usage

UMA (User Metrics Analysis) is user metrics e.g. latency metrics, feature usage, etc.

A histogram is a chart that groups numeric data into bins, displaying the bins as segmented columns.

Histogram is an object that aggregates statistics, and can summarize them in
various forms, including ASCII graphical, HTML, and numerically (as a
vector of numbers corresponding to each of the aggregating buckets).

It supports calls to accumulate either time intervals (which are processed
as integral number of milliseconds), or arbitrary integral units.

Histograms are often put in areas where they are called many many times, and
performance is critical.  As a result, they are designed to have a very low
recurring cost of executing (adding additional samples).

See for details:

* https://chromium.googlesource.com/chromium/src/+/master/tools/metrics/histograms/README.md
* https://chromium.googlesource.com/chromium/src.git/+/HEAD/tools/metrics/histograms/README.md
* https://github.com/chromium/chromium/blob/b29e8a942dd6facfec8beccdada522c34a2225fc/tools/metrics/histograms/one-pager.md
* https://sites.google.com/a/chromium.org/dev/updates/schemeful-same-site/testing-and-debugging-tips-for-schemeful-same-site#TOC-Using-Chrome-Histograms
* https://chromium.googlesource.com/chromium/src/+/lkgr/docs/speed/README.md
* https://developers.google.com/chart/interactive/docs/gallery/histogram
* https://wiki.mozilla.org/Performance/Telemetry

You can send metrics to server, see `https://github.com/chromium/chromium/blob/master/components/metrics/url_constants.cc`

First, inlude some files from `base/metrics`:

```cpp
#include <base/metrics/histogram.h>
#include <base/metrics/histogram_macros.h>
#include <base/metrics/statistics_recorder.h>
#include <base/metrics/user_metrics.h>
#include <base/metrics/user_metrics_action.h>
#include <base/metrics/histogram_functions.h>
#include <base/process/process_metrics.h>
```

There are three general types of histograms: enumerated histograms, count histograms (for arbitrary numbers), and sparse histograms (for anything when the precision is important over a wide range and/or the range is not possible to specify a priori).

See `https://chromium.googlesource.com/chromium/src/+/master/tools/metrics/histograms/README.md`

Examples:

```cpp
UMA_HISTOGRAM_BOOLEAN("App.BoolTest()", false);

UMA_HISTOGRAM_COUNTS_100("App.TestCounts", 11);

UMA_HISTOGRAM_LONG_TIMES("App.TimeNow()", ::base::TimeDelta::FromMinutes(5));

UMA_HISTOGRAM_ENUMERATION("Login", OFFLINE_AND_ONLINE, NUM_SUCCESS_REASONS);

::base::UmaHistogramMemoryLargeMB("HeapProfiler.Malloc", malloc_usage_mb);

UMA_HISTOGRAM_MEMORY_MB("SourceBufferStream.MemoryLimit", memory_limit_ / (1024 * 1024));

UMA_HISTOGRAM_COUNTS_1000("App.AppInitAttemts",
  appInitAttemtsCount);

SCOPED_UMA_HISTOGRAM_TIMER( /// \note measures up to 10 seconds
  "startPluginManager from " + FROM_HERE.ToString());

  // We scale up to the equivalent of 64 CPU cores fully loaded.
  // More than this does not really matter,
  // as we are already in a terrible place.
  const int kHistogramMin = 1;
  const int kHistogramMax = 6400;
  const int kHistogramBucketCount = 50;

  UMA_HISTOGRAM_CUSTOM_COUNTS(
      "App.AverageCPU", cpu_usage,
      kHistogramMin, kHistogramMax, kHistogramBucketCount);

  enum {
    HISTOGRAM_MIN_HTTP_RESPONSE_CODE = 100,
    HISTOGRAM_MAX_HTTP_RESPONSE_CODE = 599,
  };

  int MapHttpResponseCode(int code) {
    if (HISTOGRAM_MIN_HTTP_RESPONSE_CODE <= code &&
        code <= HISTOGRAM_MAX_HTTP_RESPONSE_CODE)
      return code;
    return 0;
  }

  std::vector<int> GetAllHttpResponseCodes() {
    std::vector<int> codes;
    codes.reserve(
        HISTOGRAM_MAX_HTTP_RESPONSE_CODE - HISTOGRAM_MIN_HTTP_RESPONSE_CODE + 2);
    codes.push_back(0);
    for (int i = HISTOGRAM_MIN_HTTP_RESPONSE_CODE;
         i <= HISTOGRAM_MAX_HTTP_RESPONSE_CODE; ++i)
      codes.push_back(i);
    return codes;
  }

  UMA_HISTOGRAM_CUSTOM_ENUMERATION("Net.HttpResponseCode",
                                   MapHttpResponseCode(response_code_),
                                   // Note the third argument is only
                                   // evaluated once, see macro
                                   // definition for details.
                                   GetAllHttpResponseCodes());

auto processMetrics
  = base::ProcessMetrics::CreateCurrentProcessMetrics();

{
  size_t malloc_usage =
      processMetrics->GetMallocUsage();

  VLOG(1)
    << "malloc_usage: "
    << malloc_usage;

  int malloc_usage_mb = static_cast<int>(malloc_usage >> 20);
  base::UmaHistogramMemoryLargeMB("App.Memory.HeapProfiler.Malloc",
                                malloc_usage_mb);
}
```

## Histogram Naming Convention

See https://chromium.googlesource.com/chromium/src/+/master/tools/metrics/histograms

Use TrackerArea.MetricName. For example:

Logging.CrashCounter
Network.TimeToDrop

## FAQ

Q. What should my histogram's |min| and |max| values be set at?
A. You should set the values to a range that covers the vast majority of samples
   that would appear in the field. Note that samples below the |min| will still
   be collected in the underflow bucket and samples above the |max| will end up
   in the overflow bucket. Also, the reported mean of the data will be correct
   regardless of the range.
Q. How many buckets should I use in my histogram?
A. You should allocate as many buckets as necessary to perform proper analysis
   on the collected data. Note, however, that the memory allocated in Chrome for
   each histogram is proportional to the number of buckets. Therefore, it is
   strongly recommended to keep this number low (e.g., 50 is normal, while 100
   is probably high).
Q. When should I use an enumeration (linear) histogram vs. a regular
   (exponential) histogram?
A. Enumeration histograms should really be used only for sampling enumerated
   events and, in some cases, percentages. Normally, you should use a regular
   histogram with exponential bucket layout that provides higher resolution at
   the low end of the range and lower resolution at the high end. Regular
   histograms are generally used for collecting performance data (e.g., timing,
   memory usage, power) as well as aggregated event counts.
