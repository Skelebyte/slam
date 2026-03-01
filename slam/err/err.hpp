#ifndef SLAM_ERR_HPP
#define SLAM_ERR_HPP

#include "../common.hpp"
#include <string>

namespace slam::err {

enum ErrorSeverity { ES_MSG = 0, ES_WARNING = 1, ES_ERROR = 2, ES_FATAL = 3 };

struct Error {
  Error() = default;
  Error(const sString &name, const sString &desc, ErrorSeverity severity);
  Error Derived(const sString &newName = "", const sString &newDesc = "") const;
  sString GetName() const;
  sString GetDesc() const;
  ErrorSeverity GetSeverity() const;

private:
  sString name;
  sString desc;
  ErrorSeverity severity;
};

const Error MSG = Error("MSG", "This is a message!", ErrorSeverity::ES_MSG);
const Error WARNING =
    Error("WARNING", "This is a warning!", ErrorSeverity::ES_WARNING);
const Error ERROR =
    Error("ERROR", "This is an error!", ErrorSeverity::ES_ERROR);
const Error FATAL = Error("ERROR", "This is fatal!", ErrorSeverity::ES_FATAL);

} // namespace slam::err

#endif