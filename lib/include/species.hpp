#ifndef SPECIES_HPP
#define SPECIES_HPP
#include <functional>
#include <ranges>
#include <string>

namespace StochasticSimulation
{
    struct Reaction;

    struct Species
    {
        virtual ~Species() = default;
        std::string name;
        mutable int _quantity;
        std::unordered_map<std::string, std::function<void()>> mark_for_recalculation;

        explicit Species(std::string name, int quantity = 0);
        Species();

        void increase_quantity(int amount = 1)
        {
            for (const auto& func : mark_for_recalculation | std::views::values) {
                func();
            }
            _quantity += amount;
        }

        void decrease_quantity(int amount = 1)
        {
            for (const auto& func : mark_for_recalculation | std::views::values) {
                func();
            }
            _quantity -= amount;
        }

        void create_delay_marker_reference(const std::string& reactionName, std::function<void()> delay_marker_func)
        {
            if (mark_for_recalculation.contains(reactionName))
                return;

            mark_for_recalculation[reactionName] = delay_marker_func;
        }

        virtual std::string to_string() const { return name; }
    };
}  // namespace StochasticSimulation

#endif  // SPECIES_HPP
