#include "pch.h"
#include "Sounds.h"
#include <FMOD/Core/fmod.hpp>
#include <FMOD/Studio/fmod_studio.hpp>

using namespace clt;

Sounds::Sounds()
{
	FMOD_RESULT result;
	FMOD::System* pSystem = nullptr;

	result = FMOD::System_Create(&pSystem);

	pSystem->init(32, FMOD_INIT_NORMAL, nullptr);

	FMOD::Sound* pSound = nullptr;

}

Sounds::~Sounds()
{
}
