#ifndef __LOGGING_POLICY_HPP__
#define __LOGGING_POLICY_HPP__

#include <cstdio>
#include <string>


class LoggingPolicy {
  protected:
    void log(const std::string& message) const;
};

#endif
