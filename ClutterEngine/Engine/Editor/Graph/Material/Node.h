#pragma once
#include <Core/CCommon.h>
#include <Core/Maths/Vectors/Vector2.h>
#include <string>
#include <vector>
#include <optional>
#include <variant>

namespace clt
{
    enum class CLUTTER_API NodeType
    {
        Float,
        Vector2,
        Vector3,
        Texture,
        Add,
        Multiply,
        Divide,
        Break
    };

    using NodeValue = std::variant<std::monostate, float, Vector2, Vector3, std::string>;

    struct CLUTTER_API Node
    {
        const char* name;
        size_t templateIndex;
        Vector2 pos;
        Vector2 size;
        NodeValue value;
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
