#pragma once
#include <Core/ActorComponent/Component.h>
#include <Core/ActorComponent/Components/Physics/RigidBody.h>
#include <Sound/SoundInstance.h>
#include <Sound/Audio.h>

namespace clt
{
	class CLUTTER_API SoundComponent : public Component
	{

		std::shared_ptr<SoundInstance> mSound;
		RigidBody* mRigidbody;

	public:
		SoundComponent(std::weak_ptr<Sound> audio, bool playOnSpawn = true, bool isLooping = false, int updateOrder = 0);
		SoundComponent(const std::string& soundName, bool playOnSpawn = true, bool isLooping = false, int updateOrder = 0);

		void SetSound(std::weak_ptr<Sound> audio, bool playOnSpawn = true, bool isLooping = false);
		void SetSound(const std::string& soundName, bool playOnSpawn = true, bool isLooping = false);

		SoundInstance& GetSound() const { return *mSound; };

		~SoundComponent() = default;

		void Update() override;
	};
}