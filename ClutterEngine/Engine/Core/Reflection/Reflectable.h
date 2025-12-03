#pragma once
#include <functional>
#include <Core/CCommon.h>
#include <Core/Reflection/ObjectRegistry.h>
#include <json/json.hpp>

namespace clt
{
    enum class PropMode { ReadWrite, ReadOnly, Hidden };
    
    struct Property
    {
        std::string name;
        PropMode mode;
        std::function<bool()> condition;
        std::function<void(nlohmann::json&)> serialize;
        std::function<void(const nlohmann::json&)> deserialize;
    };
    
    class CLUTTER_API Reflectable
    {
    protected:
        std::vector<Property> mProperties;
        
    public:
        virtual ~Reflectable() = default;
        
        virtual void SetupProperties() {};
        
        virtual std::string GetTypeName() const = 0;
        std::vector<Property>& GetProperties() const { return mProperties; }
        
        template <typename T>
        void RegisterProperty(const std::string& name,T* varPtr, PropMode mode, std::function<bool()> cond = []{return true;})
        {
            Property prop;
            prop.name = name;
            prop.mode = mode;
            prop.condition = cond;
            
            prop.serialize = [varPtr, name](const nlohmann::json& j)
            {
                j[name] = *varPtr;
            };
            
            prop.deserialize = [varPtr, name](const nlohmann::json& j)
            {
                if (j.contains(name)) *varPtr = j[name].get<T>();
            };
            
            mProperties.push_back(prop);
        }
        
        virtual nlohmann::json ToJson()
        {
            nlohmann::json j;
            j["Type"] = GetTypeName();
            
            nlohmann::json props;
            for (auto& prop : mProperties)
            {
                prop.serialize(props);
            }
            j["Properties"] = props;
            return j;
        }
        
        virtual void FromJson(const nlohmann::json& j)
        {
            if (j.contains("Properties"))
            {
                for (auto& prop : mProperties)
                {
                    prop.deserialize(j["Properties"]);
                }
            }
        }
    };
}


#define REGISTER_PROPERTY(Variable, Mode) RegisterProperty(#Variable, &Variable, Mode);
#define CPROPERTY(Variable, Mode) RegisterProperty(#Variable, &Variable, Mode);
#define CPROPERTY_COND(Variable, Mode, Condition) RegisterProperty(#Variable, &Variable, Mode, [this](){ return (Condition); });

#define CLUTTER_CLASS(ClassName) \
    virtual std::string GetTypeName() const override { return #ClassName; }