#include "src/core/script/drawing/drawing.h"
#include "src/framework/option_types/toggle.h"
#include "src/framework/option_types/icon_button.h"
#include "src/framework/option_types/button.h"

namespace Base::submenus::vehicle::ramp {
	namespace data {
		bool m_left = false;
		Object left;
		bool m_right = false;
		Object right;
		bool m_front = false;
		Object front;
		bool m_back = false;
		Object back;

		std::vector<ccp> m_ramp_type {
			"Small", "Medium", "Large", "Water", "Box"
		};
		const char* m_ramp_data[5] {
			 "prop_mp_ramp_01", "lts_prop_lts_ramp_02", "lts_prop_lts_ramp_03", "prop_jetski_ramp_01", "prop_ind_barge_01_cr"
		};

		int m_ramp_type_data = 0;
	}
	Object create_attached_ramp(Entity attach_to, Hash model, int pos = 0, bool opacitated = false) {
		g_utils->request(request_type::model, model, [=] {
			Vector3 min, max;
			MISC::GET_MODEL_DIMENSIONS(model, &min, &max);

			Vector3 dim = { max.x - min.x, max.y - min.y, max.z - min.z };

			auto coords{ g_utils->coords(attach_to) };

			*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
			Object ramp = OBJECT::CREATE_OBJECT(model, coords.x, coords.y, coords.z, true, true, false);
			*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

			switch (pos) {
			case 0:
				ENTITY::ATTACH_ENTITY_TO_ENTITY(ramp, attach_to, 0,  0, dim.y, -0.5 , 0, 0, 180, true, true, true, false, 2, true, 0);
				break;

			case 1:ENTITY::ATTACH_ENTITY_TO_ENTITY(ramp, attach_to, 0,  0, (-1) * dim.y, -0.5 , 0, 0, 0 , true, true, true, false, 2, true, 0);
				break;

			case 2:ENTITY::ATTACH_ENTITY_TO_ENTITY(ramp, attach_to, 0, (-1) * dim.x, 0, -0.5 , 0, 0, 270, true, true, true, false, 2, true, 0);
				break;

			case 3:ENTITY::ATTACH_ENTITY_TO_ENTITY(ramp, attach_to, 0, dim.x, 0, -0.5, 0, 0, 90, true, true, true, false, 2, true, 0);
				break;
			}

			if (opacitated) {
				ENTITY::SET_ENTITY_ALPHA(ramp, 100, true);
			}

			return ramp;
		});
		return 0;
	}

	void build() {
		Hash ramp{ rage::joaat(data::m_ramp_data[data::m_ramp_type_data]) };
		if (data::m_front) {
			data::front = create_attached_ramp(g_utils->vehicle(), ramp, 0);
		}

		if (data::m_back) {
			data::back = create_attached_ramp(g_utils->vehicle(), ramp, 1);
		}

		if (data::m_left) {
			data::left = create_attached_ramp(g_utils->vehicle(), ramp, 2);
		}

		if (data::m_right) {
			data::right = create_attached_ramp(g_utils->vehicle(), ramp, 3);
		}
	}
	void init() {
		draw->choose("Type", data::m_ramp_type, &data::m_ramp_type_data);
		draw->toggle("Front", &data::m_front);
		draw->toggle("Back", &data::m_back);
		draw->toggle("Left", &data::m_left);
		draw->toggle("Right", &data::m_right);
		draw->button("Build", build);
		draw->button("Delete", [] {
			g_utils->delete_entity(data::front);
			g_utils->delete_entity(data::back);
			g_utils->delete_entity(data::left);
			g_utils->delete_entity(data::right);
		});
	}
}
