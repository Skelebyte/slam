#include "err.hpp"

using namespace slam;
using namespace slam::err;

Error::Error(const sString &name, const sString &desc, ErrorSeverity severity) {
  this->name = name;
  this->desc = desc;
  this->severity = severity;
}

Error Error::Derived(const sString &newName, const sString &newDesc) const {
  Error newError = *this;

  if (!newName.empty())
    newError.name = newName;
  if (!newDesc.empty())
    newError.desc = newDesc;

  return newError;
}

sString Error::GetName() const { return name; }
sString Error::GetDesc() const { return desc; }
ErrorSeverity Error::GetSeverity() const { return severity; }
