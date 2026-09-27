
#include "ttrpg/dnd/definitions_dnd.h"
#include <gtest/gtest.h>

#include "test_tools.h"

using namespace tt::dnd;

TEST(Definitions, TestProficiencyBonus)
{
    EXPECT_EQ(CalculateProficiencyBonus(-1), 2);
    EXPECT_EQ(CalculateProficiencyBonus(1), 2);
    EXPECT_EQ(CalculateProficiencyBonus(4), 2);

    EXPECT_EQ(CalculateProficiencyBonus(5), 3);
    EXPECT_EQ(CalculateProficiencyBonus(8), 3);

    EXPECT_EQ(CalculateProficiencyBonus(9), 4);

    EXPECT_EQ(CalculateProficiencyBonus(20), 6);
    EXPECT_EQ(CalculateProficiencyBonus(21), 6);
}

TEST(Definitions, TestAbilityModifier)
{
    EXPECT_EQ(CalculateAbilityModifier(10, 2), 0); // todo
}
