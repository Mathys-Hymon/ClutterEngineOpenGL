#include "Core/All.h"

class DoomHUD : public clt::HUDComponent
{
	float mCanShoot;
	float mTauntDelay;

	std::vector<clt::Texture*> mHeads;

public:
	int mLifeState;

	DoomHUD();
	~DoomHUD() = default;

	virtual void Start() override;
	virtual void Update() override;

	bool TriggerShoot(int ammo);

	void UpdateLifeState(int pLifeState);
};