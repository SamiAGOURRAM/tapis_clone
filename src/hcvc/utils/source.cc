//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "hcvc/utils//source.hh"

#include <fstream>
#include <utility>

namespace hcvc {

  //*-- Source
  Source::~Source() = default;

  //*-- FileSource
  FileSource::FileSource(std::string path)
      : _path(std::move(path)) {
    std::fstream stream(_path);
    _content = std::string(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());
  }

  FileSource::~FileSource() = default;

  const std::string &FileSource::content() const {
    return _content;
  }

  const std::string &FileSource::path() const {
    return _path;
  }

}
