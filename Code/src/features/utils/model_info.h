#pragma once
#include "src/memory/pointers/pointers.h"

namespace Base {
	class model_info {
	public:
		static bool does_model_exist(const rage::joaat_t hash) {
			if (const auto model = model_info::get_model(hash); model)
				return true;
			return false;
		}

		template<typename T = CBaseModelInfo*>
		static T get_model(const rage::joaat_t hash) {
			const auto model_table = g_pointers->m_model_table;
			for (auto i = model_table->m_lookup_table[hash % model_table->m_lookup_key]; i; i = i->m_next) {
				if (i->m_hash == hash) {
					if (const auto model = model_table->m_data[i->m_idx]; model) {
						return reinterpret_cast<T>(model);
					}
				}
			}
			return nullptr;
		}

		static CVehicleModelInfo* get_vehicle_model(const rage::joaat_t hash) {
			if (const auto model = model_info::get_model<CVehicleModelInfo*>(hash); model && model->m_model_type == eModelType::Vehicle)
				return model;
			return nullptr;
		}

		template<typename T, typename... Args>
		static bool is_model_of_type(const rage::joaat_t hash, const T arg, const Args... args) {
			bool of_type = false;
			if (const auto model = model_info::get_model(hash)) {
				of_type = model->m_model_type == arg;
				(
					[&of_type, &model](eModelType type) {
						of_type |= model->m_model_type == type;
					}(args),
						...);
			}
			return of_type;
		}
	};
}