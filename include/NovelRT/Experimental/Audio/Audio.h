// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_AUDIO_H
#define NOVELRT_EXPERIMENTAL_AUDIO_H

//Audio dependencies
#include <cstdint>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <thread>
#include <future>
#include <vector>
#include <mutex>
#include "..\..\Utilities\Lazy.h"
#include "..\..\Utilities\Misc.h"
#include "..\..\Maths\GeoVector2F.h"
#include "..\..\LoggingService.h"
#include "..\..\Timing\Timestamp.h"
#include <sndfile.h>

/**
 * @brief The experimental Audio API. Comes with built-in support for the ECS.
 */
namespace NovelRT::Experimental::Audio
{
  enum class AudioBackend : int32_t;
  enum class ChannelState : int32_t;
  class IAudioDriver;
  class IChannel;
  class ISound;
  struct SoundWave;
  class AudioEngine;
}

//Audio types
#include "AudioBackend.h"
#include "ChannelState.h"
#include "IAudioDriver.h"
#include "IChannel.h"
#include "ISound.h"
#include "SoundWave.h"
#include "AudioEngine.h"

#endif // NOVELRT_EXPERIMENTAL_AUDIO_H
