// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_NullAUDIODRIVER_H
#define NOVELRT_NullAUDIODRIVER_H

namespace NovelRT::Experimental::Audio::Null
{
  class NullAudioDriver : public Audio::IAudioDriver
  {
    private:
      LoggingService _logger;
      std::map<int32_t, NullChannel*> _channelMap;
      const int32_t _maxChannels = 255;
      const size_t _bufferSize = 2048;

    public:
      NullAudioDriver();
      bool Initialise();
      void Update(float delta);
      SoundWave* LoadSound(std::string& fileName);
      NullChannel* CreateChannel() final;
  };
}

#endif
