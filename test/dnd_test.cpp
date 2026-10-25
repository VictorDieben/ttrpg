

#include <gtest/gtest.h>

#include "ttrpg/dnd.h"
#include "ttrpg/dnd/definitions.h"
#include "ttrpg/dnd/scratch.h"

#include "test_tools.h"

#include <entt/entt.hpp>

using namespace tt;
using namespace tt::dnd;

TEST(DND, TestInventory)
{
    using namespace entt::literals;

    entt::registry reg;

    auto backpack = create_handle(reg);
    backpack.emplace<Name>("backpack");
    backpack.emplace<Inventory>();

    auto potion = create_handle(reg);
    potion.emplace<Name>("potion");
    potion.emplace<InventoryItem>();

    EXPECT_EQ(backpack.get<Inventory>().children.size(), 0);
    EXPECT_TRUE((potion.get<InventoryItem>().parent == entt::null));

    // put potion in backpack
    InventorySystem system{reg};
    EXPECT_TRUE(system.try_connect(backpack, potion));

    EXPECT_EQ(backpack.get<Inventory>().children.size(), 1);
    EXPECT_TRUE((potion.get<InventoryItem>().parent == backpack));

    // delete potion, check that backpack is empty again
    reg.destroy(potion);

    EXPECT_EQ(backpack.get<Inventory>().children.size(), 0);
    EXPECT_FALSE(reg.valid(potion));
}

TEST(DND, TestCondition)
{
    entt::registry reg;

    auto character = create_handle(reg);
    character.emplace<Name>("character");
    character.emplace<Character>();
    character.emplace<ConditionParent>();

    auto condition = create_handle(reg);
    condition.emplace<Name>("blinded");
    condition.emplace<ConditionChild>();
    condition.emplace<Condition>(ConditionType::Blinded);

    ConditionSystem system{reg};

    system.try_connect(character, condition);
}

TEST(DND, TestTraits)
{
    entt::registry reg;

    auto character = create_handle(reg);
    character.emplace<Name>("character");
    character.emplace<Character>();
    character.emplace<TraitParent>();

    auto trait = create_handle(reg);
    character.emplace<Name>("some trait");
    character.emplace<TraitChild>();

    TraitSystem system{reg};
}

TEST(DND, TestCharacter)
{
    entt::registry reg;

    auto character = create_handle(reg);
    character.emplace<Name>("character");
    character.emplace<Character>();
    character.emplace<Inventory>();
    character.emplace<TraitParent>();
}

TEST(DND, TestEncounter)
{
    //entt::registry reg;

    //auto character = create_handle(reg);
    //character.emplace<Name>("character");
    //character.emplace<Character>();
    //character.emplace<Inventory>();
    //character.emplace<EncounterActor>();

    //auto encounter = create_handle(reg);
    //character.emplace<Name>("encounter");
    //character.emplace<Encounter>();
}

inline entt::entity CreateSword(entt::registry& reg)
{
    auto sword = create_handle(reg);
    sword.emplace<Name>("sword");
    sword.emplace<InventoryItem>();
    return sword;
}

inline entt::entity CreatePlayer(entt::registry& reg)
{
    auto player = create_handle(reg);
    player.emplace<Name>("player");
    player.emplace<Character>(CharacterType::Player);
    player.emplace<Inventory>();
    player.emplace<TraitParent>();
    player.emplace<ConditionParent>();

    //auto sword = CreateSword(reg);
    // todo: put sword in player inventory

    return player;
}

inline entt::entity CreateGoblin(entt::registry& reg)
{
    auto goblin = create_handle(reg);
    goblin.emplace<Name>("goblin");
    goblin.emplace<Character>(CharacterType::NPC);
    goblin.emplace<Inventory>();
    goblin.emplace<TraitParent>();
    goblin.emplace<ConditionParent>();
    return goblin;
}

inline entt::entity CreateCombat(entt::registry& reg)
{
    auto combat = create_handle(reg);
    combat.emplace<Name>("combat");
    combat.emplace<Combat>();
    return combat;
}

TEST(DND, TestCombat)
{
    entt::registry reg;

    auto player = CreatePlayer(reg);
    auto goblin = CreateGoblin(reg);
    auto combat = CreateCombat(reg);

    CombatSystem combatSystem{reg};

    AddToCombat(reg, combat, player);
    AddToCombat(reg, combat, goblin);

    RunCombat(reg);
}