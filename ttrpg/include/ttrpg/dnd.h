#pragma once

#include <array>
#include <cassert>
#include <flat_set>
#include <vector>

#include <entt/entt.hpp>

#include "ttrpg/base/components.h"
#include "ttrpg/base/definitions.h"

#include "ttrpg/dnd/definitions_dnd.h"

namespace tt
{
namespace dnd
{

enum class TreeType
{
    Inventory,
    Following
};

template <TreeType T>
struct Parent
{
    std::flat_set<entt::entity> children;
};

template <TreeType T>
struct Child
{
    entt::entity parent{entt::null};
};

template <TreeType T>
class Relationship
{
public:
    using Parent = Parent<TreeType::Inventory>;
    using Child = Child<TreeType::Inventory>;

    Relationship(entt::registry& reg)
        : reg(reg)
    {
        // If a parent is deleted, unparent its children
        reg.on_destroy<Parent>().connect<&Relationship::OnParentDestroyed>(this);

        // If a child is deleted, tell parent
        reg.on_destroy<Child>().connect<&Relationship::OnChildDestroyed>(this);
    }

    bool try_connect(entt::entity parent, entt::entity child)
    {
        // if parent is a parent, child is a child, and child has no parent yet,
        // connect and return true. else return false
        Child& childComp = reg.get<Child>(child);
        if(childComp.parent != entt::null)
            return false;

        Parent& parentComp = reg.get<Parent>(parent);
        if(parentComp.children.contains(child))
            return false; // child is already a child of parent (todo: assert?)

        childComp.parent = parent;
        parentComp.children.insert(child);

        return true;
    }

    bool try_disconnect(entt::entity parent, entt::entity child)
    {
        // if parent is not parent of child, return false
        Child* childComp = reg.try_get<Child>(child);
        assert(childComp);
        if(childComp.parent != parent)
            return false;

        // if child is not registered to parent, return false
        Parent* parentComp = reg.try_get<Parent>(parent);
        assert(parentComp);
        if(!parentComp->children.contains(child))
            return false;

        childComp.parent = entt::null;
        parentComp->children.erase(child);
        return true;
    }

private:
    void OnParentDestroyed(entt::registry& callReg, entt::entity parent)
    {
        // todo: assert(callReg == reg);
        auto& children = reg.get<Parent>(parent).children;
        for(auto& childId : children)
        {
            Child& child = reg.get<Child>(childId);
            if(child.parent == parent)
                child.parent = entt::null;
            else
                assert(false); // should not happen
        }
    }

    void OnChildDestroyed(entt::registry& callReg, entt::entity child)
    {
        // todo: assert(callReg == reg);
        auto parent = reg.get<Child>(child).parent;
        reg.get<Parent>(parent).children.erase(child);
    }

    entt::registry& reg;
};

using Inventory = Parent<TreeType::Inventory>;
using InventoryItem = Child<TreeType::Inventory>;
using InventorySystem = Relationship<TreeType::Inventory>;

} // namespace dnd
} // namespace tt