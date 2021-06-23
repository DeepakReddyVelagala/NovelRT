// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_AUDIO_NULL_H
#define NOVELRT_EXPERIMENTAL_AUDIO_NULL_H

namespace NovelRT::Experimental::Audio::Null
{
  class NullChannel;
  class NullSound;
  class NullListener;
  class NullAudioDriver;
}

//Audio.OpenAL dependencies
#include <cstdint>
#include <map>
#include <string>
#include "../Audio.h"
#include "../../../LoggingService.h"
#include "../../../Utilities/Lazy.h"

//Audio.OpenAL Types
#include "NullChannel.h"
#include "NullSound.h"
#include "NullAudioDriver.h"


#endif //NOVELRT_EXPERIMENTAL_AUDIO_NULL_H
