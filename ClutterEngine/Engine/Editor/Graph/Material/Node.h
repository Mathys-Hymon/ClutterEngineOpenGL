#pragma once
#include <Core/CCommon.h>
#include <Core/Maths/Vectors/Vector2.h>
#include <string>
#include <vector>
#include <optional>

namespace clt
{
    struct CLUTTER_API Node
    {
        const char* name;
        size_t templateIndex;
        Vector2 pos;
        Vector2 size;
        bool mSelected;
    };

    struct CLUTTER_API Link
    {
        size_t inputNode;
        size_t inputSlot;
        size_t outputNode;
        size_t outputSlot;
    };
}
