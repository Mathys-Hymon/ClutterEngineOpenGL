#pragma once
#include <Core/CCommon.h>
#include <Core/Maths/Color.h>
#include <string>
#include <vector>
#include <variant>
#include <optional>

namespace clt
{
    // Types de données manipulables
    enum class CLUTTER_API NodeType
    {
        Any,
        Float,
        Int,
        Bool,
        Vector2,
        Vector3,
        Color,
        Texture
    };

    // Catégorie du node
    enum class CLUTTER_API NodeKind
    {
        // Math operations
        Add,
        Subtract,
        Multiply,
        Divide,
        Equal,
        Select,

        // Break / Make nodes
        BreakVector2,
        BreakVector3,
        BreakColor,
        MakeVector2,
        MakeVector3,
        MakeColor,

        // Constants
        FloatConstant,
        IntConstant,
        BoolConstant,
        Vector2Constant,
        Vector3Constant,
        ColorConstant,
        TextureConstant,

        // Entry nodes
        Time,
        TexCoord,

        // Utils / extras
        VectorLength,
        OutResult,
    };

    inline std::string NodeTypeToString(NodeType type)
    {
        switch (type)
        {
        case NodeType::Float:     return "Float";
        case NodeType::Vector2:   return "Vector2";
        case NodeType::Vector3:   return "Vector3";
        case NodeType::Color:     return "Color";
        case NodeType::Texture:   return "Texture";
        case NodeType::Bool:      return "Bool";
        case NodeType::Int:       return "Int";
        case NodeType::Any:       return "Any";
        default:                  return "Unknown";
        }
    }

    using NodeValue = std::variant<std::monostate, float, int, bool, Vector2, Vector3, Color, std::string>;

    struct CLUTTER_API Slot
    {
        NodeType type;                   
        NodeValue value;                   
        int connectedNode{ -1 }; // node connected
        int connectedSlot{ -1 }; // output slot connected
    };

    // Node complet
    struct CLUTTER_API Node
    {
        const char* name;
        size_t templateIndex;
        NodeKind kind;
        Vector2 pos;
        Vector2 size;
        bool mSelected;

        std::vector<Slot> inputs; 
        std::vector<Slot> outputs;
    };
}
