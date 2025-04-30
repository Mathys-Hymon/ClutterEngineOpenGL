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

std::map<Weapons, int> mWeaponAmmo;

clt::AnimatorElement* mHand;  

Weapons mWeapon;  

public:  

DoomController();  
~DoomController() = default;  

virtual void Start() override;  

void RotateCamera(Vector2 movement);  
void Move(Vector2 movement);  

void Shoot();  

virtual void Update() override;  
};