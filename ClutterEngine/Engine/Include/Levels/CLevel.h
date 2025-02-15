#pragma once
#include "Graphics/Renderer.h"
#include "Core/ActorComponent/Actor.h"
//#include "EngineContent/Assets/Assets.h"

namespace clt
{
    class CLevel
    {
    public:

        static CLevel* ActiveScene;

        CLevel(std::string pTitle = "Scene");
        ~CLevel();

        //virtual void Load() {};
        //virtual void SetRenderer(Renderer* pRenderer);
        //virtual void Tick();
        //virtual void Render();
        //virtual void Close();
        //virtual void Unload();

        //void AddActor(Actor* pActor);
        //void RemoveActor(Actor* pActor);
        //void updateActors();

        Renderer& GetRenderer() const { return *mRenderer; };

    protected:
        std::string mTitle; ///< The title of the scene.
        std::shared_ptr<Renderer> mRenderer; ///< The renderer used for drawing the scene.
        //PhysicEngine* mPhysic;

        bool mUpdatingActors;

        std::vector<Actor*> mPendingActors;
        std::vector<Actor*> mDeadActors;
        std::vector<Actor*> mActors;
    };
}