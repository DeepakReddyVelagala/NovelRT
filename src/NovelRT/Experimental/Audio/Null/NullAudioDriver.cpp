// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Audio/Audio.h>
#include <NovelRT/Experimental/Audio/Null/Audio.Null.h>

using namespace NovelRT;

namespace NovelRT::Experimental::Audio::Null
{
  NullAudioDriver::NullAudioDriver()
  {
    _logger = LoggingService::LoggingService(NovelRT::Utilities::Misc::CONSOLE_LOG_AUDIO);
    channelMap = std::map<int32_t, IChannel*>();
    _soundToChannelMap = std::map<int32_t, int32_t>();
    _nextChannelId = 0;
    _nextSoundId = 0;
  }

  bool NullAudioDriver::Initialise()
  {
    _logger.logDebugLine("Null Audio Driver initialised successfully.");
    return true;
  }

  void NullAudioDriver::Update(float delta)
  {
    std::vector<std::map<int32_t, IChannel*>::iterator> stopped;
    for(auto it = channelMap.begin(); it != channelMap.end(); it++)
    {
      it->second->Update(delta);
      if(it->second->GetState() == Audio::ChannelState::Stopped)
      {
        stopped.push_back(it);
      }
    }

    for(auto& it : stopped)
    {
      channelMap.erase(it);
    }
  }

  int32_t NullAudioDriver::RegisterSound(SoundWave& sound)
  {

    //SoundWave* wave = &sound;
    auto exists = soundMap.begin();
    while(exists != soundMap.end())
    {
      std::pair<int32_t, SoundWave> existing = *exists;
      if(&existing.second == &sound)
      {
        return existing.first;
      }
      exists++;
    }

    _nextSoundId++;
    soundMap.insert(std::make_pair(_nextSoundId, sound));
    return _nextSoundId;
  }

  int32_t NullAudioDriver::PlaySound(int32_t soundId, float volume)
  {
    auto exists = soundMap.find(soundId);
    if(exists == soundMap.end())
    {
      //Sound is not registered
      return GetNextChannelId();
    }

    int32_t channelId = GetNextChannelId();
    auto soundAlreadyPlaying = _soundToChannelMap.find(soundId);
    if(soundAlreadyPlaying != _soundToChannelMap.end())
    {
      auto channel = channelMap.find(soundAlreadyPlaying->second);
      if(channel == channelMap.end())
      {
        _soundToChannelMap.erase(soundId);
      }
      else
      {
          NullChannel* nullChannel = reinterpret_cast<NullChannel*>(channel->second);

        if(!nullChannel->IsPlaying())
        {
          nullChannel->SetState(Audio::ChannelState::ToPlay);
        }
        return channel->first;
      }
    }

    std::map<int32_t, Audio::IChannel*>::iterator channelExists = channelMap.find(channelId);
    if (channelExists == channelMap.end())
    {
      auto channel = new NullChannel(this, soundId, &exists->second, volume);
      channelMap.insert(std::make_pair(channelId, channel));
      _soundToChannelMap.insert(std::make_pair(soundId, channelId));
    }

    return channelId;
  }

  int32_t NullAudioDriver::GetNextChannelId()
  {
    return _nextChannelId++;
  }

  void NullAudioDriver::LoadSound(int32_t soundId)
  {
    std::thread driverThread(&NullAudioDriver::LoadSoundInternal, this, soundId);
    driverThread.detach();
  }

  void NullAudioDriver::LoadSoundInternal(int32_t soundId)
  {
    bool retrievedLock = false;

    while(!retrievedLock)
    {
      if(_mutex.try_lock())
      {
        retrievedLock = true;
        auto existing = soundMap.find(soundId);
          if(existing != soundMap.end())
          {
            //it's registered
            auto snd = new NullSound(existing->second);
            existing->second.sound = snd;
            std::string msg = "Sound #" + std::to_string(soundId) + " loaded succesfully: " + existing->second.soundName;
            _logger.logDebugLine(msg);
            _mutex.unlock();
            return;
          }
          else
          {
            std::string msg = "Sound #" + std::to_string(soundId) + "is not registered!";
            _logger.logErrorLine(msg);
            _mutex.unlock();
          }
      }
    }


  }

  NullSound* NullAudioDriver::CreateSound(SoundWave& sound)
  {
    return new NullSound(sound);
  }

  bool NullAudioDriver::SoundIsLoaded(int32_t soundId)
  {
    auto loaded = soundMap.find(soundId);
    if (loaded == soundMap.end())
    {
      return false;
    }
    else
    {
      if(loaded->second.sound == nullptr)
      {
        return false;
      }
      else
      {
        return true;
      }
    }
  }

  NullAudioDriver::~NullAudioDriver()
  {
    for(auto it = soundMap.begin(); it != soundMap.end(); it++)
    {
      if (it->second.sound != nullptr)
      {
        delete it->second.sound;
      }
    }

    for(auto it = channelMap.begin(); it != channelMap.end(); it++)
    {
      if (it->second != nullptr)
      {
        delete it->second;
      }
    }
  }

}
