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
        Physics* mPhysics; ///< The physics system used in the level.
        LevelManager* mManager; ///< The manager responsible for this level.

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
         * @brief Sets the renderer, physics, and manager for the level.
         * @param pRenderer Pointer to the renderer.
         * @param pPhysics Pointer to the physics system.
         * @param pManager Pointer to the level manager.
         */
        void SetManager(RendererGL* pRenderer, Physics* pPhysics, LevelManager* pManager) 
        { 
            mRenderer = pRenderer; 
            mPhysics = pPhysics;
            mManager = pManager;
        };

        /**
         * @brief Opens a new level by name.
         * @param pLevelName The name of the level to open.
         */
        void OpenLevel(const std::string& pLevelName);

        /**
         * @brief Performs a line trace (raycast) in the level.
         * @param start The start position of the trace.
         * @param direction The direction of the trace.
         * @param maxDistance The maximum distance for the trace.
         * @param hit The result of the raycast.
         * @param debugPersistant Whether to persist debug visualization.
         * @param self The actor to ignore during the trace.
         * @return True if something was hit, false otherwise.
         */
        bool LineTrace(Vector3 start, Vector3 direction, float maxDistance, raycastHit& hit, bool debugPersistant = false, Actor* self = nullptr);

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

        /**
         * @brief Adds an actor of type T to the level.
         * @tparam T The type of actor to add.
         * @tparam Args The constructor arguments for the actor.
         * @param args The arguments to forward to the actor's constructor.
         * @return Pointer to the newly created actor.
         */
        template<typename T, typename... Args>
        T* AddActor(Args&&... args);

        /**
         * @brief Removes an actor from the level.
         * @tparam T The type of actor to remove.
         * @param pActor Pointer to the actor to be removed.
         */
        template<typename T>
        void DestroyActor(Actor* pActor);

        /**
         * @brief Gets all actors of a specific type.
         * @tparam T The type of actors to retrieve.
         * @return A vector of pointers to actors of type T.
         */
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

        /**
         * @brief Gets the first actor of a specific type.
         * @tparam T The type of actor to retrieve.
         * @return Pointer to the first actor of type T, or nullptr if none found.
         */
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

        /**
         * @brief Gets the physics system for the level.
         * @return Reference to the physics system.
         */
        Physics& GetPhysics()   const { return *mPhysics;  };

        friend LevelManager;
    };

    /**
     * @brief Adds an actor of type T to the level.
     * @tparam T The type of actor to add.
     * @tparam Args The constructor arguments for the actor.
     * @param args The arguments to forward to the actor's constructor.
     * @return Pointer to the newly created actor.
     */
    template<typename T, typename... Args>
    inline T* Level::AddActor(Args&&... args)
    {
        static_assert(std::is_base_of<Actor, T>::value, "T must be an Actor");
        size_t hashCode = typeid(T).hash_code();

        T* pActor = new T(this, std::forward<Args>(args)...);

        if(mUpdatingActors) mPendingActors.emplace_back(pActor);
        else
        {
            pActor->mLevel = this;
            mActors[hashCode].emplace_back(pActor);
            pActor->Start();
        }

        return pActor;
    }

    /**
     * @brief Removes an actor from the level.
     * @tparam T The type of actor to remove.
     * @param pActor Pointer to the actor to be removed.
     */
    template<typename T>
    inline void Level::DestroyActor(Actor* pActor)
    {
        static_assert(std::is_base_of<Actor, T>::value, "T must be an Actor");
        size_t hashCode = typeid(T).hash_code();

        auto& actors = mActors[hashCode];
        auto it = std::find(actors.begin(), actors.end(), pActor);

        if (it == actors.end()) return;
        else
        {
            pActor->mState = ActorState::Dead;
            mDeadActors.push_back(pActor);
            pActor->Destroy();

            actors.erase(it);

            pActor = nullptr;
        }
    }
}
