// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_NULLSOUND_H
#define NOVELRT_NULLSOUND_H

namespace NovelRT::Experimental::Audio::Null
{
  class NullSound : public Audio::ISound
  {
    protected:
      bool _loaded = false;
    public:
      NullSound(SoundWave& soundWave);
      // std::vector<uint16_t> buffer;
      // int32_t sampleRate;
      // int32_t channels;
      // int32_t sections;
      // size_t frames;
  };
}

#endif
