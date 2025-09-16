#include "Core/All.h"

class DoomHUD : public clt::HUDComponent
{
	float mCanShoot;
	float mTauntDelay;

	std::vector<std::weak_ptr<clt::Texture>> mHeads;

public:
	int mLifeState, mLife;

	DoomHUD();
	~DoomHUD() = default;

	virtual void Start() override;
	virtual void Update() override;

	bool TriggerShoot(int ammo);

	void UpdateLifeState(int pLifeState);
	void UpdateLife(int pNewLife);
};