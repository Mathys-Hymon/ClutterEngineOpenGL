#pragma once  
#include <Core/All.h>  
#include <map> // Ensure the map header is included  

enum class Weapons  
{  
Hand,  
Pistol,  
ShotGun,  
};  

class DoomController : public clt::PlayerController  
{  
float mRotationVelocity;  
Vector2 mMovementVelocity;  
int mLife;

std::map<Weapons, int> mWeaponAmmo;

clt::AnimatorElement* mHand;  

bool mDead;

Weapons mWeapon;  

public:  

DoomController();  
~DoomController() = default;  

virtual void Start() override;  

void RotateCamera(Vector2 movement);  
void Move(Vector2 movement);  

void Shoot();  

void GetHit();

virtual void Update() override;  
};