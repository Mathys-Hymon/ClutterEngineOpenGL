#pragma once
#include <functional>
#include <Core/CCommon.h>

namespace clt
{
    class Component;
    
    class CLUTTER_API ObjectRegistry
    {
    public:
        using ComponentCreator = std::function<Component*()>;
        
        static void RegisterComponent(const std::string& name, ComponentCreator creator)
        {
            GetComponentRegistry()[name] = creator;
        }
        
        static Component* CreateComponent(const std::string& name)
        {
            auto& reg = GetComponentRegistry();
            if (reg.find(name) != reg.end())
            {
                return reg[name]();
            }
            return nullptr;
        }
        
    private:
        static std::map<std::string, ComponentCreator>& GetComponentRegistry()
        {
            static std::map<std::string, ComponentCreator> registry;
            return registry;
        }
    };
}

#define REGISTER_COMPONENT_CLASS(Type) \
    namespace { \
        struct Type##Reg { \
            Type##Reg() { \
                clt::ObjectRegistry::RegisterComponent(#Type, []() -> clt::Component* { return new Type(); }); \
            } \
        }; \
        static Type##Reg global_##Type##Reg; \
    }
