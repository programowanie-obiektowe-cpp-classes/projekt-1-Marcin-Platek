#ifndef P1_CPP_LAB_RANDOMNAMEGENERATOR_HPP
#define P1_CPP_LAB_RANDOMNAMEGENERATOR_HPP

#include <array>
#include <format>
#include <random>

using namespace std;

inline constexpr array first_names{
    "Ann",
    "Andrew",
    "John",
    "Jane",
    "Bob",
    "Alice",
    "Bertram",
    "Monica",
    "Laura",
    "Eric",
    "Richard",
    "Karen",
    "Clara",
    "Rupert",
    "Bruce",
    "Martha",
    "Elizabeth",
    "Corey",
    "Nancy",
    "Joe",
    "Amy",
    "Mike",
    "James",
    "Naomi"
};

inline constexpr array last_names{
    "Hendricks",
    "Smith",
    "Gates",
    "Stein",
    "Warren",
    "Booker",
    "Williamson",
    "Walters",
    "Dunn",
    "Swanson",
    "Knope",
    "Haverford",
    "Ludgate",
    "Meagle",
    "Favreau",
    "Vietor",
    "Lovett",
    "Pfeifer",
    "Rhodes",
    "Abrams",
    "McFaul",
    "Stone",
    "Sisley",
    "Hanneman",
    "Holden",
    "Nagata"
};

inline auto getRandomName() -> string {
    static auto prng = mt19937{random_device{}()};
    auto fnd = uniform_int_distribution<size_t>{0, first_names.size() - 1};
    auto lnd = uniform_int_distribution<size_t>{0, last_names.size() - 1};
    const auto first_name = first_names[fnd(prng)];
    const auto last_name = last_names[lnd(prng)];
    return format("{} {}", first_name, last_name);
}

#endif //P1_CPP_LAB_RANDOMNAMEGENERATOR_HPP
