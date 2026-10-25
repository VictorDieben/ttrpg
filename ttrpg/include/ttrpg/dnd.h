#pragma once

#include <array>
#include <cassert>
//#include <flat_set>
#include <variant>
#include <vector>

#include <entt/entt.hpp>

#include "ttrpg/base/components.h"
#include "ttrpg/base/definitions.h"
#include "ttrpg/base/tree.h"

#include "ttrpg/dnd/definitions.h"

namespace tt
{
namespace dnd
{
using Rounds = std::int64_t;
struct UntilLongRest
{ };
struct UntilShortRest
{ };
using Duration = std::variant<Rounds, UntilLongRest, UntilShortRest>;

using namespace entt::literals;

static constexpr entt::id_type inventory_id = "inventory"_hs;
using Inventory = tt::Parent<inventory_id>;
using InventoryItem = tt::Child<inventory_id>;
using InventorySystem = tt::Relationship<inventory_id>;

static constexpr entt::id_type traits_id = "traits"_hs;
using TraitParent = tt::Parent<traits_id>;
using TraitChild = tt::Child<traits_id>;
using TraitSystem = tt::Relationship<traits_id>;

//
//
//

static constexpr entt::id_type condition_id = "condition"_hs;
using ConditionParent = tt::Parent<condition_id>;
using ConditionChild = tt::Child<condition_id>;
using ConditionSystem = tt::Relationship<condition_id>;

enum class ConditionType
{
    Blinded,
    Charmed,
    Deafened,
    Frightened,
    Grappled,
    Incapacitated,
    Invisible,
    Paralyzed,
    Petrified,
    Poisoned,
    Prone,
    Restrained,
    Stunned,
    Unconscious,

    Exhaustion1,
    Exhaustion2,
    Exhaustion3,
    Exhaustion4,
    Exhaustion5,
    Exhaustion6, // death
};

struct Condition
{
    ConditionType type;
    Duration duration;
};

//
//
//

enum class CharacterType
{
    Player,
    NPC
};

struct Character
{
    // todo: type of character, player or NPC
    CharacterType type{CharacterType::Player};
};

} // namespace dnd
} // namespace tt