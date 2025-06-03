#pragma once  
#include <Core/CCommon.h>  
#include <GLFW/glfw3.h>  

/**
 * @brief Enumeration of all supported keyboard keys.
 * 
 * Maps to GLFW key codes.
 */
enum class CLUTTER_API EKey 
{  
    A = GLFW_KEY_A,  
    B = GLFW_KEY_B,  
    C = GLFW_KEY_C,  
    D = GLFW_KEY_D,  
    E = GLFW_KEY_E,  
    F = GLFW_KEY_F,  
    G = GLFW_KEY_G,  
    H = GLFW_KEY_H,  
    I = GLFW_KEY_I,  
    J = GLFW_KEY_J,  
    K = GLFW_KEY_K,  
    L = GLFW_KEY_L,  
    M = GLFW_KEY_M,  
    N = GLFW_KEY_N,  
    O = GLFW_KEY_O,  
    P = GLFW_KEY_P,  
    Q = GLFW_KEY_Q,  
    R = GLFW_KEY_R,  
    S = GLFW_KEY_S,  
    T = GLFW_KEY_T,  
    U = GLFW_KEY_U,  
    V = GLFW_KEY_V,  
    W = GLFW_KEY_W,  
    X = GLFW_KEY_X,  
    Y = GLFW_KEY_Y,  
    Z = GLFW_KEY_Z,  
    Space = GLFW_KEY_SPACE,  
    Escape = GLFW_KEY_ESCAPE,  
    Apostrophe = GLFW_KEY_APOSTROPHE,  
    Comma = GLFW_KEY_COMMA,  
    Minus = GLFW_KEY_MINUS,  
    Period = GLFW_KEY_PERIOD,  
    Slash = GLFW_KEY_SLASH,  
    Semicolon = GLFW_KEY_SEMICOLON,  
    Equal = GLFW_KEY_EQUAL,  
    LeftBracket = GLFW_KEY_LEFT_BRACKET,  
    Backslash = GLFW_KEY_BACKSLASH,  
    RightBracket = GLFW_KEY_RIGHT_BRACKET,  
    GraveAccent = GLFW_KEY_GRAVE_ACCENT,  
    World1 = GLFW_KEY_WORLD_1,  
    World2 = GLFW_KEY_WORLD_2,  
    D0 = GLFW_KEY_0,  
    D1 = GLFW_KEY_1,  
    D2 = GLFW_KEY_2,  
    D3 = GLFW_KEY_3,  
    D4 = GLFW_KEY_4,  
    D5 = GLFW_KEY_5,  
    D6 = GLFW_KEY_6,  
    D7 = GLFW_KEY_7,  
    D8 = GLFW_KEY_8,  
    D9 = GLFW_KEY_9,  
    F1 = GLFW_KEY_F1,  
    F2 = GLFW_KEY_F2,  
    F3 = GLFW_KEY_F3,  
    F4 = GLFW_KEY_F4,  
    F5 = GLFW_KEY_F5,  
    F6 = GLFW_KEY_F6,  
    F7 = GLFW_KEY_F7,  
    F8 = GLFW_KEY_F8,  
    F9 = GLFW_KEY_F9,  
    F10 = GLFW_KEY_F10,  
    F11 = GLFW_KEY_F11,  
    F12 = GLFW_KEY_F12,  
    F13 = GLFW_KEY_F13,  
    F14 = GLFW_KEY_F14,  
    F15 = GLFW_KEY_F15,  
    F16 = GLFW_KEY_F16,  
    F17 = GLFW_KEY_F17,  
    F18 = GLFW_KEY_F18,  
    F19 = GLFW_KEY_F19,  
    F20 = GLFW_KEY_F20,  
    F21 = GLFW_KEY_F21,  
    F22 = GLFW_KEY_F22,  
    F23 = GLFW_KEY_F23,  
    F24 = GLFW_KEY_F24,  
    F25 = GLFW_KEY_F25,  
    Up = GLFW_KEY_UP,  
    Down = GLFW_KEY_DOWN,  
    Left = GLFW_KEY_LEFT,  
    Right = GLFW_KEY_RIGHT,  
    LeftShift = GLFW_KEY_LEFT_SHIFT,  
    LeftControl = GLFW_KEY_LEFT_CONTROL,  
    LeftAlt = GLFW_KEY_LEFT_ALT,  
    LeftSuper = GLFW_KEY_LEFT_SUPER,  
    RightShift = GLFW_KEY_RIGHT_SHIFT,  
    RightControl = GLFW_KEY_RIGHT_CONTROL,  
    RightAlt = GLFW_KEY_RIGHT_ALT,  
    RightSuper = GLFW_KEY_RIGHT_SUPER,  
    Menu = GLFW_KEY_MENU,  
    Tab = GLFW_KEY_TAB,  
    CapsLock = GLFW_KEY_CAPS_LOCK,  
    ScrollLock = GLFW_KEY_SCROLL_LOCK,  
    NumLock = GLFW_KEY_NUM_LOCK,  
    PrintScreen = GLFW_KEY_PRINT_SCREEN,  
    Pause = GLFW_KEY_PAUSE,  
    Insert = GLFW_KEY_INSERT,  
    Home = GLFW_KEY_HOME,  
    PageUp = GLFW_KEY_PAGE_UP,  
    Delete = GLFW_KEY_DELETE,  
    End = GLFW_KEY_END,  
    PageDown = GLFW_KEY_PAGE_DOWN,  
    KP0 = GLFW_KEY_KP_0,  
    KP1 = GLFW_KEY_KP_1,  
    KP2 = GLFW_KEY_KP_2,  
    KP3 = GLFW_KEY_KP_3,  
    KP4 = GLFW_KEY_KP_4,  
    KP5 = GLFW_KEY_KP_5,  
    KP6 = GLFW_KEY_KP_6,  
    KP7 = GLFW_KEY_KP_7,  
    KP8 = GLFW_KEY_KP_8,  
    KP9 = GLFW_KEY_KP_9,  
    KPDecimal = GLFW_KEY_KP_DECIMAL,  
    KPDivide = GLFW_KEY_KP_DIVIDE,  
    KPMultiply = GLFW_KEY_KP_MULTIPLY,  
    KPSubtract = GLFW_KEY_KP_SUBTRACT,  
    KPAdd = GLFW_KEY_KP_ADD,  
    KPEnter = GLFW_KEY_KP_ENTER,  
    KPEqual = GLFW_KEY_KP_EQUAL  
};  

/**
 * @brief Enumeration of all supported mouse buttons.
 * 
 * Maps to GLFW mouse button codes.
 */
enum class CLUTTER_API EMouseButton 
{
    Left = GLFW_MOUSE_BUTTON_LEFT,      /**< Left mouse button */
    Right = GLFW_MOUSE_BUTTON_RIGHT,    /**< Right mouse button */
    Middle = GLFW_MOUSE_BUTTON_MIDDLE,  /**< Middle mouse button */
    Button4 = GLFW_MOUSE_BUTTON_4,      /**< Mouse button 4 */
    Button5 = GLFW_MOUSE_BUTTON_5,      /**< Mouse button 5 */
    Button6 = GLFW_MOUSE_BUTTON_6,      /**< Mouse button 6 */
    Button7 = GLFW_MOUSE_BUTTON_7,      /**< Mouse button 7 */
    Button8 = GLFW_MOUSE_BUTTON_8       /**< Mouse button 8 */
};

/**
 * @brief Enumeration of all supported controller buttons.
 * 
 * Maps to GLFW gamepad button codes.
 */
enum class CLUTTER_API EControllerButton 
{
    A = GLFW_GAMEPAD_BUTTON_A,                  /**< A button */
    B = GLFW_GAMEPAD_BUTTON_B,                  /**< B button */
    X = GLFW_GAMEPAD_BUTTON_X,                  /**< X button */
    Y = GLFW_GAMEPAD_BUTTON_Y,                  /**< Y button */
    LeftBumper = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,   /**< Left bumper */
    RightBumper = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER, /**< Right bumper */
    Back = GLFW_GAMEPAD_BUTTON_BACK,            /**< Back button */
    Start = GLFW_GAMEPAD_BUTTON_START,          /**< Start button */
    Guide = GLFW_GAMEPAD_BUTTON_GUIDE,          /**< Guide button */
    LeftThumb = GLFW_GAMEPAD_BUTTON_LEFT_THUMB, /**< Left thumbstick */
    RightThumb = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB, /**< Right thumbstick */
    DpadUp = GLFW_GAMEPAD_BUTTON_DPAD_UP,       /**< D-pad up */
    DpadRight = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT, /**< D-pad right */
    DpadDown = GLFW_GAMEPAD_BUTTON_DPAD_DOWN,   /**< D-pad down */
    DpadLeft = GLFW_GAMEPAD_BUTTON_DPAD_LEFT    /**< D-pad left */
};

/**
 * @brief Enumeration of all supported controller axes.
 * 
 * Maps to GLFW gamepad axis codes.
 */
enum class CLUTTER_API EControllerAxis 
{
    LeftX = GLFW_GAMEPAD_AXIS_LEFT_X,           /**< Left stick X axis */
    LeftY = GLFW_GAMEPAD_AXIS_LEFT_Y,           /**< Left stick Y axis */
    RightX = GLFW_GAMEPAD_AXIS_RIGHT_X,         /**< Right stick X axis */
    RightY = GLFW_GAMEPAD_AXIS_RIGHT_Y,         /**< Right stick Y axis */
    LeftTrigger = GLFW_GAMEPAD_AXIS_LEFT_TRIGGER,   /**< Left trigger */
    RightTrigger = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER  /**< Right trigger */
};

/**
 * @brief Enumeration of input states for keys, mouse buttons, or controller buttons.
 */
enum class CLUTTER_API EInputState 
{  
    Pressed,   /**< Input was just pressed */
    Held,      /**< Input is being held down */
    Released,  /**< Input was just released */
    Idle       /**< Input is not active */
};
