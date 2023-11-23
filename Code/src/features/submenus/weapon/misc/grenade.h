#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include <src/utility/enum.h>
#include <src/utility/timer.h>

namespace Base {
    namespace grenade_trail {
        namespace settings {
            float scale{ 0.1f };
            float delay{ 100 };
        }

        namespace util {
            struct Grenade_Trail {
                Color color;
                Entity entity;
                std::vector<Vector3> coords;
            };

            std::vector<Grenade_Trail> trails;

            void add_trail_point(Grenade_Trail& trail, const Vector3& new_coords) {
                if (trail.coords.size() >= 9999) {
                    trail.coords.erase(trail.coords.begin());
                }
                trail.coords.push_back(new_coords);
            }
        }

        bool enabled{ false };

        void init() {
            if (!enabled) return;

            auto obj{ OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(g_utils->coords().x, g_utils->coords().y, g_utils->coords().z, 2, 290600267, 0, 0, 1) };
            if (ENTITY::GET_ENTITY_ATTACHED_TO(obj) != g_utils->self()) {
                Entity entity{ obj };
                util::trails.emplace_back(g_rainbow, entity, std::vector<Vector3>());
            }

            for (auto& trail : util::trails) {
                if (ENTITY::DOES_ENTITY_EXIST(trail.entity)) {
                    Vector3 current_coords = g_utils->coords(trail.entity);
                    util::add_trail_point(trail, current_coords);

                    auto& coords = trail.coords;
                    if (coords.size() >= 2) {
                        for (size_t i = 0; i < coords.size() - 1; i++) {
                            auto& ent = coords[i];
                            auto& next_coords = coords[i + 1];
                            if ((!ent.contains_zero() || !next_coords.contains_zero())) {
                                GRAPHICS::DRAW_LINE(ent.x, ent.y, ent.z, next_coords.x, next_coords.y, next_coords.z, trail.color.r, trail.color.g, trail.color.b, 255);
                            }
                        }
                    }
                }
            }
        }
    }

	namespace instanty_explode_grenades {
		namespace util {
			std::vector<Entity> entities;
			std::unordered_map<Entity, timer> entity_map;
		}
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			auto obj{ OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(g_utils->coords().x, g_utils->coords().y, g_utils->coords().z, 2, 290600267, 0, 0, 1) };
			if (ENTITY::GET_ENTITY_ATTACHED_TO(obj) != g_utils->self()) {
				Entity entity{ obj };
				if (util::entity_map.find(entity) == util::entity_map.end())
					util::entity_map.emplace(entity, timer(std::chrono::milliseconds(100)));
			}

			for (auto& [entity, timer] : util::entity_map) {
				auto coords{ g_utils->coords(entity) };
				if (ENTITY::DOES_ENTITY_EXIST(entity)) {
					if (ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(entity)) {
						FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, (int)eExplosionTag::GRENADE, 9999.f, true, 0, 0.f, 0);
						g_utils->delete_entity(entity);
					}
				}
				else
					util::entity_map.erase(entity);
			}
		}
	}
}
