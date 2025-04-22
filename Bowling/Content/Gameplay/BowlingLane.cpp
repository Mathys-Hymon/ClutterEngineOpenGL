#include "BowlingLane.h"


clt::CubeActor* laneFloor1;
clt::CubeActor* laneFloor2;
clt::CubeActor* gutterActor;
clt::CubeActor* bannerActor;


BowlingLane::BowlingLane(clt::Level* pLevel, std::string pName, bool isStatic,  Vector3 location) : clt::Actor(pLevel, pName)
{
    SetActorLocation(location);

	RespawnPins(true, isStatic);
    RespawnPins(false, isStatic);

    laneFloor1 = pLevel->AddActor<clt::CubeActor>("floor", clt::Assets::Get().GetTexture("floor"), false, Vector2{ 15,30 });

    laneFloor1->GetComponentOfType<clt::OBBCollider>()->mFriction = 0.1f;
    laneFloor1->SetActorScale({ 1.1f, 0.3f, 15 });
    laneFloor1->SetActorLocation(GetActorLocation() + Vector3{ -1.5f, -2, 0 });

    laneFloor2 = pLevel->AddActor<clt::CubeActor>("floor2", false, Vector2{ 15,30 });

    laneFloor2->GetComponentOfType<clt::OBBCollider>()->mFriction = 0.1f;
    laneFloor2->SetActorScale({ 1.1f, 0.3f, 15 });
    laneFloor2->SetActorLocation(GetActorLocation() + Vector3{ 1.5f, -2, 0 });

    bannerActor = pLevel->AddActor<clt::CubeActor>("banner", false);

    bannerActor->GetComponentOfType<clt::MeshComponent>()->SetTexture(clt::Assets::Get().GetTexture("banner"), 1);
    bannerActor->SetActorScale({ 1.5f,3.0f,0.1f });
    bannerActor->SetActorRotation({ 0,0, 90 });
    bannerActor->SetActorLocation(GetActorLocation()+ Vector3{ 0, 1, 10 });
    bannerActor->GetComponentOfType<clt::MeshComponent>()->SetTexture(clt::Assets::Get().GetTexture("banner"), 1);

    //gutterActor = pLevel->AddActor<clt::CubeActor>("gutter", false);
}

BowlingLane::~BowlingLane()
{
	mPinsLeft.clear();
}

void BowlingLane::RespawnPins(bool leftLane, bool isStatic)
{
    int totalRows = 4;
    float spacing = 0.6f;
    float startX;
    float y;
    float startZ;

    if (leftLane)
    {
        startX = GetActorLocation().x - 1.5f;
        y = GetActorLocation().y - 1.7f;
        startZ = GetActorLocation().z + 9.5f;

        for (clt::Actor* pin : mPinsLeft)
        {
            GetLevel()->DestroyActor<clt::Actor>(pin);
        }

        mPinsLeft.clear();
    }
    else
    {
        startX = GetActorLocation().x + 1.5f;
        y = GetActorLocation().y - 1.7f;
        startZ = GetActorLocation().z + 9.5f;

        for (clt::Actor* pin : mPinsRight)
        {
            GetLevel()->DestroyActor<clt::Actor>(pin);
        }

        mPinsRight.clear();
    }

    for (int row = 0; row < totalRows; ++row) {
        int pinsInRow = row + 1;

        float rowStartX = startX - (spacing * row / 2.0f);
        float z = startZ + row * spacing;

        for (int i = 0; i < pinsInRow; ++i) {
            float x = rowStartX + i * spacing;

            clt::Actor* tempActor = GetLevel()->AddActor<clt::Actor>("pin");
            tempActor->SetActorLocation({ x, y, z });
            tempActor->AddComponent<clt::MeshComponent>(clt::Assets::Get().GetMesh("pin"));

            if (!isStatic)
            {
                tempActor->AddComponent<clt::OBBCollider>(Vector3{ 10, 20, 10 })->SetRelativeLocation({ 0, 0.2f, 0 });
                tempActor->GetComponentOfType<clt::OBBCollider>()->mFriction = 0.5f;
                tempActor->AddComponent<clt::RigidBody>()->mLockRotation = false;
            }
            tempActor->SetActorScale(0.1f);

            if (leftLane) mPinsLeft.push_back(tempActor);
            else mPinsRight.push_back(tempActor);
        }
    }
}
