#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <Core/CCommon.h>
#include <json/json.hpp>

namespace clt
{
    class JsonUtility
    {
    public:

        static bool LoadFromFile(const std::string& filePath, nlohmann::json& outJson)
        {
            std::ifstream file(filePath);
            if (!file.is_open())
            {
                std::cerr << "Failed to open JSON file: " << filePath << "\n";
                return false;
            }

            try
            {
                file >> outJson;
            }
            catch (const nlohmann::json::parse_error& e)
            {
                std::cerr << "JSON parse error in " << filePath << ": " << e.what() << "\n";
                return false;
            }
            return true;
        }

        static bool SaveToFile(const std::string& filePath, const nlohmann::json& jsonData)
        {
            std::ofstream file(filePath);
            if (!file.is_open())
            {
                std::cerr << "Failed to open file for writing: " << filePath << "\n";
                return false;
            }

            try
            {
                file << jsonData.dump(4);
            }
            catch (const std::exception& e)
            {
                std::cerr << "JSON write error: " << e.what() << "\n";
                return false;
            }
            return true;
        }


        template<typename T>
        static T Get(const nlohmann::json& j, const std::string& key, const T& defaultValue)
        {
            if (j.contains(key))
            {
                try
                {
                    return j.at(key).get<T>();
                }
                catch (...)
                {
                    std::cerr << "JSON type mismatch for key: " << key << "\n";
                }
            }
            return defaultValue;
        }

        template<typename T>
        static void Set(nlohmann::json& j, const std::string& key, const T& value)
        {
            j[key] = value;
        }

        static bool EndsWith(const std::string& str, const std::string& suffix)
        {
            if (suffix.size() > str.size()) return false;
            return std::equal(suffix.rbegin(), suffix.rend(), str.rbegin());
        }
    };
}