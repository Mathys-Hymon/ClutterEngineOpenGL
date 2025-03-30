#pragma once
#include "Graphics/RendererGL.h"
#include "Core/ActorComponent/Actor.h"

namespace clt
{
    class Physics;
    class LevelManager;
    /**
     * @brief Represents a level in the game engine.
     */
    class CLUTTER_API Level
    {
        bool mUpdatingActors; ///< Indicates if actors are currently being updated.
        
        /**
         * @brief Updates all actors in the level.
         */
        void UpdateActors();

    protected:
        std::string mTitle; ///< The title of the scene.
        RendererGL* mRenderer; ///< The renderer used for drawing the scene.
        Physics* mPhysics;

        std::unordered_map < size_t, std::vector<Actor*> > mActors; ///< Map of actors categorized by their type.
        std::vector<Actor*> mPendingActors; ///< List of actors pending to be added to the level.
        std::vector<Actor*> mDeadActors; ///< List of actors pending to be removed from the level.

        /**
         * @brief Updates the level. Must be implemented by derived classes.
         */
        virtual void Update() = 0;

    public:

        static Level* ActiveScene; ///< Pointer to the currently active scene.

        /**
         * @brief Constructs a new level with the given title.
         * @param pTitle The title of the scene.
         */
        Level(std::string pTitle = "Scene");

        /**
         * @brief Destroys the level and cleans up resources.
         */
        ~Level();

        //template<typename T>
        //std::vector<T*> GetAllActorsOfClass();

        /**
         * @brief Loads the level. Must be implemented by derived classes.
         */
        virtual void Load() = 0;

        /**
         * @brief Sets the renderer for the level.
         * @param pRenderer Pointer to the renderer.
         */
        void SetManager(RendererGL* pRenderer, Physics* pPhysics) 
        { 
            mRenderer = pRenderer; 
            mPhysics = pPhysics;
        };

        /**
         * @brief Internal update function called by the engine.
         */
        void InternalUpdate();

        //void Render();

        /**
         * @brief Closes the level. Must be implemented by derived classes.
         */
        virtual void Close() = 0;

        /**
         * @brief Unloads the level and cleans up resources.
         */
        void Unload();

        template<typename T, typename... Args>
        T* AddActor(Args&&... args);
        /**
         * @brief Removes an actor from the level.
         * @param pActor Pointer to the actor to be removed.
         */
        void DestroyActor(Actor* pActor);

        template<typename T>
        std::vector<T*> GetAllActorOfType()
        {
            static_assert(std::is_base_of<Actor, T>::value, "T must be an Actor");

            size_t hashCode = typeid(T).hash_code();
            auto it = mActors.find(hashCode);
            if (it != mActors.end()) 
            {
                return static_cast<std::vector<T*>>(it->second);
            }
            else
            {
                std::vector<T*> temp;
                return temp;
            }
        };

        template<typename T>
        T* GetActorOfType()
        {
            static_assert(std::is_base_of<Actor, T>::value, "T must be an Actor");

            size_t hashCode = typeid(T).hash_code();
            auto it = mActors.find(hashCode);
            if (it != mActors.end()) 
            {
                return static_cast<T*>(it->second[0]);
            }
            else
            {
                return nullptr;
            }
        };

        /**
         * @brief Gets the renderer for the level.
         * @return Reference to the renderer.
         */
        RendererGL& GetRenderer() const { return *mRenderer; };
        Physics& GetPhysics()   const { return *mPhysics;  };

        friend LevelManager;
    };

    template<typename T, typename ...Args>
    inline T* Level::AddActor(Args && ...args)
    {
        static_assert(std::is_base_of<Actor, T>::value, "T must be an Actor");
        size_t hashCode = typeid(T).hash_code();

            T* pActor = new T(std::forward<Args>(args)...);

            if(mUpdatingActors) mPendingActors.emplace_back(pActor);
            else
            {
                mActors[hashCode].emplace_back(pActor);
                pActor->mLevel = this;
            }

            return pActor;
    }
}