#pragma once
#include <Core/CCommon.h>
#include <Core/Maths/Color.h>
#include <string>
#include <vector>
#include <variant>
#include <Editor/Graph/Material/Node.h>
#include <GraphEditor.h>

namespace clt
{
    using NodeValue = std::variant<std::monostate, float, int, bool, Vector2, Vector3, Color, std::string>;

    struct CLUTTER_API NodeTemplate
    {
        const char* name;
        NodeKind kind;
        size_t templateIndex;
        Vector2 defaultSize;
        std::vector<Slot> inputs;
        std::vector<Slot> outputs;
    };

    inline const std::vector<NodeTemplate> NodeTemplates = {

        // --- OutResult ---
        { "OutResult", NodeKind::OutResult, 0, {175,450},
            {
                {NodeType::Any, 0.0f}, {NodeType::Any, 0.0f}, {NodeType::Any, 0.0f},
                {NodeType::Any, 0.0f}, {NodeType::Any, 0.0f}, {NodeType::Any, 0.0f},
                {NodeType::Any, 0.0f}, {NodeType::Any, 0.0f}, {NodeType::Any, 0.0f},
                {NodeType::Any, 0.0f}
            }, // inputs
            { {NodeType::Any, 0.0f} } // outputs
        },

        // --- Math operations ---
        { "Add", NodeKind::Add, 1, {100,60},
            { {NodeType::Any, 0.0f}, {NodeType::Any, 0.0f} },
            { {NodeType::Any, 0.0f} }
        },
        { "Subtract", NodeKind::Subtract, 2, {100,60},
            { {NodeType::Any, 0.0f}, {NodeType::Any, 0.0f} },
            { {NodeType::Any, 0.0f} }
        },
        { "Multiply", NodeKind::Multiply, 3, {100,60},
            { {NodeType::Any, 0.0f}, {NodeType::Any, 0.0f} },
            { {NodeType::Any, 0.0f} }
        },
        { "Divide", NodeKind::Divide, 4, {100,60},
            { {NodeType::Any, 0.0f}, {NodeType::Any, 0.0f} },
            { {NodeType::Any, 0.0f} }
        },
        { "Equal", NodeKind::Equal, 5, {100,60},
            { {NodeType::Any, 0.0f}, {NodeType::Any, 0.0f} },
            { {NodeType::Bool, false} }
        },
        { "Select", NodeKind::Select, 6, {150,100},
            { {NodeType::Any, 0.0f}, {NodeType::Any, 0.0f}, {NodeType::Bool, false} },
            { {NodeType::Any, 0.0f} }
        },

        // --- Break nodes ---
        { "Break Vector2", NodeKind::BreakVector2, 7, {200,100},
            { {NodeType::Vector2, Vector2{0,0}} },
            { {NodeType::Float, 0.f}, {NodeType::Float, 0.f} }
        },
        { "Break Vector3", NodeKind::BreakVector3, 8, {200,120},
            { {NodeType::Vector3, Vector3{0,0,0}} },
            { {NodeType::Float, 0.f}, {NodeType::Float, 0.f}, {NodeType::Float, 0.f} }
        },
        { "Break Color", NodeKind::BreakColor, 9, {200,120},
            { {NodeType::Color, Color{1,1,1}} },
            { {NodeType::Float, 1.f}, {NodeType::Float, 1.f}, {NodeType::Float, 1.f}, {NodeType::Float, 1.f} }
        },

        // --- Make nodes ---
        { "Make Vector2", NodeKind::MakeVector2, 10, {200,100},
            { {NodeType::Float, 0.f}, {NodeType::Float, 0.f} },
            { {NodeType::Vector2, Vector2{0,0}} }
        },
        { "Make Vector3", NodeKind::MakeVector3, 11, {200,120},
            { {NodeType::Float, 0.f}, {NodeType::Float, 0.f}, {NodeType::Float, 0.f} },
            { {NodeType::Vector3, Vector3{0,0,0}} }
        },
        { "Make Color", NodeKind::MakeColor, 12, {200,120},
            { {NodeType::Float, 1.f}, {NodeType::Float, 1.f}, {NodeType::Float, 1.f}, {NodeType::Float, 1.f} },
            { {NodeType::Color, Color{1,1,1}} }
        },

        // --- Constants ---
        { "Float", NodeKind::FloatConstant, 13, {75,60}, {}, { {NodeType::Float, 0.f} } },
        { "Int", NodeKind::IntConstant, 14, {75,60}, {}, { {NodeType::Int, 0} } },
        { "Bool", NodeKind::BoolConstant, 15, {75,60}, {}, { {NodeType::Bool, false} } },
        { "Vector2", NodeKind::Vector2Constant, 16, {75,60}, {}, { {NodeType::Vector2, Vector2{0,0}} } },
        { "Vector3", NodeKind::Vector3Constant, 17, {75,60}, {}, { {NodeType::Vector3, Vector3{0,0,0}} } },
        { "Color", NodeKind::ColorConstant, 18, {75,60}, {}, { {NodeType::Color, Color{1,1,1}} } },
        { "Texture", NodeKind::TextureConstant, 19, {200,200}, {}, { {NodeType::Texture, ""} } },

        // --- Entry nodes ---
        { "Time", NodeKind::Time, 20, {100,75}, {}, { {NodeType::Float, 0.f} } },
        { "TexCoord", NodeKind::TexCoord, 21, {100,75}, {}, { {NodeType::Vector2, Vector2{0,0}} } },

        // --- Extras ---
        { "VectorLength", NodeKind::VectorLength, 22, {100,65}, { {NodeType::Vector2, Vector2{0,0}} }, { {NodeType::Float, 0.f} } }

    };
}
