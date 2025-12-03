#pragma once
#include <Core/ActorComponent/Component.h>
#include <Core/ActorComponent/Components/Physics/IRigidbody.h>
#include <Sound/SoundInstance.h>
#include <Sound/Audio.h>

namespace clt
{
	class CLUTTER_API SoundComponent : public Component
	{

		std::shared_ptr<SoundInstance> mSound;
		IRigidbody* mRigidbody{nullptr};

	public:
		CLUTTER_CLASS(SoundComponent);
		
		SoundComponent(std::weak_ptr<Sound> audio, bool playOnSpawn = true, bool isLooping = false, int updateOrder = 0);
		SoundComponent(const std::string& soundName, bool playOnSpawn = true, bool isLooping = false, int updateOrder = 0);
		SoundComponent() {};

		void SetSound(std::weak_ptr<Sound> audio, bool playOnSpawn = true, bool isLooping = false);
		void SetSound(const std::string& soundName, bool playOnSpawn = true, bool isLooping = false);

		void SetupProperties() override {
			CPROPERTY(mSound, clt::PropMode::ReadWrite);
		}
		
		SoundInstance& GetSound() const { return *mSound; };

		~SoundComponent() = default;

		void Update() override;
		
	};
}