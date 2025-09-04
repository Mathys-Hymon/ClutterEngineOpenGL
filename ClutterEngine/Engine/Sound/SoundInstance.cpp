#include "pch.h"
#include "SoundInstance.h"

using namespace clt;

SoundInstance::SoundInstance(FMOD::Channel* channel, AudioCategory category) : mChannel(channel), mCategory(category)
{}

void SoundInstance::SetVolume(float volumeDB)
{
    if (mChannel)
    {
        float volume = powf(10.0f, 0.5f * volumeDB);
        mChannel->setVolume(volume);
    }
}

void SoundInstance::SetLocation(const Vector3& pos)
{
    if (mChannel)
    {
        FMOD_VECTOR fpos {pos.x, pos.y, pos.z};
        mChannel->set3DAttributes(&fpos, nullptr);
    }
}

void SoundInstance::Stop()
{
    if (mChannel) mChannel->stop();
}    
     
void SoundInstance::Pause(bool paused)
{    
    if (mChannel) mChannel->setPaused(paused);
}    
     
bool SoundInstance::IsPlaying() const
{
    if (!mChannel) return false;
    bool playing = false;
    mChannel->isPlaying(&playing);
    return playing;
}
