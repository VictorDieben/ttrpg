

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
    potion.emplace<InventoryItem>();

    EXPECT_EQ(backpack.get<Inventory>().children.size(), 0);
    EXPECT_TRUE((potion.get<InventoryItem>().parent == entt::null));

    InventorySystem system{reg};
    EXPECT_TRUE(system.try_connect(backpack, potion));

    EXPECT_EQ(backpack.get<Inventory>().children.size(), 1);
    EXPECT_TRUE((potion.get<InventoryItem>().parent == backpack));
}
