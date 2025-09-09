#include "pch.h"
#include  <Sound/Audio.h>
#include <Core/ActorComponent/Components/Graphics/Camera/CameraComponent.h>
#include <Core/ActorComponent/Components/Physics/RigidBody.h>
#include <Sound/SoundInstance.h>
#include <Core/Assets/Assets.h>

using namespace clt;

Audio* Audio::sInstance = nullptr;

Audio& Audio::Get()
{
	if (!sInstance)  sInstance = new Audio();
	return *sInstance;
}

void Audio::Init()
{
	FMOD::Studio::System::create(&mStudioSystem);
	mStudioSystem->initialize(32, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, nullptr);

	mStudioSystem->getCoreSystem(&mCoreSystem);

	FMOD::ChannelGroup* group = nullptr;

	mCoreSystem->createChannelGroup("SFX", &group);
	mCategoryGroups[AudioCategory::SFX] = group;

	mCoreSystem->createChannelGroup("Music", &group);
	mCategoryGroups[AudioCategory::Music] = group;

	mCoreSystem->createChannelGroup("Voice", &group);
	mCategoryGroups[AudioCategory::Voice] = group;

	mCoreSystem->createChannelGroup("UI", &group);
	mCategoryGroups[AudioCategory::UI] = group;
}

void Audio::Update()
{
	if (!mCoreSystem) return;

	CameraComponent* camera = CameraComponent::GetActiveCamera();

	Vector3 pos = camera->GetWorldLocation();
	FMOD_VECTOR listenerPos = { pos.x, pos.y, pos.z };

	FMOD_VECTOR listenerVel = { 0,0,0 };

	auto* rb = camera->GetOwner()->GetComponentOfType<RigidBody>();

	if (rb)
	{
		Vector3 vel = rb->GetVelocity() * 0.01f;
		listenerVel = { vel.x, vel.y, vel.z };
	}

	Vector3 fwd = -camera->GetWorldTransform().Forward();
	FMOD_VECTOR listenerFwd = { fwd.x, fwd.y, fwd.z };

	Vector3 up = camera->GetWorldTransform().Up();
	FMOD_VECTOR listenerUp = { up.x, up.y, up.z };

	mCoreSystem->set3DListenerAttributes(0, &listenerPos, &listenerVel, &listenerFwd, &listenerUp);

	mStudioSystem->update();
}

void Audio::Shutdown()
{
	if (mStudioSystem)
	{
		mStudioSystem->unloadAll();
		mStudioSystem->release();
		mStudioSystem = nullptr;
		mCoreSystem = nullptr;
	}
}

void Audio::PlaySound(std::weak_ptr<Sound> audio)
{
	if (!audio.lock()) return;

	Sound& tempAudio = *audio.lock().get();

	FMOD::Channel* channel = nullptr;
	mCoreSystem->playSound(tempAudio.GetHandle(), nullptr, false, &channel);
	channel->setMode(FMOD_2D);

	auto categoryGroup = mCategoryGroups[tempAudio.GetCategory()];
	if (categoryGroup) channel->setChannelGroup(categoryGroup);
}

void Audio::PlaySoundAtLocation(std::weak_ptr<Sound> audio, Vector3 pos)
{
	if (!audio.lock()) return;

	Sound& tempAudio = *audio.lock().get();

	FMOD::Channel* channel = nullptr;

	mCoreSystem->playSound(tempAudio.GetHandle(), nullptr, false, &channel);
	channel->setMode(FMOD_3D);

	auto categoryGroup = mCategoryGroups[tempAudio.GetCategory()];
	if (categoryGroup) channel->setChannelGroup(categoryGroup);

	FMOD_VECTOR fmodPos = { pos.x, pos.y, pos.z };
	FMOD_VECTOR vel = { 0,0,0 };
	if (channel) channel->set3DAttributes(&fmodPos, &vel);
}

void Audio::SetAttenuationSettings(float distanceFactor, float rolloffDistance, float dopplerScale)
{
	mCoreSystem->set3DSettings(dopplerScale, distanceFactor, rolloffDistance);
}

SoundInstance& Audio::SpawnSound(std::weak_ptr<Sound> audio)
{
	Sound& tempAudio = *audio.lock().get();

	FMOD::Channel* channel = nullptr;

	mCoreSystem->playSound(tempAudio.GetHandle(), nullptr, false, &channel);
	channel->setMode(FMOD_2D);

	auto categoryGroup = mCategoryGroups[tempAudio.GetCategory()];
	if (categoryGroup) channel->setChannelGroup(categoryGroup);

	auto instance = std::make_shared<SoundInstance>(channel, tempAudio.GetCategory());
	mActiveSounds.push_back(instance);

	return *instance;
}

SoundInstance& Audio::SpawnSoundAtLocation(std::weak_ptr<Sound> audio, Vector3 pos)
{
	Sound& tempAudio = *audio.lock().get();

	FMOD::Channel* channel = nullptr;

	mCoreSystem->playSound(tempAudio.GetHandle(), nullptr, false, &channel);
	channel->setMode(FMOD_3D);

	auto categoryGroup = mCategoryGroups[tempAudio.GetCategory()];
	if (categoryGroup) channel->setChannelGroup(categoryGroup);

	FMOD_VECTOR fmodPos = { pos.x, pos.y, pos.z };
	FMOD_VECTOR vel = { 0,0,0 };
	if (channel) channel->set3DAttributes(&fmodPos, &vel);

	auto instance = std::make_shared<SoundInstance>(channel, tempAudio.GetCategory());
	mActiveSounds.push_back(instance);

	return *instance;
}

void Audio::PlaySound(const std::string& soundName)
{
	std::weak_ptr<Sound> temp = Assets::Get().GetAudio(soundName);

	if (!temp.lock())
	{
		CLUTTER_WARNING("Sound : " + soundName + " cannot be played, first load it in Assets.");
		return;
	}
	else PlaySound(temp);
}

void Audio::PlaySoundAtLocation(const std::string& soundName, Vector3 pos)
{
	std::weak_ptr<Sound> temp = Assets::Get().GetAudio(soundName);

	if (!temp.lock())
	{
		CLUTTER_WARNING("Sound : " + soundName + " cannot be played, first load it in Assets.");
		return;
	}
	else PlaySoundAtLocation(temp, pos);
}

void Audio::ClearSpawnedSounds()
{
	for (std::weak_ptr<SoundInstance> sound : mActiveSounds)
	{
		if (auto lockedSound = sound.lock())	lockedSound->Stop();
	}

	mActiveSounds.clear();
}

void Audio::ClearAllSounds()
{
	FMOD::ChannelGroup* master = nullptr;
	mCoreSystem->getMasterChannelGroup(&master);

	if (master) master->stop();
	mActiveSounds.clear();
}

void Audio::ClearByCategory(AudioCategory category)
{
	auto temp = mCategoryGroups[category];

	if (temp) temp->stop();
}

FMOD::System& Audio::GetCoreSystem() const
{
	if (mCoreSystem) return *mCoreSystem;
	else
	{
		const_cast<Audio*>(this)->Init();
		return *mCoreSystem;
	}
}