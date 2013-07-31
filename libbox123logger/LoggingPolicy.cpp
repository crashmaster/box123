#include <LoggingPolicy.hpp>

void LoggingPolicy::log(const std::string& message) const {
  std::printf("%s\n", message.c_str());
}
