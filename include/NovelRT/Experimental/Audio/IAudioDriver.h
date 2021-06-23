// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_IAUDIODRIVER_H
#define NOVELRT_IAUDIODRIVER_H

namespace NovelRT::Experimental::Audio
{
  class IAudioDriver
  {
    protected:
      LoggingService _logger;
      int32_t _nextChannelId;
      int32_t _nextSoundId;
    public:

      std::map<int32_t, SoundWave> soundMap;
      std::map<int32_t, Audio::IChannel*> channelMap;

      virtual bool Initialise() = 0;
      virtual void Update(float delta) = 0;
      virtual int32_t PlaySound(int32_t soundId, float volume) = 0;
      virtual int32_t GetNextChannelId() = 0;
      virtual int32_t RegisterSound(SoundWave& sound) = 0;
      virtual void LoadSound(int32_t soundId) = 0;
      virtual bool SoundIsLoaded(int32_t soundId) = 0;
      virtual ~IAudioDriver() = 0;
  };

  inline IAudioDriver::~IAudioDriver(){}
}

#endif
