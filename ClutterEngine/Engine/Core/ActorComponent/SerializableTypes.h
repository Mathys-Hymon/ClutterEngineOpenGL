#pragma once

enum class EPropertyFlags : uint8_t
{
    None         = 0,
    Serializable = 1 << 0, // Value is saved in CLevel
    Editable     = 1 << 1, // Value is visible in editor
};

inline EPropertyFlags operator | (EPropertyFlags a, EPropertyFlags b)
{
    return static_cast<EPropertyFlags>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inline bool HasFlag(EPropertyFlags flags, EPropertyFlags flag)
{
    return (static_cast<uint8_t>(flags) & static_cast<uint8_t>(flag)) != 0;
}

enum class EPropertyType
{
    Float, Int, Bool, String, Vector2, Vector3, Vector4, Color, Quaternion, Texture
};

struct PropertyInfo
{
    std::string Name;
    size_t Offset; // offset of (Class, field)
    EPropertyType Type;
    EPropertyFlags Flags;
};