// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Audio/Audio.h>
#include <NovelRT/Experimental/Audio/Null/Audio.Null.h>

using namespace NovelRT;

namespace NovelRT::Experimental::Audio::Null
{
  NullChannel::NullChannel(NullAudioDriver* driver, int32_t soundId, SoundWave* wave, float volume)
  {
    _driver = driver;
    _soundId = soundId;
    _sound = wave;
    _volume = volume;
    stopRequested = false;
  }

  void NullChannel::Update(float delta)
  {
    std::string msg = std::to_string(delta) + " ";
    switch(_state)
    {
      case Audio::ChannelState::Initialise:
      case Audio::ChannelState::ToPlay:
      {
        if(stopRequested)
        {
          msg += "Stop requested on Sound #" + std::to_string(_soundId);
          _logger.logDebugLine(msg);
          _state = Audio::ChannelState::Stopping;
          return;
        }

        if(!_driver->SoundIsLoaded(_soundId))
        {
          msg += "Sound is loading - Sound #" + std::to_string(_soundId);
          _logger.logDebugLine(msg);
          //_driver->LoadSound(_soundId);
          LoadSound(_soundId);
          _state = Audio::ChannelState::Loading;
          return;
        }

        auto exists = _driver->soundMap.find(_soundId);
        if(exists != _driver->soundMap.end())
        {
          //Play a sound
          msg += "Sound is playing - Sound #" + std::to_string(_soundId);
          _logger.logDebugLine(msg);
          _state = Audio::ChannelState::Playing;
        }
        break;
      }
      case Audio::ChannelState::Loading:
      {
        if(_driver->SoundIsLoaded(_soundId))
        {
          msg += "Sound prepared to play - Sound #" + std::to_string(_soundId);
          _logger.logDebugLine(msg);
          _state = Audio::ChannelState::ToPlay;
        }
        else
        {
          msg += "Sound still loading - Sound #" + std::to_string(_soundId);
          _logger.logDebugLine(msg);
        }
        break;
      }
      case Audio::ChannelState::Playing:
      {
        if(!IsPlaying() || stopRequested)
        {
          msg += "Sound is stopping - Sound #" + std::to_string(_soundId);
          _logger.logDebugLine(msg);
          _state = Audio::ChannelState::Stopping;
          return;
        }
        break;
      }
      case Audio::ChannelState::Stopping:
      {
        //call stop
        if(!IsPlaying())
        {
          msg += "Sound is stopped - Sound #" + std::to_string(_soundId);
          _logger.logDebugLine(msg);
          _state = Audio::ChannelState::Stopped;
          return;
        }
        break;
      }
      case Audio::ChannelState::Stopped:
      {
        break;
      }
    }
  }

  bool NullChannel::IsStopped()
  {
    return (_state == Audio::ChannelState::Stopped) ? true : false;
  }

  bool NullChannel::IsPlaying()
  {
    return (_state == Audio::ChannelState::Playing) ? true : false;
  }

  float NullChannel::GetVolume()
  {
    return _volume;
  }

  void NullChannel::SetVolume(float vol)
  {
    _volume = vol;
  }

  void NullChannel::LoadSound(int32_t soundId)
  {
    _driver->LoadSound(soundId);
  }

  NullChannel::~NullChannel()
  {}

}
