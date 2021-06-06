// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#include "..\IAudioDriver.h"
#include "OALChannel.h"
#include "NovelRT.h"
#include <map>
#include <string>
//#include <thread>

#ifndef NOVELRT_OALAUDIODRIVER_H
#define NOVELRT_OALAUDIODRIVER_H

namespace NovelRT::Experimental::Audio
{
  class OALAudioDriver : public IAudioDriver
  {
    private:
      int32_t _nextChannelId;
      std::map<OALChannel> _channelMap;
      Utilities::Lazy<std::unique_ptr<ALCdevice, void (*)(ALCdevice*)>> _device;
      Utilities::Lazy<std::unique_ptr<ALCcontext, void (*)(ALCcontext*)>> _context;
      //std::thread _backgroundThread;     -> Need to ask Matt about this since I don't want to block main thrd.

      const int32_t _maxChannels = 255;   //256 channels supported -> this should be 32 on mobile but we're not there yet.
      const size_t _bufferSize = 2048;
      const ALuint _noBuffer = 0;
      const ALfloat _pitch = 1.0f;

      bool InitialiseOpenAL();
      int CreateChannel(std::string& fileName);

    public:
      OALAudioDriver();
      bool Initialise();
      void Update(float delta);
      int LoadSound(std::string& fileName);
  };
}

#endif
