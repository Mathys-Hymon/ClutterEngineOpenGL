#include "pch.h"
#include "SoundComponent.h"

using namespace clt;

SoundComponent::SoundComponent(std::weak_ptr<Sound> audio, bool isLooping, bool playOnSpawn, int updateOrder) : Component(updateOrder), mSound(nullptr), mRigidbody(nullptr)
{
	mSound = &Audio::Get().SpawnSoundComponent(audio, GetWorldLocation());

	if (!playOnSpawn) mSound->Pause();
	mSound->SetLooping(isLooping);
}

SoundComponent::SoundComponent(const std::string& soundName, bool isLooping, bool playOnSpawn, int updateOrder) : Component(updateOrder), mSound(nullptr), mRigidbody(nullptr)
{
	mSound = &Audio::Get().SpawnSoundComponent(soundName, GetWorldLocation());

	if (!playOnSpawn) mSound->Pause();
	mSound->SetLooping(isLooping);
}

void SoundComponent::SetSound(std::weak_ptr<Sound> audio, bool playOnSpawn, bool isLooping)
{
	if (mSound) mSound->Stop();
	mSound = &Audio::Get().SpawnSoundComponent(audio, GetWorldLocation());

	if (!playOnSpawn) mSound->Pause();
	mSound->SetLooping(isLooping);
}

void SoundComponent::SetSound(const std::string& soundName, bool playOnSpawn, bool isLooping)
{
	if (mSound) mSound->Stop();
	mSound = &Audio::Get().SpawnSoundComponent(soundName, GetWorldLocation());

	if (!playOnSpawn) mSound->Pause();
	mSound->SetLooping(isLooping);
}

void SoundComponent::Update()
{
	if (mSound)
	{
		if(!mRigidbody) mRigidbody = GetOwner()->GetComponentOfType<RigidBody>();

		Vector3 vel = mRigidbody ? mRigidbody->GetVelocity() : Vector3{ 0,0,0 };

		mSound->Set3DAttributes(GetWorldLocation(), vel);
	}
}
