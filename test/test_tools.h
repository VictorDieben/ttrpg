#pragma once

#include "ttrpg/ttrpg.h"
#include <array>
#include <cstdint>
#include <iomanip>
#include <ostream>

#include <entt/entt.hpp>

namespace tt
{

// convenience wrapper around entt::handle{reg, reg.create()};
inline entt::handle create_handle(entt::registry& registry)
{
    return entt::handle{registry, registry.create()}; //
}

} // namespace tt