#include <string>
#define GLAD_GL_IMPLEMENTATION
#include "common.hpp"

using namespace slam;

str ToStr(int value) { return std::to_string(value); }

str ToStr(double value) { return std::to_string(value); }

str ToStr(float value) { return std::to_string(value); }

str ToStr(char value) { return std::to_string(value); }

str ToStr(char *value) { return str(value); }