#pragma once
#include <d3d11.h>
#include "src/utility/common/common.h"

namespace Base {
	struct vec2 { uint32_t m_x, m_y; };
	struct img { unsigned char* m_data; vec2 m_v2; };
	struct image_data { unsigned char* m_image_bytes; int m_image_length; uint32_t m_frame_delay; };
	struct shader_data { ID3D11Resource* m_resource{}; ID3D11ShaderResourceView* m_resource_view{}; };
	struct frame_data { uint32_t m_frame_delay; shader_data m_shader; };

	class renderer_queue {
	public:
		void tick() {
			for (auto& fn : m_funcs)
				fn.second();
		}
		void add(str id, std::function<void()> func) {
			if (m_funcs.size() == NULL)
				m_funcs.insert({ id, std::move(func) });
		}
		void remove(str id) {
			m_funcs.erase(id);
		}
	public:
		std::map<str, std::function<void()>> m_funcs;
	};
	inline renderer_queue g_renderer_queue;

	struct resource {
		str m_name{};
		shader_data m_data{};
		decltype(m_data.m_resource_view) get_shader_resource() {
			return m_data.m_resource_view;
		}
	};
	struct resources {
		resource get(str key) {
			for (auto& r : m_table) {
				if (!r.m_name.compare(key.c_str())) {
					return r;
				}
			}
			return {};
		}
		void add(resource resource) {
			m_table.push_back(resource);
		}
		ID3D11ShaderResourceView* operator[](str key) {
			return get(key).get_shader_resource();
		}
		std::vector<resource> m_table{};
	};
}