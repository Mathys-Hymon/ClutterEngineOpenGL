#include "pch.h"
#include "SoundComponent.h"

using namespace clt;

REGISTER_COMPONENT_CLASS(SoundComponent);

SoundComponent::SoundComponent(const std::string& soundName, bool isLooping, bool playOnSpawn, int updateOrder) 
	: Component(0), mSoundName(soundName), mPlayOnSpawn(playOnSpawn), mIsLooping(isLooping)
{
	mSound = Audio::Get().SpawnSoundComponent(soundName);
	mPlayOnSpawn = playOnSpawn;
	mIsLooping = isLooping;
	mSoundName = soundName;

	if (!playOnSpawn) mSound->Pause();
	mSound->SetLooping(isLooping);
	
	SetupProperties();
}

SoundComponent::SoundComponent() 
	: Component(0), mSoundName(""), mPlayOnSpawn(true), mIsLooping(false)
{
	SetupProperties();
}

void SoundComponent::Start()
{
	Component::Start();
	
	if (!mSoundName.empty())
	{
		SetSound(mSoundName, mIsLooping, mPlayOnSpawn);
	}
}

void SoundComponent::SetSound(const std::string& soundName, bool playOnSpawn, bool isLooping)
{
	mSoundName = soundName;
	mPlayOnSpawn = playOnSpawn;
	mIsLooping = isLooping;
	
	if (mSound) mSound->Stop();
	mSound = Audio::Get().SpawnSoundComponent(soundName, GetWorldLocation());

	if (!playOnSpawn) mSound->Pause();
	mSound->SetLooping(isLooping);
}

void SoundComponent::Update()
{
	if (mSound)
	{
		if(!mRigidbody) mRigidbody = GetOwner()->GetComponentOfType<IRigidbody>();

		Vector3 vel = mRigidbody ? mRigidbody->GetVelocity() : Vector3{ 0,0,0 };

		mSound->Set3DAttributes(GetWorldLocation(), vel);
	}
}
