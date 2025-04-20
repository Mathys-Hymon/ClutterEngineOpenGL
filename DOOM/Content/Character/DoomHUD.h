#include "Core/All.h"

class DoomHUD : public clt::HUDComponent
{
public:
	int lifeState;

	DoomHUD();
	~DoomHUD() = default;

	virtual void Start() override;

	void TriggerShoot();
};