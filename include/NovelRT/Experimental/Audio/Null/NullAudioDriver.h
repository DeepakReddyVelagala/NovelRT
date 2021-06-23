// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_NullAUDIODRIVER_H
#define NOVELRT_NullAUDIODRIVER_H

namespace NovelRT::Experimental::Audio::Null
{
  class NullAudioDriver : public Audio::IAudioDriver
  {
    private:
      const int32_t _maxChannels = 255;
      const size_t _bufferSize = 2048;
      std::mutex _mutex;
      std::map<int32_t, int32_t> _soundToChannelMap;

      NullSound* CreateSound(SoundWave& sound);
      void LoadSoundInternal(int32_t soundId);

    public:
      NullAudioDriver();
      ~NullAudioDriver() final;
      bool Initialise();
      void Update(float delta);
      int32_t PlaySound(int32_t soundId, float volume) final;
      int32_t GetNextChannelId() final;
      void LoadSound(int32_t soundId) final;
      int32_t RegisterSound(SoundWave& sound) final;
      bool SoundIsLoaded(int32_t soundId) final;
  };
}

#endif
