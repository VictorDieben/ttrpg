
#include "ttrpg/dnd/definitions.h"
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
    EXPECT_EQ(CalculateAbilityModifier(1), -5);

    EXPECT_EQ(CalculateAbilityModifier(2), -4);
    EXPECT_EQ(CalculateAbilityModifier(3), -4);

    EXPECT_EQ(CalculateAbilityModifier(4), -3);
    EXPECT_EQ(CalculateAbilityModifier(5), -3);

    EXPECT_EQ(CalculateAbilityModifier(6), -2);
    EXPECT_EQ(CalculateAbilityModifier(7), -2);

    EXPECT_EQ(CalculateAbilityModifier(8), -1);
    EXPECT_EQ(CalculateAbilityModifier(9), -1);
    EXPECT_EQ(CalculateAbilityModifier(10), 0);
    EXPECT_EQ(CalculateAbilityModifier(11), 0);

    EXPECT_EQ(CalculateAbilityModifier(19), 4);
    EXPECT_EQ(CalculateAbilityModifier(20), 5);
    EXPECT_EQ(CalculateAbilityModifier(21), 5);
}
