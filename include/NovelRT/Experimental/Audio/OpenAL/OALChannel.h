// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_OALCHANNEL_H
#define NOVELRT_OALCHANNEL_H

namespace NovelRT::Experimental::Audio::OpenAL
{
  class OALChannel : public Audio::IChannel
  {
    private:
      bool Initialise() final;
    public:
      void Update(float delta) final;
  };
}

#endif
