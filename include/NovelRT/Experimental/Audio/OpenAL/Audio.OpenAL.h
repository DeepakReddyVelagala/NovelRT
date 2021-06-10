// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_AUDIO_OPENAL_H
#define NOVELRT_EXPERIMENTAL_AUDIO_OPENAL_H

namespace NovelRT::Experimental::Audio::OpenAL
{
  class OALChannel;
  class OALSound;
  class OALListener;
  class OALAudioDriver;
}

//Audio.OpenAL dependencies
#include <AL/al.h>
#include <AL/alc.h>
#include <cstdint>
#include <map>
#include <string>
#include <thread>
#include "../Audio.h"
#include "../../../LoggingService.h"
#include "../../../Utilities/Lazy.h"

//Audio.OpenAL Types
#include "OALChannel.h"
#include "OALAudioDriver.h"


#endif //NOVELRT_EXPERIMENTAL_AUDIO_OPENAL_H
