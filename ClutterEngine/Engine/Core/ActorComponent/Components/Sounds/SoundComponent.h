#pragma once
#include <Core/ActorComponent/Component.h>
#include <Core/ActorComponent/Components/Physics/RigidBody.h>
#include <Sound/SoundInstance.h>
#include <Sound/Audio.h>

namespace clt
{
	class CLUTTER_API SoundComponent : public Component
	{

		SoundInstance* mSound;
		RigidBody* mRigidbody;

	public:
		SoundComponent(std::weak_ptr<Sound> audio, bool playOnSpawn, bool isLooping, int updateOrder = 0);
		SoundComponent(const std::string& soundName, bool playOnSpawn, bool isLooping, int updateOrder = 0);

		void SetSound(std::weak_ptr<Sound> audio);
		void SetSound(const std::string& soundName);

		Sound& GetSound() const;

		~SoundComponent() = default;

		void Update() override;
	};
}