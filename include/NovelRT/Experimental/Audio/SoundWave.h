// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_SOUNDWAVE_H
#define NOVELRT_SOUNDWAVE_H

namespace NovelRT::Experimental::Audio
{
  struct SoundWave
  {
    std::string soundName;
    bool looping;
    float defaultVolume;
    ISound* sound;
  };
}

#endif
