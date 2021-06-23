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
      const size_t _bufferSize = 2048;
      bool _debugModeEnabled;
      IAudioDriver* _driver;
      LoggingService _logger;

    public:
      AudioEngine();
      AudioEngine(AudioBackend backend);
      void Initialize();
      void Update(NovelRT::Timing::Timestamp stamp);
      void Shutdown();

      int32_t RegisterSound(const std::string& sndName, float defaultVolume, bool isLooping, bool loadNow = true);
      void UnregisterSound(int32_t soundId);
      void LoadSound(int32_t soundId);
      void UnloadSound(int32_t soundId);
      void SetListenerOrientation(const NovelRT::Maths::GeoVector2F& position, const NovelRT::Maths::GeoVector2F& up);
      int32_t PlaySound(int32_t soundId, float volume);
      void StopChannel(int32_t channelId);
      //void PauseChannel(int32_t channelId);
      void StopAllChannels();
      void SetChannelVolume(int32_t channelId, float volume);
      bool IsPlaying(int32_t channelId);
      bool IsStopped(int32_t channelId);
  };
}

#endif // NOVELRT_AUDIOENGINE_H
