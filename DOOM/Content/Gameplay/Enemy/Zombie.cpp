#include "Zombie.h"


Zombie::Zombie(clt::Level* pLevel, std::string pName) : clt::Actor(pLevel, pName), mLife(1), mOldAnimIndex(-1), mAnimIndex(0)
{
    
	mAnimator = AddComponent<clt::AnimatorComponent>("idle_0", clt::Assets::Get().LoadTexture("Content/Resources/Sprites/Enemy/idle_front.png", "idle_Front", TextureFilter::NEAREST, false));

    mAnimator->AddNewAnim("death", clt::Assets::Get().BulkLoadTexture("Content/Resources/Sprites/Enemy/", 4, "_death.png", "death", TextureFilter::NEAREST, false), false);

    mAnimator->AddNewAnim("idle_1", clt::Assets::Get().LoadTexture("Content/Resources/Sprites/Enemy/idle_frontleft.png", "idle_FrontLeft", TextureFilter::NEAREST, false), false);

    mAnimator->AddNewAnim("idle_2", clt::Assets::Get().LoadTexture("Content/Resources/Sprites/Enemy/idle_left.png", "idle_Left", TextureFilter::NEAREST, false), false);

    mAnimator->AddNewAnim("idle_3", clt::Assets::Get().LoadTexture("Content/Resources/Sprites/Enemy/idle_backleft.png", "idle_BackLeft", TextureFilter::NEAREST, false), false);
    
    mAnimator->AddNewAnim("idle_4", clt::Assets::Get().LoadTexture("Content/Resources/Sprites/Enemy/idle_back.png", "idle_Back", TextureFilter::NEAREST, false), false);

    AddComponent<clt::OBBCollider>(Vector3{2.5f,5.0f,2.5f});

    SetActorLocation({ GetActorLocation().x,-0.3f,GetActorLocation().z});
    SetActorScale(1.3f);
}

Zombie::~Zombie()
{
}

void Zombie::Start()
{
}

void Zombie::Update()
{
	clt::CameraComponent* cam = clt::CameraComponent::GetActiveCamera();
    mAnimator->SetWorldRotation(Quaternion::LookAt(cam->GetWorldLocation(), GetActorLocation()));


    if(mLife > 0) GetDirection();

    if (mAnimIndex != mOldAnimIndex)
    {
        std::string tempAnim = mHit ? "hit_" + std::to_string(mAnimIndex) : "idle_" + std::to_string(mAnimIndex);
        mAnimator->SetFlipX(mSpriteFlip);
        mAnimator->PlayAnim(tempAnim);

        mHit = false;
    }
}

void Zombie::GetDirection()
{
    mOldAnimIndex = mAnimIndex;

    Vector2 toCam = (clt::CameraComponent::GetActiveCamera()->GetWorldLocation().xz() - GetActorLocation().xz()).Normalized();
    Vector2 forward = GetTransform().Forward().xz().Normalized();
    Vector2 right = GetTransform().Right().xz().Normalized();

    float dotF = Vector2::Dot(forward, toCam);
    float dotR = Vector2::Dot(right, toCam);
    float angle = std::atan2(dotR, dotF);

    float degrees = angle * (180.0f / Maths::PI);
    if (degrees < 0) degrees += 360.0f;

    int index = 0;
    bool flip = false;

    if (degrees < 22.5f || degrees >= 337.5f)
    {
        mAnimIndex = 0; // Front
        mSpriteFlip = false;
    }
    else if (degrees < 67.5f)
    {
        mAnimIndex = 1; // Front Right
        mSpriteFlip = false;
    }
    else if (degrees < 112.5f)
    {
        mAnimIndex = 2; // Right
        mSpriteFlip = false;
    }
    else if (degrees < 157.5f)
    {
        mAnimIndex = 3; // Back Right
        mSpriteFlip = false;
    }
    else if (degrees < 202.5f)
    {
        mAnimIndex = 4; // Back
        mSpriteFlip = false;
    }
    else if (degrees < 247.5f)
    {
        mAnimIndex = 3;
        mSpriteFlip = true; // Back Left
    }
    else if (degrees < 292.5f)
    {
        mAnimIndex = 2;
        mSpriteFlip = true; // Left
    }
    else if (degrees < 337.5f)
    {
        mAnimIndex = 1;
        mSpriteFlip = true; // Front Left
    }
}

void Zombie::GetHit()
{
    if (mLife > 0)
    {
       // mHit = true;
        
        mLife--;
    }
    else
    {
        mAnimator->PlayAnim("death");
    }
}
