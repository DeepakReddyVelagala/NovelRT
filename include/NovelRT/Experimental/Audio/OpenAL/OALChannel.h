// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#include <cstdint>
#include "..\IChannel.h"

#ifndef NOVELRT_OALCHANNEL_H
#define NOVELRT_OALCHANNEL_H

namespace NovelRT::Experimental::Audio
{
  class OALChannel : public IChannel
  {
    public:
      bool Initialise();
      void Update(float delta);
  };
}

#endif
