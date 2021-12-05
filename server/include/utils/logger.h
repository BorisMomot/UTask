//
// Created by boris on 05.12.2021.
//

#ifndef GTEST_DEMO_LOGGER_H
#define GTEST_DEMO_LOGGER_H
#include "aixlog.h"

class Logger {
public:
  Logger() {
    AixLog::Log::init<AixLog::SinkCout>(AixLog::Severity::trace);
    LOG(TRACE, "LOG_TAG") << "Logger with one cout log sink\n";
    LOG(DEBUG, "LOG_TAG") << "Logger with one cout log sink\n";
    LOG(INFO, "LOG_TAG") << "Logger with one cout log sink\n";

    AixLog::Filter filter;
    // log all lines with "trace" severity
    filter.add_filter("*:TRACE");
    // log all lines with tag "LOG_TAG"	with debug or higher severity
    filter.add_filter("LOG_TAG:DEBUG");
    auto sink_cout = std::make_shared<AixLog::SinkCout>(filter);
    AixLog::Filter filter_syslog;
    // log lines with tag "SYSLOG" to syslog
    filter_syslog.add_filter("SYSLOG:TRACE");
    auto sink_syslog = std::make_shared<AixLog::SinkNative>("aixlog example", filter_syslog);

    AixLog::Log::init({sink_cout, sink_syslog});
  }
};

#endif // GTEST_DEMO_LOGGER_H
