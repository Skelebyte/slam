#include <string>
#define GLAD_GL_IMPLEMENTATION
#include "common.hpp"

using namespace slam;

str String::From(int32 value) { return std::to_string(value); }

str String::From(float64 value) { return std::to_string(value); }

str String::From(float32 value) { return std::to_string(value); }

str String::From(char value) { return std::to_string(value); }

str String::From(char *value) { return str(value); }