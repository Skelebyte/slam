#include "err.hpp"

using namespace slam;
using namespace slam::err;

Error::Error(const str &name, const str &desc, ErrorSeverity severity) {
  this->name = name;
  this->desc = desc;
  this->severity = severity;
}

Error Error::Derived(const str &newName, const str &newDesc) const {
  Error newError = *this;

  if (!newName.empty())
    newError.name = newName;
  if (!newDesc.empty())
    newError.desc = newDesc;

  return newError;
}

str Error::GetName() const { return name; }
str Error::GetDesc() const { return desc; }
ErrorSeverity Error::GetSeverity() const { return severity; }
