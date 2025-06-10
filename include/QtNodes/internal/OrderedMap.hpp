#pragma once
#include <vector>
#include <unordered_map>

namespace QtNodes {
    template<typename Key, typename Value>
    class OrderedMap
    {
    public:
        /// @brief 插入数据
        /// @param key Key 键
        /// @param value Value 值
        void insert(const Key& key, const Value& value) {
            if (_data.find(key) == _data.end()) { // 如果键不存在
                _order.push_back(key);            // 记录插入顺序
            }
            _data[key] = value; // 插入或更新值
        }

        /// @brief 判断是否包含key
        /// @param key 键
        /// @return true:包含；false:不包含
        bool contains(const Key& key) const { return _data.find(key) != _data.end();
        }

        /// @brief 移除元素
        /// @param key 键
        void erase(const Key& key) {
            if (contains(key)) {
                _data.erase(key);
                _order.erase(std::find(_order.begin(), _order.end(), key));
            }
        }

        /// @brief 获取Key列表
        /// @return 按照先后顺序插入的Key列表
        const std::vector<Key>& orderedKey() const { 
            return _order;
        }

        /// @brief 获取结果
        /// @param key 键
        /// @return Value 值
        std::optional<Value> value(const Key &key) const
        {
            auto it = _data.find(key);
            return (it != _data.end()) ? std::optional<Value>(it->second) : std::nullopt;
        }

    private:
        std::vector<Key> _order;
        std::unordered_map<Key, Value> _data;
    };
}