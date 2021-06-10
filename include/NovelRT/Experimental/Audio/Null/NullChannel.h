// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_NULLCHANNEL_H
#define NOVELRT_NULLCHANNEL_H

namespace NovelRT::Experimental::Audio::Null
{
  class NullChannel : public Audio::IChannel
  {
    private:
      bool Initialise() final;

    public:
      NullChannel(int32_t channel);
      void Update(float delta) final;
  };
}

#endif  //NOVELRT_NULLCHANNEL_H
