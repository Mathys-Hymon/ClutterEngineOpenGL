#pragma once
#include "Graphics/Renderer.h"
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
        Renderer* mRenderer; ///< The renderer used for drawing the scene.
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
        void SetManager(Renderer* pRenderer, Physics* pPhysics) 
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

        /**
         * @brief Adds an actor to the level.
         * @param pActor Pointer to the actor to be added.
         */
        Actor* AddActor(Actor* pActor);

        /**
         * @brief Removes an actor from the level.
         * @param pActor Pointer to the actor to be removed.
         */
        void RemoveActor(Actor* pActor);

        /**
         * @brief Gets the renderer for the level.
         * @return Reference to the renderer.
         */
        Renderer& GetRenderer() const { return *mRenderer; };
        Physics& GetPhysics()   const { return *mPhysics;  };

        friend LevelManager;
    };
}