// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#include <string>

#ifndef NOVELRT_IAUDIODRIVER_H
#define NOVELRT_IAUDIODRIVER_H

namespace NovelRT::Experimental::Audio
{
  class IAudioDriver
  {
    public:
      virtual bool Initialise() = 0;
      virtual void Update(float delta) = 0;
      virtual int LoadSound(std::string& fileName) = 0;
  };
}

#endif
