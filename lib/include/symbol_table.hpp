#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <format>
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

        Value& get(const Key& key) {
            if (!table.contains(key)) throw std::out_of_range(std::format("(SymbolTable) - Key {} not found, passed wrong state to simulator?", key));
            return table.at(key);
        }
        const Value& get(const Key& key) const { // Overload for const symboltables
            if (!table.contains(key)) throw std::out_of_range(std::format("(SymbolTable:const) - Key {} not found, passed wrong state to simulator?", key));
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

        auto begin() { return table.begin(); }
        auto end() { return table.end(); }
        auto begin() const { return table.begin(); }
        auto end() const { return table.end(); }
    };
}
#endif //SYMBOL_TABLE_HPP
