#pragma once
#include "Graphics/Renderer.h"
#include "Core/ActorComponent/Actor.h"
//#include "EngineContent/Assets/Assets.h"

namespace clt
{
    class CLevelManager;
    class CLUTTER_API CLevel
    {
        bool mUpdatingActors;
        void UpdateActors();

    protected:
        std::string mTitle; ///< The title of the scene.
        Renderer* mRenderer; ///< The renderer used for drawing the scene.
        //PhysicEngine* mPhysic;

        std::unordered_map < size_t, std::vector<Actor*> > mActors;
        std::vector<Actor*> mPendingActors;
        std::vector<Actor*> mDeadActors;

        virtual void Update() {};

    public:

        static CLevel* ActiveScene;

        CLevel(std::string pTitle = "Scene");
        ~CLevel();

        //template<typename T>
        //std::vector<T*> GetAllActorsOfClass();

        //template<typename T>
        //T* GetActorOfClass();

        virtual void Load() {};

        void SetRenderer(Renderer* pRenderer) { mRenderer = pRenderer; };
        void InternalUpdate();
        //void Render();

        virtual void Close() {};

        void Unload();

        void AddActor(Actor* pActor);
        void RemoveActor(Actor* pActor);

        Renderer& GetRenderer() const { return *mRenderer; };

        friend CLevelManager;
    };
}