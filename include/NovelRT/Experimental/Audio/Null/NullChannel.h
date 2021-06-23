// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_NULLCHANNEL_H
#define NOVELRT_NULLCHANNEL_H

namespace NovelRT::Experimental::Audio::Null
{
  class NullChannel : public Audio::IChannel
  {
    private:
      void LoadSound(int32_t soundId);
    public:
      NullChannel(NullAudioDriver* driver, int32_t soundId, SoundWave* wave, float volume);
      void Update(float delta) final;
      bool IsStopped() final;
      bool IsPlaying() final;
      float GetVolume() final;
      void SetVolume(float vol) final;

      ~NullChannel() final;

  };
}

#endif  //NOVELRT_NULLCHANNEL_H
