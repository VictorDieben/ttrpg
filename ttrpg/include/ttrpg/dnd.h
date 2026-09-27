#pragma once

#include <array>
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
    std::vector<entt::entity> children;
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
    Relationship(entt::registry& reg)
        : reg(reg)
    { }

    using Parent = Parent<TreeType::Inventory>;
    using Child = Child<TreeType::Inventory>;

    bool try_connect(entt::entity parent, entt::entity child)
    {
        // if parent is a parent, child is a child, and child has no parent yet,
        // connect and return true. else return false
        reg.get<Child>(child).parent;
        auto& children = reg.get<Parent>(parent).children;

        return true;
    }

    bool try_disconnect(entt::entity parent, entt::entity child) { }

private:
    entt::registry& reg;
};

using Inventory = Parent<TreeType::Inventory>;
using InventoryItem = Child<TreeType::Inventory>;
using InventorySystem = Relationship<TreeType::Inventory>;

} // namespace dnd
} // namespace tt