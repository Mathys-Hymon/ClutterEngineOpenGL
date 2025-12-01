#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include <any>
#include <algorithm>

namespace clt
{
    namespace editor
    {
        class CLUTTER_API EventBus
        {
        public:
            using Callback = std::function<void (const std::any&)>;   
    
        private:
            struct Subscriber
            {
                int id;
                Callback cb;
            };
    
            std::unordered_map<std::string, std::vector<Subscriber>> mSubs;
            int mNextId{0};
        public:
    
            int Subscribe(const std::string& name, Callback cb)
            {
                int id = mNextId++;
                mSubs[name].push_back({id, std::move(cb)});
                return id;
            }
    
            void Unsubscribe(const std::string& name, int id)
            {
                auto it = mSubs.find(name);
                if (it == mSubs.end()) return;
                auto& vec = it->second;
                vec.erase(std::remove_if(vec.begin(), vec.end(), [id](const Subscriber& s){ return s.id == id; }), vec.end());
            }
    
            void Publish( const std::string& name, const std::any& payload = {})
            {
                auto it = mSubs.find(name);
                if (it == mSubs.end()) return;
        
                auto copy = it->second;
        
                for (auto& sub : copy)
                {
                    if (sub.cb) sub.cb(payload);
                }
            }
        };
    }
}
