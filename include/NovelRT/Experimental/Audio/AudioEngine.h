// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_AUDIOENGINE_H
#define NOVELRT_AUDIOENGINE_H

/**
 * @brief The experimental Audio API. Comes with built-in support for the ECS.
 */
namespace NovelRT::Experimental::Audio
{
  class AudioEngine
  {
    private:
      bool _debugModeEnabled;
      IAudioDriver* _driver;
      LoggingService _logger;
      std::map<std::string, SoundWave*> _soundMap;
      std::map<int32_t, IChannel*> _channelMap;

    public:
      AudioEngine();
      AudioEngine(AudioBackend backend);
      void Initialize();
      void Update();
      void Shutdown();

      void LoadSound(const std::string& soundPath, bool isLooping = false);
      void UnloadSound(const std::string& soundName);
      void SetListenerOrientation(const NovelRT::Maths::GeoVector2F& position, const NovelRT::Maths::GeoVector2F& up);
      int32_t PlaySound(const std::string& soundName, float volume);
      void StopChannel(int32_t channelId);
      void PauseChannel(int32_t channelId);
      void StopAllChannels();
      void SetChannelVolume(int32_t channelId, float volume);
      bool IsPlaying(int32_t channelId);
      bool IsStopped(int32_t channelId);
  };
}

#endif // NOVELRT_AUDIOENGINE_H
