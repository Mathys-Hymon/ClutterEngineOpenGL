#include "Core/All.h"

class DoomHUD : public clt::HUDComponent
{
public:
	int lifeState;

	float test;

	DoomHUD();
	~DoomHUD() = default;

	virtual void Start() override;

	virtual void Update() override;

	void TriggerShoot();
};