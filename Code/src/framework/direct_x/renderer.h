#pragma once
#include <src/framework/ImGui/imgui.h>
#include "font_data/fa_solid_900.h"
#include "font_data/font_awesome.h"
#define RETURN(...) return { __VA_ARGS__ };
#define RETURN_DEFAULT return {};
#define IS_VALID(check) \
	if (!check) { \
		RETURN_DEFAULT; \
	}
#define RETURN_IF_VALID(check, ...) IS_VALID(check) RETURN(check, __VA_ARGS__)


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#include "resources.h"

namespace Base {
	namespace imgui {
		extern void SetColors();
		extern void CreateHandles(ComPtr<ID3D11Device> dev, ComPtr<ID3D11DeviceContext> ctx);
		extern void CreateImFont(ImFontAtlas* atlas, ImFont*& font, fs::path path, float size, ImFontConfig* cfg);
		template <size_t dataSize>
		extern void CreateImFont(ImFontAtlas* atlas, ImFont*& font, uint8_t(&data)[dataSize], float size, ImFontConfig* cfg);
	}
	class Renderer {
	public:
		Renderer();
		~Renderer();
	public:
		void Present();
	public:
		std::pair<shader_data, vec2> create_texture(fs::path filePath);
		std::map<int, frame_data> create_gif_texture(fs::path path);
		shader_data create_shader_data(unsigned char* imgData, vec2 imgSize);
	public:
		static LRESULT WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	public:
		int header_frame = 0;
		std::map<int, frame_data> m_header;
	public:
		resources m_resources{};
	public:
		ImFont* m_Roboto{};
		ImFont* m_RobotoBold{};
		ImFont* m_RobotoItalic{};
		ImFont* m_Arial{};
		ImFont* m_notification_font{};
		ImFont* m_ArialSmall{};
		ImFont* m_ArialItalic{};
		ImFont* m_ArialBold{};
		ImFont* m_ArialBoldItalic{};
		ImFont* m_ArialBlack{};
		ImFont* m_Tahoma{};
		ImFont* m_smaller_arial{};
		ImFont* m_title_font{};
		ImFont* m_icon_font{};
		ImFont* m_titlebar_font{};
		ImFontConfig m_FontCfg;
	public:
		void merge_icons_with_latest_font(float font_size, bool FontDataOwnedByAtlas = false) {
			static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

			ImFontConfig icons_config;
			icons_config.MergeMode = true;
			icons_config.PixelSnapH = true;
			icons_config.FontDataOwnedByAtlas = FontDataOwnedByAtlas;

			ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Native\\Fonts\\fa-solid-900.ttf", font_size, &icons_config, icons_ranges);
		}
	public:
		WNDPROC m_WndProc{};
		ComPtr<IDXGISwapChain> swapchain{};
		ComPtr<ID3D11Device> m_Device{};
		ComPtr<ID3D11DeviceContext> m_Context{};
	};
	inline std::unique_ptr<Renderer> g_renderer{};
}