// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#include <cstdint>
#include "SoundState.h"

#ifndef NOVELRT_ICHANNEL_H
#define NOVELRT_ICHANNEL_H

namespace NovelRT::Experimental::Audio
{
  class IChannel
  {
    public:
      int32_t channelId;
      ChannelState state;

      virtual bool Initialise() = 0;
      virtual void Update(float delta) = 0;
  };
}

#endif
