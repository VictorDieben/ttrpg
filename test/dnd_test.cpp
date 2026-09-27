

#include "ttrpg/dnd.h"
#include <gtest/gtest.h>

#include "test_tools.h"

#include <entt/entt.hpp>

using namespace tt;
using namespace tt::dnd;

TEST(DND, TestInventory)
{
    entt::registry reg;

    auto backpack = entt::handle{reg, reg.create()};
    backpack.emplace<Name>("backpack");
    backpack.emplace<Inventory>();

    auto potion = entt::handle{reg, reg.create()};
    potion.emplace<Name>("potion");
    backpack.emplace<InventoryItem>();

    InventorySystem system{reg};
    EXPECT_TRUE(system.try_connect(backpack, potion));
}
