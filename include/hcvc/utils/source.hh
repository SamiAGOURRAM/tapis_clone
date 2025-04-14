//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <string>

namespace hcvc {

  //*-- Source
  class Source {
  public:
    virtual ~Source();

    //*- properties

    virtual const std::string &content() const = 0;

    virtual const std::string &path() const = 0;
  };

  //*-- FileSource
  class FileSource: public Source {
  public:
    FileSource(std::string path);

    ~FileSource() override;

    //*- properties

    const std::string &content() const override;

    const std::string &path() const override;

  private:
    std::string _path;
    std::string _content;
  };

}
