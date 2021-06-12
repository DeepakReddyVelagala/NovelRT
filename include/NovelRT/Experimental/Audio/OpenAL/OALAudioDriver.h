// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_OALAUDIODRIVER_H
#define NOVELRT_OALAUDIODRIVER_H

namespace NovelRT::Experimental::Audio::OpenAL
{
  class OALAudioDriver : public Audio::IAudioDriver
  {
    private:

      Utilities::Lazy<std::unique_ptr<ALCdevice, void (*)(ALCdevice*)>> _device;
      Utilities::Lazy<std::unique_ptr<ALCcontext, void (*)(ALCcontext*)>> _context;
      LoggingService _logger;


      const int32_t _maxChannels = 255;   //256 channels supported -> this should be 32 on mobile but we're not there yet.
      const size_t _bufferSize = 2048;
      const ALuint _noBuffer = 0;
      const ALfloat _pitch = 1.0f;

      bool InitialiseOpenAL();

    public:
      OALAudioDriver();
      bool Initialise();
      void Update(float delta);
      SoundWave* LoadSound(std::string& fileName);
      inline OALChannel* CreateChannel() final
      {
        return new OALChannel();
      }
  };
}

#endif
