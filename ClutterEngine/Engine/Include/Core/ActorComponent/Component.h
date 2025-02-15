#pragma once
#include <Core/CCommon.h>

class Actor;
class CLUTTER_API Component
{
protected:
    bool mIsEnable = true; ///< Indicates if the component is active.
    int mUpdateOrder = 0; ///< The order in which the component is updated.
    Actor* mOwner; ///< The actor that owns this component.

public:

    Component(int pUpdateOrder = 0);
    ~Component() {};

    virtual void Start() {};
    virtual void Update() {};

    void Enable(bool pEnable) { mIsEnable = pEnable; };
    void OnDestroy() {};

    bool IsEnable() const { return mIsEnable; }
    int GetUpdateOrder() const { return mUpdateOrder; }

    friend Actor;
};