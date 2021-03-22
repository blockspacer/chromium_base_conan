# About

Place code that computes or updates statistics in `/statistics/`.

Note code that computes function execution times can also be found at `/base/metrics/`, `/base/trace_event/` etc.

## TIPS AND TRICKS

* Never consider the average as “the” value to pay attention to, since it can be deceiving, as it often hides important information.

* Consider the standard deviation to know just how useful the average is, the higher the standard deviation, the less meaningful it is.

* Observe the percentile values and define acceptance criteria based on that, keeping in mind that if you select the 90th percentile, you’re basically saying, “I don’t care if 10% of my users experience bad response times”.

## How NOT to Measure Latency

Latency is defined as the time it took one operation to happen.

Describe the complete distribution of latencies.

Latency almost never follows a normal, Gaussian, or Poisson distribution, so looking at averages, medians, and even standard deviations is useless.

Simply looking at the 95th or even 99th percentile is not sufficient because tail latency matters.

Take care of server freeze (lag) from clients side of view:

If server freezes and you measure (on server) only time between recieving response (response may be not recieved in proper time due to freeze) and sending answer, than freeze may be not detected or detected only for few requests (while freeze may affect many requests).

i.e. you can send per-request-timestamp from client to calculate real time that client had to wait (note that some clients may send wrong data on purpose, so use load tests that can simulate production workload).

Latency is not service time, so if you plot your data with coordinated omission, there’s often a quick, high rise in the curve.

Run a “CTRL+Z” test to see if you have `coordinated omission` problem.

There is no single metric which defines the behavior of latency, so pair latency information with other relevant data that may affect it (load, up-time, etc.).

Make sure you have no tooling problem:

* Many of the tools we use do not do a good job of capturing and representing latency data.
* Most monitoring systems stop at the 95th or 99th percentile.
* The data collected by most monitoring systems is usually summarized in small, five or ten second windows.

You can use HdrHistogram for latency (for example, hdrhistogram.github.io/HdrHistogram/). Make sure tool supports value recording times as low as few nanoseconds.

Instead of capturing a count and a sum of all latency recorded to then calculate a mean latency, you can capture latency values and assign them to a bucket.

See for details:

* https://bravenewgeek.com/everything-you-know-about-latency-is-wrong/
* https://leecampbell.com/2016/03/18/measuing-latency-with-hdrhistogram/
* http://psy-lob-saw.blogspot.com/2015/02/hdrhistogram-better-latency-capture.html
* https://medium.com/expedia-group-tech/your-latency-metrics-could-be-misleading-you-how-hdrhistogram-can-help-9d545b598374
* https://youtu.be/lJ8ydIuPFeU

## Do not forget about data size if you need to compute valid statistics

The easiest way to avoid too much data is to throw data away.

Too little data and you might as well have not bothered.

Or worse, you make an uninformed decision that takes your service down with it.

Then again, too much data can take down a service.

You also need to consider the resources required to manage excess data.

## Make sure you use informative statistics

The mean and variance have two advantages: easy implementation and broad usage.

In reality, that familiarity leads to damaging assumptions that ignore specifics like outliers.

An outlier is any data point distant from the rest of the distribution.

“Outlier” may sound remote and improbable, but they are everywhere, making moment-based statistics uninformative and even dangerous.

Outliers often represent the most critical data for a troubleshooting engineer.

The percentile is typically used to establish acceptance criteria, indicating that 90% of the sample should be below a certain value.

Percentile can be used to rule out outliers.

For example, the 90th percentile (abbreviated as p90) indicates that 90% of the sample is below that value and the rest of the values (that is, the other 10%) are above it.

## Statistics for Software

Statistics can answer frequently asked questions: “How fast?” and “How reliable?”.

Mean — The central tendency of the data

Variance — The looseness of the grouping around the mean

Skewness — The symmetry or bias toward one end of the scale

Kurtosis — The amount of data in “the wings” of the set

See for details:

* https://medium.com/paypal-engineering/statistics-for-software-e395ca08005d
* https://courses.lumenlearning.com/introstats1/
* https://www.elastic.co/blog/averages-can-dangerous-use-percentile
* https://www.dynatrace.com/news/blog/why-averages-suck-and-percentiles-are-great/
* https://www.dynatrace.com/support/help/how-to-use-dynatrace/problem-detection-and-analysis/problem-analysis/percentiles-for-analyzing-performance/
* https://dzone.com/articles/3-performance-testing-metrics-every-tester-should
* https://bravenewgeek.com/everything-you-know-about-latency-is-wrong/
* https://www.splunk.com/en_us/blog/it/practical-introduction-metrics-monitoring-getting-value-data-analytics.html
* https://www.sisense.com/blog/top-5-statistical-techniques-in-python/

