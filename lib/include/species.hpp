
#ifndef SPECIES_HPP
#define SPECIES_HPP
#include <functional>
#include <ranges>
#include <string>
#include <iostream>
#include <set>
#include <unordered_set>

namespace StochasticSimulation {
    struct Reaction;

    struct Species {
        virtual ~Species() = default;
        std::string name;
        mutable int _quantity;
        std::unordered_map<std::string, std::function<void()>> mark_for_recalculation;

        explicit Species(std::string name, int quantity = 0);
        Species();

        void increase_quantity() {
            for (const auto &func: mark_for_recalculation | std::views::values) {
                func();
            }
            _quantity++;
        }

        void decrease_quantity() {
            for (const auto &func: mark_for_recalculation | std::views::values) {
                func();
            }
            _quantity--;
        }

        void create_delay_marker_reference(const std::string& reactionName, std::function<void()> delay_marker_func) {
            if (mark_for_recalculation.contains(reactionName))
                return;

            mark_for_recalculation[reactionName] = delay_marker_func;
            std::cout << "Creating delay marker " << reactionName << std::endl;
        }

        virtual std::string to_string() const {
            return name;
        }
    };
}

#endif //SPECIES_HPP
