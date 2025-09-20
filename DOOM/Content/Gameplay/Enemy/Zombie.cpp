#include "Zombie.h"
#include "Character/DoomController.h"

Zombie::Zombie(clt::Level* pLevel, std::string pName) : clt::Actor(pLevel, pName), mLife(1), mOldAnimIndex(-1), mAnimIndex(0), mAttackMode(false), mDead(false)
{
    
	mAnimator = AddComponent<clt::AnimatorComponent>("idle_0", clt::Assets::Get().LoadTexture("Content/Resources/Sprites/Enemy/idle_front.png", "idle_Front", TextureFilter::NEAREST, false));

    mAnimator->AddNewAnim("death", clt::Assets::Get().BulkLoadTexture("Content/Resources/Sprites/Enemy/", 4, "_death.png", "death", TextureFilter::NEAREST, false), false);

    mAnimator->AddNewAnim("idle_1", clt::Assets::Get().LoadTexture("Content/Resources/Sprites/Enemy/idle_frontleft.png", "idle_FrontLeft", TextureFilter::NEAREST, false), false);

    mAnimator->AddNewAnim("idle_2", clt::Assets::Get().LoadTexture("Content/Resources/Sprites/Enemy/idle_left.png", "idle_Left", TextureFilter::NEAREST, false), false);

    mAnimator->AddNewAnim("idle_3", clt::Assets::Get().LoadTexture("Content/Resources/Sprites/Enemy/idle_backleft.png", "idle_BackLeft", TextureFilter::NEAREST, false), false);
    
    mAnimator->AddNewAnim("idle_4", clt::Assets::Get().LoadTexture("Content/Resources/Sprites/Enemy/idle_back.png", "idle_Back", TextureFilter::NEAREST, false), false);

    mAnimator->AddNewAnim("hitAnim", clt::Assets::Get().LoadTexture("Content/Resources/Sprites/Enemy/hitAnim.png", "hitAnim", TextureFilter::NEAREST, false), false);

    mAnimator->AddNewAnim("shoot", clt::Assets::Get().LoadTexture("Content/Resources/Sprites/Enemy/shoot.png", "shootAnim", TextureFilter::NEAREST, false), false);

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

    if (!mDead && !mHit)
    {
        if (mAttackMode)
        {
            mShootDelay += clt::Timer::deltaTime;

            if (mShootDelay < 1)
            {
                mShooted = false;
                mAnimator->PlayAnim("idle_0");
            }
            else
            {
                mAnimator->PlayAnim("shoot");

                if (!mShooted)
                {
                    mShooted = true;
                    RaycastHit hitResult;

                    LineTrace(GetActorLocation(), -mAnimator->GetWorldTransform().Forward(), 150, hitResult);

                    DoomController* temp = hitResult.Actor->GetComponentOfType<DoomController>();
                    if (temp) temp->GetHit();
                }

                if (mShootDelay > 1.2f)
                {
                    mShootDelay = 0;
                }
            }
        }
        else
        {
            if (mLife > 0) GetDirection();

            if (mAnimIndex != mOldAnimIndex)
            {
                std::string tempAnim = "idle_" + std::to_string(mAnimIndex);
                mAnimator->SetFlipX(mSpriteFlip);
                mAnimator->PlayAnim(tempAnim);
            }
        }
    }
    else if (mHit)
    {
        mAnimator->PlayAnim("hitAnim");
        mAnimator->SetFlipX(false);
        
        if (mHitDelay > 0.2f)
        {
            mHit = false;
        }
        else
        {
            mHitDelay += clt::Timer::deltaTime;
        }
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
    if (!mDead)
    {
        if (mLife > 0)
        {
            mLife--;
            mAttackMode = true;
            mHit = true;
        }
        else
        {
            mAnimator->PlayAnim("death");
            RemoveComponent<clt::OBBCollider>();
            mDead = true;
        }
    }
}
