#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <numeric>
#include <set>
#include <vector>

#include "definitions.h"

namespace tt
{
namespace dnd // Note: 5e
{

using Dice = tt::Dice; // in case Dice is expanded with other sizes

using AbilityScore = std::int32_t;
using AbilityModifier = std::int32_t;
using ProficiencyModifier = std::int32_t;
using ProficiencyBonus = std::int32_t;
using SkillScore = std::int32_t;
using Initiative = std::int32_t;
using Level = std::int32_t;
using ClassLevel = Level;
using SavingThrowModifier = std::int32_t;
using Speed = std::int32_t;
using ArmorClass = std::int32_t;
using HitDice = Dice;
using HitPoints = std::int32_t;
using TempHitPoints = std::int32_t;

static constexpr std::size_t num_abilities = 6;
static constexpr std::size_t num_skills = 18;

enum class Ability : std::size_t
{
    Strength = 0,
    Dexterity = 1,
    Constitution = 2,
    Intelligence = 3,
    Wisdom = 4,
    Charisma = 5
};

enum class Class : std::size_t
{
    Artificer = 0,
    Barbarian = 1,
    Bard = 2,
    Cleric = 3,
    Druid = 4,
    Fighter = 5,
    Monk = 6,
    Paladin = 7,
    Ranger = 8,
    Rogue = 9,
    Sorcerer = 10,
    Warlock = 11,
    Wizard = 12
};

using ClassLevels = std::array<ClassLevel, 13>;

enum class ClassCathegory
{
    Martial,
    ThirdCaster,
    HalfCaster,
    Caster,
    Other // Note: warlock/special cases
};

constexpr ClassCathegory Cathegory(const Class cls)
{
    // todo: some subclasses are slightly different (Arcane Trickster, Eldrich Knight)
    switch(cls)
    {
    case Class::Bard:
    case Class::Cleric:
    case Class::Druid:
    case Class::Sorcerer:
    case Class::Wizard:
        return ClassCathegory::Caster;

    case Class::Artificer:
    case Class::Paladin:
    case Class::Ranger:
        return ClassCathegory::HalfCaster;

    case Class::Barbarian:
    case Class::Fighter:
    case Class::Monk:
    case Class::Rogue:
        return ClassCathegory::Martial;
    case Class::Warlock:
        return ClassCathegory::Other;
    }
}

enum class Skill : std::size_t
{
    Acrobatics = 0,
    AnimalHandling,
    Acrana,
    Athletics,
    Deception,
    History,
    Insight,
    Intimidation,
    Investigation,
    Medicine,
    Nature,
    Perception,
    Performance,
    Persuasion,
    Religion,
    SleightOfHand,
    Stealth,
    Survival
};

enum class OtherProficiency : std::size_t
{
    Armor,
    Shields,
    SimpleWeapons,
    MartialWeapons
    // todo
};

enum class Proficiency : std::size_t
{
    // todo: can you have expertise in say, wearing armour?
    None = 0,
    Proficiency = 1,
    Expertise = 2
};

using SavingThrowModifiers = std::array<SavingThrowModifier, num_abilities>;
using SavingThrowProficiencies = std::array<Proficiency, num_abilities>;

using OtherProficiencies = std::set<OtherProficiency>; // todo: flat set

enum class Language : std::size_t
{
    Common,
    Draconic,
    Dwarvish
    // todo
};

using Languages = std::set<Language>; // todo: flat set

using AbilityScores = std::array<AbilityScore, num_abilities>;
using AbilityModifiers = std::array<AbilityModifier, num_abilities>;
using AbilityProficiencies = std::array<Proficiency, num_abilities>;

using Skills = std::array<SkillScore, num_skills>;

constexpr AbilityModifier CalculateAbilityModifier(const AbilityScore score, //
                                                   const ProficiencyBonus bonus)
{
    return {}; // todo
}

constexpr AbilityModifiers CalculateAbilityModifiers(const AbilityScores& scores, //
                                                     const ProficiencyBonus bonus)
{
    AbilityModifiers mods{};
    for(std::size_t i = 0; i < num_abilities; ++i)
        mods[i] = CalculateAbilityModifier(scores[i], bonus);
    return mods;
}

constexpr Level GetTotalLevel(const ClassLevels& levels) { return std::accumulate(levels.begin(), levels.end(), 0); }

constexpr ProficiencyBonus CalculateProficiencyBonus(const Level level)
{
    // level should never be lower than 1, and proficiency bonus stops increasing at 20
    const auto clamped = std::clamp(level, 1, 20);
    return 2 + ((clamped - 1) / 4);
}

constexpr SavingThrowModifiers CalculateSavingThrowModifiers(const AbilityModifiers& modifiers,
                                                             const SavingThrowProficiencies& proficiencies,
                                                             const ProficiencyBonus bonus)
{
    return SavingThrowModifiers{};
}

// NOTE: this struct is just to get an idea of what has been implemented and still needs to be done.
// in real code some members of this class should probably be separate ECS components.
// For instance, not everything that can speak a langauge can also join battle

struct Character
{

    ClassLevels class_levels;

    Level GetLevel() const { return GetTotalLevel(class_levels); }

    ProficiencyBonus proficiency_bonus = CalculateProficiencyBonus(GetLevel());

    // base score, without bonusses for proficiency/race/items/background/etc
    AbilityScores base_ability_scores{10, 10, 10, 10, 10, 10};

    AbilityModifiers ability_modifiers = CalculateAbilityModifiers(base_ability_scores, //
                                                                   proficiency_bonus);

    SavingThrowProficiencies saving_throw_proficiencies{Proficiency::Proficiency,
                                                        Proficiency::Expertise,
                                                        Proficiency::None,
                                                        Proficiency::None,
                                                        Proficiency::None,
                                                        Proficiency::None};

    SavingThrowModifiers saving_throw_modifiers = CalculateSavingThrowModifiers(ability_modifiers, //
                                                                                saving_throw_proficiencies,
                                                                                proficiency_bonus);

    Skills skill_scores{};

    Languages languages{Language::Common};

    HitDice hitdice = Dice::d10;

    HitPoints hitpoints;

    TempHitPoints temphitpoints = 0;

    //const AbilityScore& str() const { return ability_scores[(std::size_t)Ability::Strength]; };
    //const AbilityScore& dex() const { return ability_scores[(std::size_t)Ability::Dexterity]; };
    //const AbilityScore& con() const { return ability_scores[(std::size_t)Ability::Constitution]; };
    //const AbilityScore& intl() const { return ability_scores[(std::size_t)Ability::Intelligence]; };
    //const AbilityScore& wis() const { return ability_scores[(std::size_t)Ability::Wisdom]; };
    //const AbilityScore& cha() const { return ability_scores[(std::size_t)Ability::Charisma]; };

    //AbilityScore& str() { return ability_scores[(std::size_t)Ability::Strength]; };
    //AbilityScore& dex() { return ability_scores[(std::size_t)Ability::Dexterity]; };
    //AbilityScore& con() { return ability_scores[(std::size_t)Ability::Constitution]; };
    //AbilityScore& intl() { return ability_scores[(std::size_t)Ability::Intelligence]; };
    //AbilityScore& wis() { return ability_scores[(std::size_t)Ability::Wisdom]; };
    //AbilityScore& cha() { return ability_scores[(std::size_t)Ability::Charisma]; };
};

} // namespace dnd
} // namespace tt