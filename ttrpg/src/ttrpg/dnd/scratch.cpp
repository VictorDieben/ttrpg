

#include "ttrpg/dnd/scratch.h"
namespace tt
{

namespace dnd
{

void AddToCombat(entt::registry& reg, //
                 entt::entity combat,
                 entt::entity combattant)
{
    // todo: validate
    reg.get<Combat>(combat).combattants.push_back(combattant);
    reg.get<Combattant>(combattant).combat = combat;
}

void RemoveFromCombat(entt::registry& reg, //
                      entt::entity combat,
                      entt::entity combattant)
{
    // todo: validate
    reg.get<Combat>(combat).combattants.push_back(combattant);
    reg.get<Combattant>(combattant).combat = combat;
}

static void RunCombatActive(entt::registry& reg, //
                            entt::entity entity,
                            Combat& combat)
{
    //
    combat.combatState = CombatState::End;
}

void RunCombat(entt::registry& reg)
{
    reg.view<Combat>().each([&reg](entt::entity combatEntity, Combat& combat) {
        if(combat.combattants.empty())
            reg.destroy(combatEntity); // a combat without participants is removed

        // todo: for each other combat, check if they need to be merged

        // todo: combat phase

        switch(combat.combatState)
        {
        case CombatState::Inactive: {
            combat.combatState = CombatState::Start;
            break;
        }
        case CombatState::Start: {
            combat.combatState = CombatState::Active;
            break;
        }
        case CombatState::Active: {
            RunCombatActive(reg, combatEntity, combat);
            break;
        }
        case CombatState::End: {
            break;
        }
        }
    });
};

} // namespace dnd
} // namespace tt