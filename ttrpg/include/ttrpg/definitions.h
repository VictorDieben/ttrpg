#pragma once

#include <array>
#include <cstdint>

namespace tt
{

enum class Dice : std::size_t
{
    d4,
    d6,
    d8,
    d10,
    d12,
    d20
};

constexpr std::uint32_t Sides(const Dice dice)
{
    switch(dice)
    {
    case Dice::d4:
        return 4;
    case Dice::d6:
        return 6;
    case Dice::d8:
        return 8;
    case Dice::d10:
        return 10;
    case Dice::d12:
        return 12;
    case Dice::d20:
        return 20;
    }
}

constexpr const char* to_string(const Dice dice)
{
    switch(dice)
    {
    case Dice::d4:
        return "d4";
    case Dice::d6:
        return "d6";
    case Dice::d8:
        return "d8";
    case Dice::d10:
        return "d10";
    case Dice::d12:
        return "d12";
    case Dice::d20:
        return "d20";
    }
}

} // namespace tt