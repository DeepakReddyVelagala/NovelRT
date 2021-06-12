// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Audio/Audio.h>
//#include <NovelRT/Experimental/Audio/OpenAL/Audio.OpenAL.h>
#include <NovelRT/Experimental/Audio/Null/Audio.Null.h>

using namespace NovelRT;

namespace NovelRT::Experimental::Audio
{
  AudioEngine::AudioEngine():
    _debugModeEnabled(false),
    _driver(nullptr),
    _logger(LoggingService::LoggingService(NovelRT::Utilities::Misc::CONSOLE_LOG_AUDIO)),
    _soundMap(std::map<std::string, SoundWave*>()),
    _channelMap(std::map<int32_t, IChannel*>())
  {
    //_driver = new OpenAL::OALAudioDriver();
  }

  AudioEngine::AudioEngine(AudioBackend backend):
    _debugModeEnabled(false),
    _driver(nullptr),
    _logger(LoggingService::LoggingService(NovelRT::Utilities::Misc::CONSOLE_LOG_AUDIO)),
    _soundMap(std::map<std::string, SoundWave*>()),
    _channelMap(std::map<int32_t, IChannel*>())
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
    //Commented until I determine when to remove/change to Info...
    // #ifdef DEBUG
    // _debugModeEnabled = true;
    // #endif

    // if(_debugModeEnabled)
    // {
      _logger.setLogLevel(LogLevel::Debug);
    // }
    // else
    // {
    //   _logger.setLogLevel(LogLevel::Info);
    // }

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

  void AudioEngine::Update()
  {
    _driver->Update(0);
  }

      // void Shutdown();

  void AudioEngine::LoadSound(const std::string& soundPath, bool isLooping)
  {
    SoundWave* newWave = new SoundWave;
    newWave->looping = isLooping;

    std::ifstream file(soundPath, std::ios::in || std::ios::binary);

    if(!file.is_open())
    {
      std::string msg = "Could not open ";
      msg += soundPath;
      _logger.logErrorLine(msg);
      return;
    }
    else
    {
      char* header = new char[4];
      file.seekg(0, std::ios::beg);
      file.read(header, 4);

      std::string msg = "\nFile Loading...\nHeader: ";
      msg += header;
      msg += "\n";
      _logger.logDebugLine(header);
    }
  }
      // void UnloadSound(const std::string& soundName);
      // void SetListenerOrientation(const NovelRT::Maths::GeoVector2F& position, const NovelRT::Maths::GeoVector2F& up);
      // int32_t PlaySound(const std::string& soundName, float volume);
      // void StopChannel(int32_t channelId);
      // void PauseChannel(int32_t channelId);
      // void StopAllChannels();
      // void SetChannelVolume(int32_t channelId, float volume);
      // bool IsPlaying(int32_t channelId);
      // bool IsStopped(int32_t channelId);
}
