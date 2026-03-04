#include "gltf_loader.hpp"

using namespace nlohmann;
using namespace slam::util;
using namespace slam::err;
using namespace slam;

void Loader::Load(const sString &path) {
  if (File::Exists(path) == false) {
    THROW_ERROR(ERROR.Derived("", "File " + path + " does not exist!"));
    return;
  }

  sString content = File::Read(path);

  json json_data = json::parse(content);

  sString bytesText;
  sString uri = json_data["buffers"][0]["uri"];

  sString fileString = sString(path);

  sString fileDirectory =
      fileString.substr(0, fileString.find_last_of('/') + 1);
  bytesText = File::Read(fileDirectory + uri);

  std::vector<sUchar> data(bytesText.begin(), bytesText.end());
}