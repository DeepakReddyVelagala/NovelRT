// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Audio/Audio.h>
#include <NovelRT/Experimental/Audio/Null/Audio.Null.h>

using namespace NovelRT;

namespace NovelRT::Experimental::Audio::Null
{
  NullAudioDriver::NullAudioDriver() :
    _logger(LoggingService::LoggingService(NovelRT::Utilities::Misc::CONSOLE_LOG_AUDIO))
  {
    _nextChannelId = 0;
  }

  bool NullAudioDriver::Initialise()
  {
    _logger.logDebugLine("Initialising Null Audio Driver...");

    for(int32_t i = 0; i < _maxChannels; i++)
    {
      _channelMap.insert(std::pair<int32_t, NullChannel*>(_nextChannelId, CreateChannel()));
      if(_channelMap[_nextChannelId] == nullptr)
      {
        _logger.logErrorLine("Something went wrong creating a channel!");
        return false;
      }

      _nextChannelId++;
    }

    _logger.logDebugLine("Null Audio Driver initialised successfully.");
    return true;
  }

  void NullAudioDriver::Update(float delta)
  {
    for(auto& [key, channel] : _channelMap)
    {
      channel->Update(delta);
    }
  }

  // SoundWave* LoadSound(std::string& fileName);

  NullChannel* NullAudioDriver::CreateChannel()
  {
    return new NullChannel(_nextChannelId);
  }
}
