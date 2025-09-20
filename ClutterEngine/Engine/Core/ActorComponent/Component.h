#pragma once
#include <Core/CCommon.h>
#include <Core/ActorComponent/Actor.h>

namespace clt
{
    /**
     * @brief Base class for all components attached to an Actor.
     */
    class CLUTTER_API Component
    {

    protected:
        bool mIsActive = true; ///< Indicates if the component is active.
        int mUpdateOrder = 0; ///< The order in which the component is updated.
        Actor* mOwner; ///< The actor that owns this component.

        Transform mRelativeTransform;

        virtual void SetOwner(Actor* pOwner) 
        { 
            mOwner = pOwner;
            Start();
        };

        bool LineTrace(const Vector3& start, const Vector3& direction, float maxDistance, RaycastHit& outHit, const TraceParams& params)
        {
            if (mOwner) return mOwner->LineTrace(start, direction, maxDistance, outHit, params);
            else return false;
        };

    public:
        /**
         * @brief Constructor for Component.
         * @param pOwner The actor that owns this component.
         * @param pUpdateOrder The order in which the component is updated.
         */
        Component(int pUpdateOrder = 0) : mUpdateOrder(pUpdateOrder), mOwner(nullptr) {};

        /**
         * @brief Virtual destructor for Component.
         */
        virtual ~Component() = default;

        /**
         * @brief Called when the component is started.
         */
        virtual void Start() {};

        /**
         * @brief Called every frame to update the component.
         */
        virtual void Update() {};

        virtual void Destroy() {};

        /**
         * @brief Enables or disables the component.
         * @param pEnable True to enable the component, false to disable it.
         */
        void SetActive(bool pActive) { mIsActive = pActive; };

        /**
         * @brief Called when the component is destroyed.
         */
        void OnDestroy() {};

        /**
         * @brief Checks if the component is enabled.
         * @return True if the component is enabled, false otherwise.
         */
        bool IsActive() const { return mIsActive; }

        /**
         * @brief Gets the update order of the component.
         * @return The update order of the component.
         */
        int GetUpdateOrder() const { return mUpdateOrder; }

        void SetRelativeLocation(const Vector3& loc) 
        { 
            mRelativeTransform.SetLocation(loc);
        };

        void SetRelativeLocation(const Vector2& loc)
        {
            mRelativeTransform.SetLocation(loc); 
        };

        void SetWorldLocation(const Vector3& loc)
        {
            if (!mOwner)
                return;

            Vector3 ownerLocation = mOwner->GetActorLocation();
            Quaternion ownerRotation = mOwner->GetRotation();
            Vector3 localPosition = Vector3::Transform(loc - ownerLocation, ownerRotation.Inverse());

            Vector3 parentScale = mOwner->GetScale();
            localPosition = localPosition / parentScale;

            SetRelativeLocation(localPosition);
        }

        void SetRelativeScale(const Vector3& scale)  
        { 
            mRelativeTransform.SetScale(scale);
        };
        void SetRelativeScale(const Vector2& scale) 
        { 
            mRelativeTransform.SetScale(scale);
        };
        void SetRelativeRotation(Quaternion rot)    
        { 
            mRelativeTransform.SetRotation(rot);
        };

        void SetRelativeRotation(Vector3 rot)
        {
            mRelativeTransform.SetRotation(rot);
        };


        void SetWorldRotation(const Quaternion& rot)
        {
            if (mOwner)
            {
                Quaternion ownerRotation = mOwner->GetRotation();
                Quaternion relativeRotation = Quaternion::Concatenate(ownerRotation, rot);
                mRelativeTransform.SetRotation(relativeRotation);
            }
        }

        void SetWorldRotation(const Vector3& rot)
        {
            Quaternion worldRotation = Quaternion::FromEuler(rot);
            SetWorldRotation(worldRotation);
        }
        void AddRelativeRotation(Vector3 rot)
        {
            mRelativeTransform.AddRotation(rot);
        };

        void SetRelativeRotation(float rot) 
        { 
            mRelativeTransform.SetRotation(rot);
        };
        void SetRelativeTransform(Transform& transform) 
        {
            SetRelativeLocation(transform.Location());
            SetRelativeScale(transform.Scale());
            SetRelativeRotation(transform.Rotation());
        };

        Vector3 GetRelativeLocation()      const { return mRelativeTransform.Location(); };
        Vector3 GetRelativeScale()         const { return mRelativeTransform.Scale();    };
        Quaternion GetRelativeRotation()   const { return mRelativeTransform.Rotation(); };
        Vector3 GetRelativeRotationEuler()   const { return mRelativeTransform.EulerRotation(); };
        Transform GetRelativeTransform()   const { return mRelativeTransform;            };

        Vector3 GetWorldLocation()         const 
        { 
            if (!mOwner) return Vector3::Zero;

            return mOwner->GetActorLocation() +
                mRelativeTransform.Location().x * mOwner->GetTransform().Right() +
                mRelativeTransform.Location().y * mOwner->GetTransform().Up() +
                mRelativeTransform.Location().z * mOwner->GetTransform().Forward();
        };

        Vector3 GetWorldScale()            const { return mRelativeTransform.Scale() * mOwner->GetScale();            };
        Quaternion GetWorldRotation()      const { return Quaternion::Concatenate(mOwner->GetRotation(), mRelativeTransform.Rotation()); };
        virtual Transform GetWorldTransform() const
        {
            if (!mOwner) return Transform{};

            return
            {
                GetWorldLocation(),
                GetWorldScale(),
                GetWorldRotation()
            };
        };

        Actor* GetOwner() const { return mOwner; };

        friend Actor;
    };
}
