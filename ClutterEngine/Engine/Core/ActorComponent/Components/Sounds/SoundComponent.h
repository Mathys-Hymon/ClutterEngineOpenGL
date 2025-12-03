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

		std::string mSoundName;
		bool mPlayOnSpawn{true};
		bool mIsLooping{false};
		
	public:
		CLUTTER_CLASS(SoundComponent)
		
		SoundComponent(const std::string& soundName, bool playOnSpawn = true, bool isLooping = false, int updateOrder = 0);
		SoundComponent();

		void SetupProperties() override 
		{
			CPROPERTY(mSoundName, PropMode::ReadWrite)
			CPROPERTY(mPlayOnSpawn, PropMode::ReadWrite)
			CPROPERTY(mIsLooping, PropMode::ReadWrite)
		}
		
		void Start() override;
		
		void SetSound(const std::string& soundName, bool playOnSpawn = true, bool isLooping = false);
		
		SoundInstance& GetSound() const { return *mSound; };

		~SoundComponent() = default;

		void Update() override;
		
	};
}