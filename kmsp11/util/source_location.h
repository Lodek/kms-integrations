#ifndef KMSP11_UTIL_SOURCE_LOCATION_H_
#define KMSP11_UTIL_SOURCE_LOCATION_H_

#include <string>
#include <vector>

#include "absl/strings/str_cat.h"
#include "absl/strings/str_split.h"

namespace kmsp11 {

// Class representing a specific location in the source code of a program.
//
// Note to maintainers: Abseil is in the process of releasing something like
// this publicly (see go/absl_source_location_review and
// go/source_location_lsc). Once that is done, we should move to it, and delete
// this.
class SourceLocation {
 public:
  constexpr SourceLocation(uint32_t line, const char* file_name)
      : line_(line), file_name_(file_name) {}

  uint32_t line() const { return line_; }
  std::string file_name() const { return file_name_; }

  std::string ToString() const {
    std::vector<std::string> path_elems = absl::StrSplit(file_name_, '/');
    return absl::StrCat(path_elems.back(), ":", line_);
  }

 private:
  const uint32_t line_;
  const char* file_name_;
};

}  // namespace kmsp11

// A macro for retrieving a SourceLocation object containing the curent file
// path and line number.
#define SOURCE_LOCATION ::kmsp11::SourceLocation(__LINE__, __FILE__)

#endif  // KMSP11_UTIL_SOURCE_LOCATION_H_
