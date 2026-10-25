#pragma once

// a file with temporary test classes

#include <array>
#include <cstdint>
#include <string_view>
#include <vector>

#include "definitions.h"

#include <entt/entt.hpp>

namespace tt
{

namespace dnd
{

enum class Friendlyness
{
    Friendly,
    Neutral,
    Hostile
};

enum class CombatState
{
    Inactive,
    Start,
    Active,
    End
};

enum class RoundState
{
    Inactive,
    Start,
    Active,
    End
};

enum class CombattantState
{
    RollInitiative,
    AwaitTurn,
    ActiveTurn,
    CompletedTurn
};

struct Combat
{
    std::vector<entt::entity> combattants;

    CombatState combatState{CombatState::Inactive};
    RoundState roundState{RoundState::Inactive};
};

struct Combattant
{
    entt::entity combat{entt::null};
    CombattantState state{CombattantState::RollInitiative};
    Initiative initiative;
};

//
// System
//

void AddToCombat(entt::registry& reg, //
                 entt::entity combat,
                 entt::entity combattant);

void RemoveFromCombat(entt::registry& reg, //
                      entt::entity combat,
                      entt::entity combattant);

void RunCombat(entt::registry& reg);

class CombatSystem
{
public:
    CombatSystem(entt::registry& reg)
        : reg(reg)
    { }

private:
    entt::registry& reg; // todo: just pass each frame?
};

} // namespace dnd
} // namespace tt