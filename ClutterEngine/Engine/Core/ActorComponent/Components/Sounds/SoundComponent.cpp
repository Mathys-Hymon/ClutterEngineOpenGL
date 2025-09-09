#include "pch.h"
#include "SoundComponent.h"

using namespace clt;

SoundComponent::SoundComponent(std::weak_ptr<Sound> audio, bool isLooping, bool playOnSpawn, int updateOrder) : Component(updateOrder), mSound(nullptr), mRigidbody(nullptr)
{
	mSound = &Audio::Get().SpawnSoundAtLocation(audio, GetWorldLocation());

	if (!playOnSpawn) mSound->Pause();
}

SoundComponent::SoundComponent(const std::string& soundName, bool isLooping, bool playOnSpawn, int updateOrder) : Component(updateOrder), mSound(nullptr), mRigidbody(nullptr)
{
	mSound = &Audio::Get().SpawnSoundAtLocation(soundName, GetWorldLocation());

	if (!playOnSpawn) mSound->Pause();
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
