// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Audio/Audio.h>
#include <NovelRT/Experimental/Audio/Null/Audio.Null.h>

using namespace NovelRT;

namespace NovelRT::Experimental::Audio
{
  AudioEngine::AudioEngine():
    _debugModeEnabled(false),
    _driver(nullptr),
    _logger(LoggingService::LoggingService(NovelRT::Utilities::Misc::CONSOLE_LOG_AUDIO))
  {
    //_driver = new OpenAL::OALAudioDriver();
  }

  AudioEngine::AudioEngine(AudioBackend backend):
    _debugModeEnabled(false),
    _driver(nullptr),
    _logger(LoggingService::LoggingService(NovelRT::Utilities::Misc::CONSOLE_LOG_AUDIO))
  {
    if (backend == AudioBackend::Null)
    {
      _driver = new Null::NullAudioDriver();
    }
    else
    {
      //_driver = new OpenAL::OALAudioDriver();
    }
  }

  void AudioEngine::Initialize()
  {
    _logger.setLogLevel(LogLevel::Debug);

    _logger.logInfoLine("Initializing Audio Engine...");
    if (_driver->Initialise())
    {
      _logger.logInfoLine("Audio Engine initialised.");
    }
    else
    {
      _logger.logErrorLine("Failed to initialise Audio Engine!");
    }
  }

  void AudioEngine::Update(NovelRT::Timing::Timestamp stamp)
  {
    _driver->Update(stamp.getSecondsFloat());
  }

  void AudioEngine::LoadSound(int32_t soundId)
  {
    _driver->LoadSound(soundId);
  }

  int32_t AudioEngine::RegisterSound(const std::string& sndName, float defaultVolume, bool isLooping, bool loadNow)
  {
    SoundWave* wave = new SoundWave{ sndName, isLooping, defaultVolume, nullptr };

    int32_t id = _driver->RegisterSound(*wave);

    if(loadNow)
    {
      LoadSound(id);
    }

    return id;
  }

  int32_t AudioEngine::PlaySound(int32_t soundId, float volume)
  {
    return _driver->PlaySound(soundId, volume);
  }

  void AudioEngine::StopChannel(int32_t channelId)
  {
    auto exists = _driver->channelMap.find(channelId);
    if(exists == _driver->channelMap.end())
    {
      return;
    }

    exists->second->stopRequested = true;
  }

  void AudioEngine::Shutdown()
  {
    if (_driver != nullptr)
    {
      delete _driver;
    }
  }

// void UnloadSound(const std::string& soundName)
// void SetListenerOrientation(const NovelRT::Maths::GeoVector2F& position, const NovelRT::Maths::GeoVector2F& up);
// void PauseChannel(int32_t channelId);
// void StopAllChannels();
// void SetChannelVolume(int32_t channelId, float volume);
// bool IsPlaying(int32_t channelId);
// bool IsStopped(int32_t channelId);

}
