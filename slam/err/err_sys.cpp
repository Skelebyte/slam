#include "err_sys.hpp"
#include "../evt/evt_sys.hpp"

using namespace slam;
using namespace slam::err;
using namespace slam::evt;

void ErrorSystem::ThrowError(const Error &error, bool print,
                             const sString &file, const sString &func) {

  if (error.GetSeverity() == ErrorSeverity::ES_WARNING &&
      silenceWarnings == true)
    return;
  if (print == false)
    return;

  sString err_sev;
  switch (error.GetSeverity()) {
  case ErrorSeverity::ES_MSG:
    err_sev = "MSG";
    break;
  case ErrorSeverity::ES_WARNING:
    err_sev = "WARNING";
    break;
  case ErrorSeverity::ES_ERROR:
    err_sev = "ERROR";
    break;
  case ErrorSeverity::ES_FATAL:
    err_sev = "FATAL";
    break;
  default:
    err_sev = "MSG";
    break;
  }

  std::cout << "[" << err_sev << "] " << error.GetName() << ": "
            << error.GetDesc() << " (file: `" << file << "`, function: `"
            << func << "`)\n";

  this->file = file;
  function = func;

  lastError = &error;

  EventSystem::Get().on_error.Invoke();

  if (error.GetSeverity() == ErrorSeverity::ES_FATAL) {
    exit(ErrorSeverity::ES_FATAL);
  }
}

void ErrorSystem::ThrowErrorGL(const Error &error, bool print,
                               const sString &file, const sString &func) {
  sUint glErr = glGetError();
  Error err = error.Derived("", error.GetDesc() +
                                    " OpenGL error: " + std::to_string(glErr));
  if (glErr != GL_NO_ERROR) {
    ThrowError(err, print, file, func);
  }
}