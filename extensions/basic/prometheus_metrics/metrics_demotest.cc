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
#include "base/rand_util.h"
#include "base/i18n/time_formatting.h"
#include "base/strings/utf_string_conversions.h"

#include "testing/gtest/include/gtest/gtest.h"

#include <string>
#include <unordered_set>
#include <vector>

#include <boost/assign/list_of.hpp>

using std::string;
using std::unordered_set;
using std::vector;

namespace {

static int kMetricsRetirementAgeMs = 120 * 1000;

} // namespace

namespace basic {

METRIC_DEFINE_entity(test_entity);

} // namespace basic

#include <cstdlib>
#include <memory>
#include <stdexcept>

namespace detail {

struct static_pool
{
    std::size_t size_;
    std::size_t refs_ = 1;
    std::size_t count_ = 0;
    char* p_;

    char*
    end()
    {
        return reinterpret_cast<char*>(this + 1) + size_;
    }

    explicit
    static_pool(std::size_t size)
        : size_(size)
        , p_(reinterpret_cast<char*>(this + 1))
    {
    }

public:
    static
    static_pool&
    construct(std::size_t size)
    {
        auto p = new char[sizeof(static_pool) + size];
        return *(::new(p) static_pool{size});
    }

    static_pool&
    share()
    {
        ++refs_;
        return *this;
    }

    void
    destroy()
    {
        if(refs_--)
            return;
        this->~static_pool();
        delete[] reinterpret_cast<char*>(this);
    }

    void*
    alloc(std::size_t n)
    {
        auto last = p_ + n;
        if(last >= end())
            NOTREACHED();
        ++count_;
        auto p = p_;
        p_ = last;
        return p;
    }

    void
    dealloc()
    {
        if(--count_)
            return;
        p_ = reinterpret_cast<char*>(this + 1);
    }
};

} // detail

/** A non-thread-safe allocator optimized for @ref basic_fields.

    This allocator obtains memory from a pre-allocated memory block
    of a given size. It does nothing in deallocate until all
    previously allocated blocks are deallocated, upon which it
    resets the internal memory block for re-use.

    To use this allocator declare an instance persistent to the
    connection or session, and construct with the block size.
    A good rule of thumb is 20% more than the maximum allowed
    header size. For example if the application only allows up
    to an 8,000 byte header, the block size could be 9,600.

    Then, for every instance of `message` construct the header
    with a copy of the previously declared allocator instance.
*/
template<class T>
struct fields_alloc
{
    detail::static_pool* pool_;

public:
    using value_type = T;
    using is_always_equal = std::false_type;
    using pointer = T*;
    using reference = T&;
    using const_pointer = T const*;
    using const_reference = T const&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    template<class U>
    struct rebind
    {
        using other = fields_alloc<U>;
    };

#if defined(_GLIBCXX_USE_CXX11_ABI) && (_GLIBCXX_USE_CXX11_ABI == 0)
    // Workaround for g++
    // basic_string assumes that allocators are default-constructible
    // See: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=56437
    fields_alloc() = default;
#endif

    explicit
    fields_alloc(std::size_t size)
        : pool_(&detail::static_pool::construct(size))
    {
    }

    fields_alloc(fields_alloc const& other)
        : pool_(&other.pool_->share())
    {
    }

    template<class U>
    fields_alloc(fields_alloc<U> const& other)
        : pool_(&other.pool_->share())
    {
    }

    ~fields_alloc()
    {
        pool_->destroy();
    }

    value_type*
    allocate(size_type n)
    {
        return static_cast<value_type*>(
            pool_->alloc(n * sizeof(T)));
    }

    void
    deallocate(value_type*, size_type)
    {
        pool_->dealloc();
    }

#if defined(BOOST_LIBSTDCXX_VERSION) && BOOST_LIBSTDCXX_VERSION < 60000
    template<class U, class... Args>
    void
    construct(U* ptr, Args&&... args)
    {
        ::new(static_cast<void*>(ptr)) U(
            std::forward<Args>(args)...);
    }

    template<class U>
    void
    destroy(U* ptr)
    {
        ptr->~U();
    }
#endif

    template<class U>
    friend
    bool
    operator==(
        fields_alloc const& lhs,
        fields_alloc<U> const& rhs)
    {
        return &lhs.pool_ == &rhs.pool_;
    }

    template<class U>
    friend
    bool
    operator!=(
        fields_alloc const& lhs,
        fields_alloc<U> const& rhs)
    {
        return ! (lhs == rhs);
    }
};

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>
#include <memory>
#include <string>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

// Return a reasonable mime type based on the extension of a file.
beast::string_view
mime_type(beast::string_view path)
{
    using beast::iequals;
    auto const ext = [&path]
    {
        auto const pos = path.rfind(".");
        if(pos == beast::string_view::npos)
            return beast::string_view{};
        return path.substr(pos);
    }();
    if(iequals(ext, ".htm"))  return "text/html";
    if(iequals(ext, ".html")) return "text/html";
    if(iequals(ext, ".php"))  return "text/html";
    if(iequals(ext, ".css"))  return "text/css";
    if(iequals(ext, ".txt"))  return "text/plain";
    if(iequals(ext, ".js"))   return "application/javascript";
    if(iequals(ext, ".json")) return "application/json";
    if(iequals(ext, ".xml"))  return "application/xml";
    if(iequals(ext, ".swf"))  return "application/x-shockwave-flash";
    if(iequals(ext, ".flv"))  return "video/x-flv";
    if(iequals(ext, ".png"))  return "image/png";
    if(iequals(ext, ".jpe"))  return "image/jpeg";
    if(iequals(ext, ".jpeg")) return "image/jpeg";
    if(iequals(ext, ".jpg"))  return "image/jpeg";
    if(iequals(ext, ".gif"))  return "image/gif";
    if(iequals(ext, ".bmp"))  return "image/bmp";
    if(iequals(ext, ".ico"))  return "image/vnd.microsoft.icon";
    if(iequals(ext, ".tiff")) return "image/tiff";
    if(iequals(ext, ".tif"))  return "image/tiff";
    if(iequals(ext, ".svg"))  return "image/svg+xml";
    if(iequals(ext, ".svgz")) return "image/svg+xml";
    return "application/text";
}

METRIC_DEFINE_counter(test_entity, http_requests_created,
                      "Number of created http requests.",
                      basic::MetricUnit::kConnections,
                      "Number of created http requests.");

METRIC_DEFINE_histogram_with_percentiles(test_entity, http_request_processing_duration,
                        "Histogram for http request processing durations",
                        basic::MetricUnit::kMilliseconds,
                        "Histogram for http request processing durations",
                        1000000, 3);

#if TODO
METRIC_DEFINE_gauge_string(test_entity, fake_memory_usage, "Memory Usage",
                           basic::MetricUnit::kBytes, "Test Gauge 1");
#endif

METRIC_DEFINE_gauge_int64(test_entity, test_func_gauge, "Test Gauge",
                          basic::MetricUnit::kBytes, "Test Gauge 2");

class http_worker
{
public:
    http_worker(http_worker const&) = delete;
    http_worker& operator=(http_worker const&) = delete;

    http_worker(tcp::acceptor& acceptor, const std::string& doc_root,
                basic::MetricRegistry& registry, scoped_refptr<basic::MetricEntity> entity) :
        acceptor_(acceptor),
        doc_root_(doc_root),
        registry_(registry),
        entity_(entity)
    {
    }

    void start()
    {
        accept();
        check_deadline();
    }

private:
    using alloc_t = fields_alloc<char>;
    //using request_body_t = http::basic_dynamic_body<beast::flat_static_buffer<1024 * 1024>>;
    using request_body_t = http::string_body;

    // The acceptor used to listen for incoming connections.
    tcp::acceptor& acceptor_;

    // The path to the root of the document directory.
    std::string doc_root_;

    basic::MetricRegistry& registry_;

    scoped_refptr<basic::MetricEntity> entity_;

    // The socket for the currently connected client.
    tcp::socket socket_{acceptor_.get_executor()};

    // The buffer for performing reads
    beast::flat_static_buffer<8192> buffer_;

    // The allocator used for the fields in the request and reply.
    alloc_t alloc_{8192};

    // The parser for reading the requests
    boost::optional<http::request_parser<request_body_t, alloc_t>> parser_;

    // The timer putting a time limit on requests.
    net::steady_timer request_deadline_{
        acceptor_.get_executor(), (std::chrono::steady_clock::time_point::max)()};

    scoped_refptr<basic::Counter> connections_created_
      = METRIC_http_requests_created.Instantiate(entity_);

    scoped_refptr<basic::Histogram> processing_duration_hist_
      = METRIC_http_request_processing_duration.Instantiate(entity_);

    scoped_refptr<basic::AtomicGauge<int64_t> > test_func_usage =
      METRIC_test_func_gauge.Instantiate(entity_, 0);

#if TODO
    scoped_refptr<basic::StringGauge > mem_usage =
      METRIC_fake_memory_usage.InstantiateStringGauge(entity_, "123");
#endif

    // The string-based response message.
    boost::optional<http::response<http::string_body, http::basic_fields<alloc_t>>> string_response_;

    // The string-based response serializer.
    boost::optional<http::response_serializer<http::string_body, http::basic_fields<alloc_t>>> string_serializer_;

    // The file-based response message.
    boost::optional<http::response<http::file_body, http::basic_fields<alloc_t>>> file_response_;

    // The file-based response serializer.
    boost::optional<http::response_serializer<http::file_body, http::basic_fields<alloc_t>>> file_serializer_;

    void accept()
    {
        // Clean up any previous connection.
        beast::error_code ec;
        socket_.close(ec);
        buffer_.consume(buffer_.size());

        acceptor_.async_accept(
            socket_,
            [this](beast::error_code ec)
            {
                if (ec)
                {
                    accept();
                }
                else
                {
                    // Request must be fully processed within 60 seconds.
                    request_deadline_.expires_after(
                        std::chrono::seconds(60));

                    read_request();
                }
            });
    }

    void read_request()
    {
        // On each read the parser needs to be destroyed and
        // recreated. We store it in a boost::optional to
        // achieve that.
        //
        // Arguments passed to the parser constructor are
        // forwarded to the message object. A single argument
        // is forwarded to the body constructor.
        //
        // We construct the dynamic body with a 1MB limit
        // to prevent vulnerability to buffer attacks.
        //
        parser_.emplace(
            std::piecewise_construct,
            std::make_tuple(),
            std::make_tuple(alloc_));

        http::async_read(
            socket_,
            buffer_,
            *parser_,
            [this](beast::error_code ec, std::size_t)
            {
                if (ec)
                    accept();
                else
                    process_request(parser_->get());
            });
    }

    void process_request(http::request<request_body_t, http::basic_fields<alloc_t>> const& req)
    {
        auto time_started = base::Time::Now();

        const int rndSleep = base::RandInt(1, 100);

        const std::string formatted_time
          = base::UTF16ToASCII(base::TimeFormatWithPattern(time_started, "MMMMdjmmss"));

        test_func_usage->set_value(rndSleep);
        test_func_usage->set_label("other_label", "other_label_text");
        /// \note Arbitrary string messages are usually bad idea,
        /// as each value will be a new time series which will run you into performance issues.
        test_func_usage->set_label("string_label", std::to_string(rndSleep) + "_x");
        /// \note Arbitrary string messages are usually bad idea,
        /// as each value will be a new time series which will run you into performance issues.
        test_func_usage->set_label("i18n_time", formatted_time);

#if TODO
        mem_usage->set_value(std::to_string(rndSleep));
        mem_usage->set_label("string_label", std::to_string(rndSleep) + "_bytes_used");
#endif

        // artificial delay to imitate request processing
        base::PlatformThread::Sleep(base::TimeDelta::FromMilliseconds(rndSleep));

        IncrementCounter(connections_created_);
        connections_created_->set_label("other_label", "other_label_text");
        /// \note Arbitrary string messages are usually bad idea,
        /// as each value will be a new time series which will run you into performance issues.
        connections_created_->set_label("string_label", std::to_string(rndSleep) + "_y");
        /// \note Arbitrary string messages are usually bad idea,
        /// as each value will be a new time series which will run you into performance issues.
        connections_created_->set_label("i18n_time", formatted_time);

        auto passed = (base::Time::Now() - time_started).InMilliseconds();

        /// \note use in production `SCOPED_LATENCY_METRIC` like so:
        /// SCOPED_LATENCY_METRIC(processing_duration_hist_, basic::Auto::kTrue);
        processing_duration_hist_->Increment(passed);
        processing_duration_hist_->set_label("other_label", "other_label_text");
        /// \note Arbitrary string messages are usually bad idea,
        /// as each value will be a new time series which will run you into performance issues.
        processing_duration_hist_->set_label("string_label", std::to_string(rndSleep) + "_z");
        /// \note Arbitrary string messages are usually bad idea,
        /// as each value will be a new time series which will run you into performance issues.
        processing_duration_hist_->set_label("i18n_time", formatted_time);

        switch (req.method())
        {
            case http::verb::get: {
                std::stringstream output;
                basic::MetricPrometheusOptions opts;
                opts.metricsNodeName = "DEMO_NODE_NAME";
                opts.exposeMetricHistogramPercentiles = true;
                basic::PrometheusWriter writer(&output);

                kMetricsRetirementAgeMs = 120 * 1000;

                ASSERT_OK(registry_.WriteForPrometheus(
                  &writer, opts, kMetricsRetirementAgeMs))
                  << "Couldn't write metrics for prometheus";

                send_text(output.str());
                break;
            }

            default: {
                // We return responses indicating an error if
                // we do not recognize the request method.
                send_bad_response(
                    http::status::bad_request,
                    "Invalid request-method '" + std::string(req.method_string()) + "'\r\n");
                break;
            }
        }
    }

    void send_bad_response(
        http::status status,
        std::string const& error)
    {
        string_response_.emplace(
            std::piecewise_construct,
            std::make_tuple(),
            std::make_tuple(alloc_));

        string_response_->result(status);
        string_response_->keep_alive(false);
        string_response_->set(http::field::server, "Beast");
        string_response_->set(http::field::content_type, "text/plain");
        string_response_->body() = error;
        string_response_->prepare_payload();

        string_serializer_.emplace(*string_response_);

        http::async_write(
            socket_,
            *string_serializer_,
            [this](beast::error_code ec, std::size_t)
            {
                socket_.shutdown(tcp::socket::shutdown_send, ec);
                string_serializer_.reset();
                string_response_.reset();
                accept();
            });
    }

    void send_text(std::string const& text)
    {
        string_response_.emplace(
            std::piecewise_construct,
            std::make_tuple(),
            std::make_tuple(alloc_));

        string_response_->result(http::status::ok);
        string_response_->keep_alive(false);
        string_response_->set(http::field::server, "Beast");
        string_response_->set(http::field::content_type, "text/plain");
        string_response_->body() = text;
        string_response_->prepare_payload();

        string_serializer_.emplace(*string_response_);

        http::async_write(
            socket_,
            *string_serializer_,
            [this](beast::error_code ec, std::size_t)
            {
                socket_.shutdown(tcp::socket::shutdown_send, ec);
                string_serializer_.reset();
                string_response_.reset();
                accept();
            });
    }

    void check_deadline()
    {
        // The deadline may have moved, so check it has really passed.
        if (request_deadline_.expiry() <= std::chrono::steady_clock::now())
        {
            // Close socket to cancel any outstanding operation.
            beast::error_code ec;
            socket_.close();

            // Sleep indefinitely until we're given a new deadline.
            request_deadline_.expires_at(
                std::chrono::steady_clock::time_point::max());
        }

        request_deadline_.async_wait(
            [this](beast::error_code)
            {
                check_deadline();
            });
    }
};


#include <exception>

namespace boost {

#ifdef BOOST_NO_EXCEPTIONS
// see https://stackoverflow.com/a/33691561
void throw_exception(const std::exception& ex)
{
  NOTREACHED()
    << "boost thrown exception: "
    << ex.what();
  /// \note application will exit, without returning.
  exit(0);
}
#endif // BOOST_NO_EXCEPTIONS

} // namespace boost

namespace basic {

class MetricsExampleServer : public testing::Test {
 public:
  void SetUp() override {
    entity_ = METRIC_ENTITY_test_entity.Instantiate(&registry_, "my-test");
    entity_->set_label("global_label", "global_label_text");
  }

 protected:
  MetricRegistry registry_;
  scoped_refptr<MetricEntity> entity_;
  base::test::TaskEnvironment task_environment;
};

TEST_F(MetricsExampleServer, ExamplePrometheusWebEndpoint) {
  auto const address = boost::asio::ip::make_address("0.0.0.0");
  unsigned short port = 8070;
  std::string doc_root = ".";
  int num_workers = 1;
  bool spin = false;

  boost::asio::io_context ioc{1};
  tcp::acceptor acceptor{ioc, {address, port}};

  std::list<http_worker> workers;
  for (int i = 0; i < num_workers; ++i)
  {
      workers.emplace_back(acceptor, doc_root, registry_, entity_);
      workers.back().start();
  }

  if (spin)
    for (;;) ioc.poll();
  else
    ioc.run();
}

} // namespace basic
