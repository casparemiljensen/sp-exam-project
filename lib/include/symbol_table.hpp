#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <stdexcept>
#include "symbol_table.hpp"
#include <unordered_map>
#include <vector>
namespace StochasticSimulation {
    template<typename Key, typename Value>
    class SymbolTable
    {
        std::unordered_map<Key, Value> table;

    public:
        const Value& add(const Key& key, const Value& value)
        {
            if (table.contains(key)) throw std::runtime_error("Key already exists");
            table[key] = value;
            return value;
        }

        const Value& get(const Key& key) {
            if (!table.contains(key)) throw std::out_of_range("Key not found");
            return table.at(key);
        }

        bool contains(const Key& key) const {
            return table.contains(key);
        }

        std::vector<Value> getValues() const {
            std::vector<Value> values;
            for (const auto& [_, value] : table) {
                values.push_back(value);
            }
            return values;
        }
    };
}
#endif //SYMBOL_TABLE_HPP
