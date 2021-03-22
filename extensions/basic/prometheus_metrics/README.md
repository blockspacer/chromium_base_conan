# About

See metric types in https://prometheus.io/docs/concepts/metric_types/

See comments in `metrics.hpp`

NOTE: Do not use a counter to expose a value that can decrease. For example, do not use a counter for the number of currently running processes; instead use a gauge.

## Example: Prometheus with Docker

Usage in code:

```
METRIC_DEFINE_entity(test_entity);

METRIC_DEFINE_counter(test_entity, http_requests_created,
                      "Number of created http requests.",
                      basis::MetricUnit::kConnections,
                      "Number of created http requests.");

METRIC_DEFINE_histogram_with_percentiles(test_entity, http_request_processing_duration,
                        "Histogram for http request processing durations",
                        basis::MetricUnit::kMilliseconds,
                        "Histogram for http request processing durations",
                        1000000, 3);

class http_worker
{
  // ...
  scoped_refptr<basis::Counter> connections_created_ = METRIC_http_requests_created.Instantiate(entity_);
  scoped_refptr<basis::Histogram> processing_duration_hist_ = METRIC_http_request_processing_duration.Instantiate(entity_);
  // ...
  void read_request()
  {
    // ...
    auto time_started = base::Time::Now();
    const int rndSleep = base::RandInt(1, 100);
    // artificial delay to imitate request processing
    base::PlatformThread::Sleep(base::TimeDelta::FromMilliseconds(rndSleep));
    // ...
    IncrementCounter(connections_created_);
    // ...
    auto passed = (base::Time::Now() - time_started).InMilliseconds();
    processing_duration_hist_->Increment(passed);
  }
};

NOTE: In production use `SCOPED_LATENCY_METRIC(processing_duration_hist_, basis::Auto::kTrue);` to measure execution time.

See code in `metrics_demotest.cc`

Now run Prometheus with Docker, commands below based on https://devconnected.com/how-to-install-prometheus-with-docker-on-ubuntu-18-04/

Note that under 'localhost:8070' we run compiled `metrics_demotest.cc`.

```bash
sudo useradd -rs /bin/false prometheus

sudo mkdir /etc/prometheus

cd /etc/prometheus/ && sudo touch prometheus.yml
sudo mkdir -p /data/prometheus

sudo chown prometheus:prometheus /data/prometheus /etc/prometheus/*

vi /etc/prometheus/prometheus.yml

scrape_configs:
  - job_name: 'prometheus'
    scrape_interval: 10s
    static_configs:
      - targets: ['localhost:9090']
  - job_name: 'node_exporter'
    scrape_interval: 10s
    static_configs:
      - targets: ['localhost:9100']
  - job_name: 'test_example'
    scrape_interval: 10s
    static_configs:
      - targets: ['localhost:8070']

sudo netstat -tulpn | grep 9090

cat /etc/passwd | grep prometheus
prometheus:x:999:999:/home/prometheus:/bin/false

# NOTE: CHANGE USER 999 TO YOUR USER

(docker stop prometheus_example || true)
(docker rm prometheus_example || true)

docker run -d -p 9090:9090 --user 999:999 \
--name prometheus_example \
--net=host \
-v /etc/prometheus/prometheus.yml:/etc/prometheus/prometheus.yml \
-v /data/prometheus:/data/prometheus \
prom/prometheus \
--config.file="/etc/prometheus/prometheus.yml" \
--storage.tsdb.path="/data/prometheus" \
--web.enable-admin-api

ps aux | grep prometheus

docker container ls -a

docker container logs -f --since 10m prometheus_example

curl http://localhost:9090/metrics

open in browser http://localhost:9090/targets

open in browser http://localhost:9090/graph?g0.expr=rate(node_cpu_seconds_total%7Bmode%3D%22system%22%7D%5B1m%5D)&g0.tab=0&g0.stacked=0&g0.range_input=1h

Metrics specific to the Node Exporter are prefixed with `node_`.

Here `rate(node_cpu_seconds_total{mode="system"}[1m])` is the average amount of CPU time spent in system mode, per second, over the last minute (in seconds)

sudo netstat -tulpn | grep 9100

sudo useradd -rs /bin/false node_exporter

cat /etc/passwd | grep node_exporter
prometheus:x:998:998:/home/node_exporter:/bin/false

# NOTE: CHANGE USER 999 TO YOUR USER

docker run -d -p 9100:9100 --user 998:998 \
--name node_exporter_example \
-v "/:/hostfs" \
--net="host" \
prom/node-exporter \
--path.rootfs=/hostfs

curl http://localhost:9100/metrics

open in browser http://localhost:9090/

Grafana supports querying Prometheus. See https://prometheus.io/docs/visualization/grafana/

sudo netstat -tulpn | grep 3000

docker run --name grafana_example -d -p 3000:3000 --net=host grafana/grafana

docker container logs -f --since 10m grafana_example

Open grafana in browser http://localhost:3000/

username:admin
password:admin

Add Prometheus as a datasource into grafana. Open http://localhost:3000/datasources

Click on the Grafana logo to open the sidebar.
Click on “Data Sources” in the sidebar.
Choose “Add New”.
Select “Prometheus” as the data source.
Set the Prometheus server URL (in our case: http://localhost:9090/)
Click “Add” to test the connection and to save the new data source.

See `Grafana Dashboards from Basic to Advanced` https://www.metricfire.com/blog/grafana-dashboards-from-basic-to-advanced/

Build basis tests and run test for metrics http server:

# Change `$HOME/basis` and `$HOME/chromium_base_conan` directory paths below
cd ~/basis
dir ~/chromium_base_conan
gdb -ex r -ex bt -ex q --args \
 $HOME/basis/build/Debug/tests/basis-tests/basis-metrics_demotest \
  --single-process-tests \
  --test-data-dir=$HOME/chromium_base_conan/tests/data/

Visit http://localhost:8070/metrics multiple times

Counter `http_requests_created` must increase with each page visit.

Histogram `http_request_processing_duration` must beasure elapsed time per each request.

To see graph in Prometheus open http://localhost:9090/graph?g0.expr=http_requests_created&g0.tab=0&g0.stacked=0&g0.range_input=30m

You can also create `Grafana Dashboard` that shows `http_requests_created` or `http_request_processing_duration`.

You can use admin api (requires `--web.enable-admin-api`) to delete old time series, see https://prometheus.io/docs/prometheus/latest/querying/api/

# delete alerts series
curl -g -XPOST 'http://localhost:9090/api/v1/admin/tsdb/delete_series?match[]={instance="localhost:8070"}' -v

# delete data from disk
curl -XPOST 'http://localhost:9090/api/v1/admin/tsdb/clean_tombstones' -v

Note: Prometheus provides a query language called PromQL.

See:

* https://prometheus.io/docs/prometheus/latest/querying/operators/
* https://www.innoq.com/en/blog/prometheus-counters/
* https://deploy.live/blog/today-i-learned-adding-labels-to-prometheus-queries/
* https://promlabs.com/promql-cheat-sheet/

In Prometheus, a metric is identified by the name of the metric AND the set of labeled dimensions.

Each time label changes, it is another metric and thus another graph.

In order to merge the metric, you have to compute a resulting metric without the label that changes.

Average is often a good candidate but doesn't matter if the metrics don't overlap:

avg without (i18n_time, string_label) (http_requests_created)
avg without (i18n_time, string_label) (http_request_processing_duration)

To get resulting metric only with label that does not change:

avg by (global_label) (http_request_processing_duration)

quantile(0.5, http_request_processing_duration)
```

## Example: Gauge using labels

Suppose you want to create Grafana dashboard that reports the latest version of our app i.e. "1.5.0-abcdefg".

Prometheus can store only numeric string in value, but can store arbitrary string in label.

```cpp
// BAD: arbitrary string in label
my_gauge->set_label("string_label", std::to_string(rndSleep) + "_bytes_used");
// GOOD: very limited set of strings in label
if (rndSleep > 10)
  my_gauge->set_label("string_label", "high_bytes_usage");
else
  my_gauge->set_label("string_label", "low_bytes_usage");
```

NOTE: Arbitrary string messages are usually bad idea, as each value will be a new time series which will run you into performance issues.

NOTE: Strings aren't metrics. If the number of states is bounded (not arbitrary!), then map states to some integer values.

Enter the label name as the legend using the {{[LABEL]}} notation (here {{string_label}}).

Activate the "instant" option.

See https://stackoverflow.com/a/57850590

You can also create Variable in New dashboard / Settings and use `label_values(fake_memory_usage, string_label)`

See:

* https://shubhamc183.medium.com/building-a-dynamic-grafana-dashboard-from-prometheus-f073faaa86be
* https://performance-monitoring-with-prometheus.readthedocs.io/en/latest/dashboard.html#add-panel
* https://banzaicloud.com/blog/grafana-templating/

# Performance metrics

To spot sources of performance degradation you can create metrics:

* Latencies
* Error rates

For latencies metrics use `SCOPED_LATENCY_METRIC(hist_name_, basis::Auto::kTrue);`

## WRITING CLIENT LIBRARIES

See:

* https://prometheus.io/docs/instrumenting/writing_clientlibs/
* https://prometheus.io/docs/prometheus/latest/querying/api/
* https://prometheus.io/docs/concepts/data_model/
* https://prometheus.io/docs/instrumenting/exposition_formats/#text-based-format

## The Prometheus Data Model

https://training.robustperception.io/courses/data-model/lectures/3157135

## Production in Kubernetes

You can deploy Prometheus and Grafana using Kubernetes.

See:

* https://blog.yugabyte.com/monitoring-yugabytedb-with-prometheus-and-grafana-in-kubernetes/
* https://github.com/yugabyte/yb-monitoring
