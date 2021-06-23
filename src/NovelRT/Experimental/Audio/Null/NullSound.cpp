// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Audio/Audio.h>
#include <NovelRT/Experimental/Audio/Null/Audio.Null.h>

using namespace NovelRT;

namespace NovelRT::Experimental::Audio::Null
{
  NullSound::NullSound(SoundWave& soundWave)
  {
    SF_INFO info;
    info.format = 0;
    SNDFILE* file = sf_open(soundWave.soundName.c_str(), SFM_READ, &info);

    if (file == nullptr)
    {
      //_logger.logError(std::string(sf_strerror(nullptr)));
      sampleRate = 0;
      channels = 0;
      sections = 0;
      frames = 0;
      buffer = std::vector<uint16_t>();
      return;
    }

    sampleRate = info.samplerate;
    channels = info.channels;
    sections = info.sections;
    frames = static_cast<size_t>(info.frames);

    buffer = std::vector<uint16_t>();
    std::vector<short> readBuffer;
    readBuffer.resize(2048);  //magic number REEEEEEEEEEEEEEEEEEEEEEEE

    sf_count_t readSize = 0;

    while ((readSize = sf_read_short(file, readBuffer.data(), static_cast<sf_count_t>(readBuffer.size()))) != 0)
    {
      buffer.insert(buffer.end(), readBuffer.begin(), readBuffer.begin() + readSize);
    }
  }
}
