// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Audio/Audio.h>
#include <NovelRT/Experimental/Audio/Null/Audio.Null.h>

using namespace NovelRT;

namespace NovelRT::Experimental::Audio::Null
{
  NullChannel::NullChannel(int32_t channel)
  {
    channelId = channel,
    state = Audio::ChannelState::Unloaded;
  }

  bool NullChannel::Initialise()
  {
    return true;
  }

  void NullChannel::Update(float delta)
  {
    auto d = delta;
    d = d;
  }
}
