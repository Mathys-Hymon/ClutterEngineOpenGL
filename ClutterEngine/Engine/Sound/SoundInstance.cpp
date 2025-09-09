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

void SoundInstance::SetPitch(float pitch)
{
    if(mChannel) mChannel->setPitch(pitch);
}

void SoundInstance::Set3DAttributes(const Vector3& pos, const Vector3& vel)
{
    if (mChannel)
    {
        FMOD_VECTOR fpos{ pos.x, pos.y, pos.z };

        if (vel.Length() != 0)
        {
            FMOD_VECTOR fvel{ vel.x, vel.y, vel.z };
            mChannel->set3DAttributes(&fpos, &fvel);
        }
        else  mChannel->set3DAttributes(&fpos, nullptr);
    }
}

void SoundInstance::Stop()
{
    if (mChannel) mChannel->stop();
}

void SoundInstance::Pause() const
{
    SetPaused(true);
}

void SoundInstance::Play() const
{
    SetPaused(false);
}

void SoundInstance::SetPaused(bool paused) const
{    
    if (mChannel) mChannel->setPaused(paused);
}    
     
void SoundInstance::SetLooping(bool loop) const
{
    if (!mChannel) return;

    mChannel->setMode(loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
}

bool SoundInstance::IsPlaying() const
{
    if (!mChannel) return false;
    bool playing = false;
    mChannel->isPlaying(&playing);
    return playing;
}
