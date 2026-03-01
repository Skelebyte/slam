#include "file.hpp"

using namespace slam;
using namespace slam::util;
using namespace slam::err;

sString File::Read(sString path) {
  if (File::Exists(path) == false) {
    THROW_ERROR(ERROR.Derived("", "File " + path + " does not exist!"));
    return "";
  }

  std::ifstream file;

  file.open(path, std::ios::binary | std::ios::ate);

  if (file.fail()) {
    THROW_ERROR(ERROR.Derived("", "Failed to open file " + path + "."));
    return "";
  }

  std::streamsize size = (std::streamsize)file.tellg();
  file.seekg(0, std::ios::beg);

  char *buffer = new char[size + 1];
  if (!file.read(buffer, size)) {
    THROW_ERROR(ERROR.Derived("", "Failed to read file " + path + "."));
    delete[] buffer;
    return "";
  }

  buffer[size] = '\0';

  file.close();

  sString data = buffer;
  delete[] buffer;

  return data;
}

void Write(sString path, sString content, bool overwrite = false) {
  std::ofstream file;

  if (overwrite) {
    file.open(path, std::ios::trunc);
  } else {
    file.open(path, std::ios::app);
  }

  file << content << std::endl;
  file.close();
}

bool File::Exists(sString path) { return std::filesystem::exists(path); }