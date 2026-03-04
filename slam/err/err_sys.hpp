#ifndef SLAM_ERR_SYS_HPP
#define SLAM_ERR_SYS_HPP

#include "../ext/glad/glad.h"
#include "err.hpp"
#include <iostream>

namespace slam::err {
struct ErrorSystem : public Singleton<ErrorSystem> {
  ErrorSystem() = default;
  void ThrowError(const Error &error, bool print, const sString &file,
                  const sString &func);
  void ThrowErrorGL(const Error &error, bool print, const sString &file,
                    const sString &func);

  // This is a flag that determins what errors can have pop up windows.
  // Selected errors: `ErrorSeverity::ERROR` and `ErrorSeverity::FATAL`.
  sUint enablePopupOnErrors = ErrorSeverity::ES_ERROR | ErrorSeverity::ES_FATAL;

  // If this is true, warnings will not be printed to the console. If
  // `ErrorSeverity::WARNING` has been added to `enablePopupOnErrors` then a
  // window will still appear for warnings.
  bool silenceWarnings = false;

  const Error *lastError = nullptr;
  sString file;
  sString function;
};

#define THROW_ERROR(error)                                                     \
  ErrorSystem::Get().ThrowError(error, true, __FILE__, __FUNCTION__)

#define THROW_ERROR_GL(error)                                                  \
  ErrorSystem::Get().ThrowErrorGL(error, true, __FILE__, __FUNCTION__)

} // namespace slam::err

#endif