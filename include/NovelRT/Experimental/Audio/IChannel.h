// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ICHANNEL_H
#define NOVELRT_ICHANNEL_H

namespace NovelRT::Experimental::Audio
{
  class IChannel
  {
    protected:
      LoggingService _logger;
      IAudioDriver* _driver;
      ChannelState _state = Audio::ChannelState::Initialise;
      int32_t _soundId;
      int32_t _channelId;
      NovelRT::Maths::GeoVector2F _channelPosition;
      float _volume;
      SoundWave* _sound;

    public:
      bool stopRequested;

      virtual ~IChannel() = default;
      virtual void Update(float delta) = 0;
      virtual bool IsPlaying() = 0;
      virtual bool IsStopped() = 0;
      virtual float GetVolume() = 0;
      virtual void SetVolume(float vol) = 0;

      inline ChannelState GetState()
      {
        return _state;
      }

      inline void SetState(ChannelState state)
      {
        _state = state;
      }

  };
}
#endif
