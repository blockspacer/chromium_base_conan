// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" basic, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.
//
// The following only applies to changes made to this file as part of YugaByte development.
//
// Portions Copyright (c) YugaByte, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
// in compliance with the License.  You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software distributed under the License
// is distributed on an "AS IS" basic, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
// or implied.  See the License for the specific language governing permissions and limitations
// under the License.
//

#include "basic/test/test_macros.h"
#include "basic/statistics/hdr_histogram.h"
#include "basic/prometheus_metrics/metrics.h"

#include "base/test/task_environment.h"
#include "base/strings/stringprintf.h"
#include "base/json/json_reader.h"
#include "base/json/json_writer.h"

#include "testing/gtest/include/gtest/gtest.h"
#include "testing/gmock/include/gmock/gmock.h"

#include <string>
#include <unordered_set>
#include <vector>

using std::string;
using std::unordered_set;
using std::vector;

namespace {

static int kMetricsRetirementAgeMs = 120 * 1000;

} // namespace

namespace basic {

METRIC_DEFINE_entity(test_entity);

class MetricsTest : public testing::Test {
 public:
  void SetUp() override {
    entity_ = METRIC_ENTITY_test_entity.Instantiate(&registry_, "my-test");
  }

 protected:
  template <class LagType>
  void DoLagTest(const MillisLagPrototype& metric) {
    scoped_refptr<LagType> lag = new LagType(&metric);
    ASSERT_EQ(metric.description(), lag->prototype()->description());
    base::PlatformThread::Sleep(base::TimeDelta::FromMilliseconds(500));
    // Internal timestamp is set to the time when the metric was created.
    // So this lag is measure of the time elapsed since the metric was
    // created and the check time.
    ASSERT_GE(lag->lag_ms(), 500);
    auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
    lag->UpdateTimestampInMilliseconds(now_ms);
    // Verify that the update happened correctly. The lag time should
    // be close to 0, but giving it extra time to account for slow
    // tests.
    ASSERT_LT(lag->lag_ms(), 200);
    // Set the timestamp to some time in the future to verify that the
    // metric can correctly deal with this case.
    lag->UpdateTimestampInMilliseconds(now_ms * 2);
    ASSERT_EQ(0, lag->lag_ms());
  }

  MetricRegistry registry_;
  scoped_refptr<MetricEntity> entity_;
  base::test::TaskEnvironment task_environment{
    base::test::TaskEnvironment::TimeSource::MOCK_TIME};
};

METRIC_DEFINE_counter(test_entity, reqs_pending, "Requests Pending", MetricUnit::kRequests,
                      "Number of requests pending");

TEST_F(MetricsTest, SimpleCounterTest) {
  scoped_refptr<Counter> requests =
    new Counter(&METRIC_reqs_pending);
  ASSERT_EQ("Number of requests pending", requests->prototype()->description());
  ASSERT_EQ(0, requests->value());
  requests->Increment();
  ASSERT_EQ(1, requests->value());
  requests->IncrementBy(2);
  ASSERT_EQ(3, requests->value());
}

METRIC_DEFINE_lag(test_entity, lag_simple, "Test MillisLag", "Test MillisLag Description");
TEST_F(MetricsTest, SimpleLagTest) {
  ASSERT_NO_FATAL_FAILURE(DoLagTest<MillisLag>(METRIC_lag_simple));
}

METRIC_DEFINE_lag(test_entity, atomic_lag_simple, "Test Atomic MillisLag",
                  "Test Atomic MillisLag Description");
TEST_F(MetricsTest, SimpleAtomicLagTest) {
  ASSERT_NO_FATAL_FAILURE(DoLagTest<AtomicMillisLag>(METRIC_atomic_lag_simple));
}

METRIC_DEFINE_gauge_uint64(test_entity, fake_memory_usage, "Memory Usage",
                           MetricUnit::kBytes, "Test Gauge 1");

TEST_F(MetricsTest, SimpleAtomicGaugeTest) {
  scoped_refptr<AtomicGauge<uint64_t> > mem_usage =
    METRIC_fake_memory_usage.Instantiate(entity_, 0);
  ASSERT_EQ(METRIC_fake_memory_usage.description(), mem_usage->prototype()->description());
  ASSERT_EQ(0, mem_usage->value());
  mem_usage->IncrementBy(7);
  ASSERT_EQ(7, mem_usage->value());
  mem_usage->set_value(5);
  ASSERT_EQ(5, mem_usage->value());
}

METRIC_DEFINE_gauge_int64(test_entity, test_func_gauge, "Test Gauge", MetricUnit::kBytes,
                          "Test Gauge 2");

static int64_t MyFunction(int* metric_val) {
  return (*metric_val)++;
}

TEST_F(MetricsTest, SimpleFunctionGaugeTest) {
  int metric_val = 1000;
  scoped_refptr<FunctionGauge<int64_t> > gauge =
    METRIC_test_func_gauge.InstantiateFunctionGauge(
      entity_, base::Bind(&MyFunction, base::Unretained(&metric_val)));

  ASSERT_EQ(1000, gauge->value());
  ASSERT_EQ(1001, gauge->value());

  gauge->DetachToCurrentValue();
  // After detaching, it should continue to return the same constant value.
  ASSERT_EQ(1002, gauge->value());
  ASSERT_EQ(1002, gauge->value());

  // Test resetting to a constant.
  gauge->DetachToConstant(2);
  ASSERT_EQ(2, gauge->value());
}

TEST_F(MetricsTest, AutoDetachToLastValue) {
  int metric_val = 1000;
  scoped_refptr<FunctionGauge<int64_t> > gauge =
    METRIC_test_func_gauge.InstantiateFunctionGauge(
        entity_, base::Bind(&MyFunction, base::Unretained(&metric_val)));

  ASSERT_EQ(1000, gauge->value());
  ASSERT_EQ(1001, gauge->value());
  {
    FunctionGaugeDetacher detacher;
    gauge->AutoDetachToLastValue(&detacher);
    ASSERT_EQ(1002, gauge->value());
    ASSERT_EQ(1003, gauge->value());
  }

  ASSERT_EQ(1004, gauge->value());
  ASSERT_EQ(1004, gauge->value());
}

TEST_F(MetricsTest, AutoDetachToConstant) {
  int metric_val = 1000;
  scoped_refptr<FunctionGauge<int64_t> > gauge =
    METRIC_test_func_gauge.InstantiateFunctionGauge(
        entity_, base::Bind(&MyFunction, base::Unretained(&metric_val)));

  ASSERT_EQ(1000, gauge->value());
  ASSERT_EQ(1001, gauge->value());
  {
    FunctionGaugeDetacher detacher;
    gauge->AutoDetach(&detacher, 12345);
    ASSERT_EQ(1002, gauge->value());
    ASSERT_EQ(1003, gauge->value());
  }

  ASSERT_EQ(12345, gauge->value());
}

METRIC_DEFINE_gauge_uint64(test_entity, counter_as_gauge, "Gauge exposed as Counter",
                           MetricUnit::kBytes, "Gauge exposed as Counter",
                           EXPOSE_AS_COUNTER);
TEST_F(MetricsTest, TEstExposeGaugeAsCounter) {
  ASSERT_EQ(MetricType::kCounter, METRIC_counter_as_gauge.type());
}

METRIC_DEFINE_histogram(test_entity, test_hist, "Test Histogram",
                        MetricUnit::kMilliseconds, "foo", 1000000, 3);

TEST_F(MetricsTest, SimpleHistogramTest) {
  scoped_refptr<Histogram> hist = METRIC_test_hist.Instantiate(entity_);
  hist->Increment(2);
  hist->IncrementBy(4, 1);
  ASSERT_EQ(2, hist->histogram_->MinValue());
  ASSERT_EQ(3, hist->histogram_->MeanValue());
  ASSERT_EQ(4, hist->histogram_->MaxValue());
  ASSERT_EQ(2, hist->histogram_->TotalCount());
  ASSERT_EQ(6, hist->histogram_->TotalSum());
  // TODO: Test coverage needs to be improved a lot.
}

TEST_F(MetricsTest, ResetHistogramTest) {
  scoped_refptr<Histogram> hist = METRIC_test_hist.Instantiate(entity_);
  for (int i = 1; i <= 100; i++) {
    hist->Increment(i);
  }
  EXPECT_EQ(5050, hist->histogram_->TotalSum());
  EXPECT_EQ(100, hist->histogram_->TotalCount());
  EXPECT_EQ(5050, hist->histogram_->CurrentSum());
  EXPECT_EQ(100, hist->histogram_->CurrentCount());

  EXPECT_EQ(1, hist->histogram_->MinValue());
  EXPECT_EQ(50.5, hist->histogram_->MeanValue());
  EXPECT_EQ(100, hist->histogram_->MaxValue());
  EXPECT_EQ(10, hist->histogram_->ValueAtPercentile(10));
  EXPECT_EQ(25, hist->histogram_->ValueAtPercentile(25));
  EXPECT_EQ(50, hist->histogram_->ValueAtPercentile(50));
  EXPECT_EQ(75, hist->histogram_->ValueAtPercentile(75));
  EXPECT_EQ(99, hist->histogram_->ValueAtPercentile(99));
  EXPECT_EQ(100, hist->histogram_->ValueAtPercentile(99.9));
  EXPECT_EQ(100, hist->histogram_->ValueAtPercentile(100));

  hist->histogram_->DumpHumanReadable(&LOG_STREAM(INFO));
  hist->histogram_->ResetPercentiles();
  hist->histogram_->DumpHumanReadable(&LOG_STREAM(INFO));

  EXPECT_EQ(5050, hist->histogram_->TotalSum());
  EXPECT_EQ(100, hist->histogram_->TotalCount());
  EXPECT_EQ(0, hist->histogram_->CurrentSum());
  EXPECT_EQ(0, hist->histogram_->CurrentCount());

  EXPECT_EQ(0, hist->histogram_->MinValue());
  EXPECT_EQ(0, hist->histogram_->MeanValue());
  EXPECT_EQ(0, hist->histogram_->MaxValue());
  EXPECT_EQ(0, hist->histogram_->ValueAtPercentile(10));
  EXPECT_EQ(0, hist->histogram_->ValueAtPercentile(25));
  EXPECT_EQ(0, hist->histogram_->ValueAtPercentile(50));
  EXPECT_EQ(0, hist->histogram_->ValueAtPercentile(75));
  EXPECT_EQ(0, hist->histogram_->ValueAtPercentile(99));
  EXPECT_EQ(0, hist->histogram_->ValueAtPercentile(99.9));
  EXPECT_EQ(0, hist->histogram_->ValueAtPercentile(100));
}

#if TODO
TEST_F(MetricsTest, JsonPrintTest) {
  scoped_refptr<Counter> bytes_seen = METRIC_reqs_pending.Instantiate(entity_);
  bytes_seen->Increment();
  entity_->SetAttribute("test_attr", "attr_val");

  // Generate the JSON.
  std::stringstream out;
  JsonWriter writer(&out, JsonWriter::PRETTY);
  ASSERT_OK(entity_->WriteAsJson(&writer, { "*" }, MetricJsonOptions()));

  // Now parse it back out.
  JsonReader reader(out.str());
  ASSERT_OK(reader.Init());

  vector<const rapidjson::Value*> metrics;
  ASSERT_OK(reader.ExtractObjectArray(reader.root(), "metrics", &metrics));
  ASSERT_EQ(1, metrics.size());
  string metric_name;
  ASSERT_OK(reader.ExtractString(metrics[0], "name", &metric_name));
  ASSERT_EQ("reqs_pending", metric_name);
  int64_t metric_value;
  ASSERT_OK(reader.ExtractInt64(metrics[0], "value", &metric_value));
  ASSERT_EQ(1L, metric_value);

  const rapidjson::Value* attributes;
  ASSERT_OK(reader.ExtractObject(reader.root(), "attributes", &attributes));
  string attr_value;
  ASSERT_OK(reader.ExtractString(attributes, "test_attr", &attr_value));
  ASSERT_EQ("attr_val", attr_value);

  // Verify that, if we filter for a metric that isn't in this entity, we get no result.
  out.str("");
  ASSERT_OK(entity_->WriteAsJson(&writer, { "not_a_matching_metric" }, MetricJsonOptions()));
  ASSERT_EQ("", out.str());
}
#endif

// Test that metrics are retired when they are no longer referenced.
TEST_F(MetricsTest, RetirementTest) {
  kMetricsRetirementAgeMs = 100;

  const string kMetricName = "foo";
  scoped_refptr<Counter> counter = METRIC_reqs_pending.Instantiate(entity_);
  ASSERT_EQ(1, entity_->UnsafeMetricsMapForTests().size());

  // Since we hold a reference to the counter, it should not get retired.
  entity_->RetireOldMetrics(kMetricsRetirementAgeMs);
  ASSERT_EQ(1, entity_->UnsafeMetricsMapForTests().size());

  // When we de-ref it, it should not get immediately retired, either, because
  // we keep retirable metrics around for some amount of time. We try retiring
  // a number of times to hit all the cases.
  counter = nullptr;
  for (int i = 0; i < 3; i++) {
    entity_->RetireOldMetrics(kMetricsRetirementAgeMs);
    ASSERT_EQ(1, entity_->UnsafeMetricsMapForTests().size());
  }

  // If we wait for longer than the retirement time, and call retire again, we'll
  // actually retire it.
  // base::PlatformThread::Sleep(base::TimeDelta::FromMilliseconds(kMetricsRetirementAgeMs * 1.5));
  task_environment.FastForwardBy(base::TimeDelta::FromMilliseconds(kMetricsRetirementAgeMs * 1.5));
  entity_->RetireOldMetrics(kMetricsRetirementAgeMs);
  ASSERT_EQ(0, entity_->UnsafeMetricsMapForTests().size());
}

TEST_F(MetricsTest, TestRetiringEntities) {
  ASSERT_EQ(1, registry_.num_entities());

  // Drop the reference to our entity.
  entity_.reset();

  // Retire metrics. Since there is nothing inside our entity, it should
  // retire immediately (no need to loop).
  registry_.RetireOldMetrics(kMetricsRetirementAgeMs);

  ASSERT_EQ(0, registry_.num_entities());
}

// Test that we can mark a metric to never be retired.
TEST_F(MetricsTest, NeverRetireTest) {
  entity_->NeverRetire(METRIC_test_hist.Instantiate(entity_));
  kMetricsRetirementAgeMs = 0;

  for (int i = 0; i < 3; i++) {
    entity_->RetireOldMetrics(kMetricsRetirementAgeMs);
    ASSERT_EQ(1, entity_->UnsafeMetricsMapForTests().size());
  }
}

TEST_F(MetricsTest, TestInstantiatingTwice) {
  // Test that re-instantiating the same entity ID returns the same object.
  scoped_refptr<MetricEntity> new_entity = METRIC_ENTITY_test_entity.Instantiate(
      &registry_, entity_->id());
  ASSERT_EQ(new_entity.get(), entity_.get());
}

TEST_F(MetricsTest, TestInstantiatingDifferentEntities) {
  scoped_refptr<MetricEntity> new_entity = METRIC_ENTITY_test_entity.Instantiate(
      &registry_, "some other ID");
  ASSERT_NE(new_entity.get(), entity_.get());
}

TEST_F(MetricsTest, TestPrometheusWriter) {
  scoped_refptr<Histogram> hist = METRIC_test_hist.Instantiate(entity_);
  entity_->NeverRetire(hist);
  for (int i = 1; i <= 100; i++) {
    hist->Increment(i);
  }
  EXPECT_EQ(5050, hist->histogram_->TotalSum());
  EXPECT_EQ(100, hist->histogram_->TotalCount());
  EXPECT_EQ(5050, hist->histogram_->CurrentSum());
  EXPECT_EQ(100, hist->histogram_->CurrentCount());

  EXPECT_EQ(1, hist->histogram_->MinValue());
  EXPECT_EQ(50.5, hist->histogram_->MeanValue());
  EXPECT_EQ(100, hist->histogram_->MaxValue());
  EXPECT_EQ(10, hist->histogram_->ValueAtPercentile(10));
  EXPECT_EQ(25, hist->histogram_->ValueAtPercentile(25));
  EXPECT_EQ(50, hist->histogram_->ValueAtPercentile(50));
  EXPECT_EQ(75, hist->histogram_->ValueAtPercentile(75));
  EXPECT_EQ(99, hist->histogram_->ValueAtPercentile(99));
  EXPECT_EQ(100, hist->histogram_->ValueAtPercentile(99.9));
  EXPECT_EQ(100, hist->histogram_->ValueAtPercentile(100));

  std::stringstream output;
  MetricPrometheusOptions opts;
  PrometheusWriter writer(&output);

  kMetricsRetirementAgeMs = 120 * 1000;

  ASSERT_OK(registry_.WriteForPrometheus(
    &writer, opts, kMetricsRetirementAgeMs))
    << "Couldn't write metrics for prometheus";
  task_environment.FastForwardUntilNoTasksRemain();

  SCOPED_TRACE(base::StringPrintf("PrometheusWriter output=%s", output.str().c_str()));

  ASSERT_STR_CONTAINS(output.str(), "test_hist_sum")
    << output.str();

  ASSERT_STR_CONTAINS(output.str(), "metric_id=\"my-test\"")
    << output.str();

  ASSERT_STR_CONTAINS(output.str(), "metric_type=\"test_entity\"")
    << output.str();

  ASSERT_STR_CONTAINS(output.str(), "exported_instance=\"DEFAULT_NODE_NAME\"")
    << output.str();

  ASSERT_STR_CONTAINS(output.str(), "test_hist_count")
    << output.str();

  ASSERT_STR_CONTAINS(output.str(), "5050")
    << output.str();

  ASSERT_STR_CONTAINS(output.str(), "100")
    << output.str();
}

} // namespace basic
