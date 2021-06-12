// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_SOUNDWAVE_H
#define NOVELRT_SOUNDWAVE_H

namespace NovelRT::Experimental::Audio
{
  struct SoundWave
  {
    std::string fileName;
    bool looping;
    bool streaming;
    char* buffer;
    int32_t sampleRate;
  };
}

#endif
