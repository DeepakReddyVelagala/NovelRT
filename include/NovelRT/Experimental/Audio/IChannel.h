// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ICHANNEL_H
#define NOVELRT_ICHANNEL_H

namespace NovelRT::Experimental::Audio
{
  class IChannel
  {
    private:
      virtual bool Initialise() = 0;
    protected:
      int32_t channelId;
      ChannelState state;
    public:
      virtual void Update(float delta) = 0;
  };
}

#endif
