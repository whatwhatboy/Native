#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "STB/image.h"
#include "STB/image_write.h"
#include "renderer.h"
#include "src/fiber/fiber_helper.h"
#include "src/framework/framework.h"
#include "src/utility/setting.h"

namespace Base {
	image_data write_png_to_memory(int x, int y, int comp, const void* data, int strideBytes, uint32_t delay) {
		int len;
		unsigned char* png{ stbi_write_png_to_mem((const unsigned char*)data, strideBytes, x, y, comp, &len) };
		if (png == NULL)
			return {};
		return { png, len, delay };
	}
	img load_image_from_memory(image_data data) {
		vec2 vec{};
		auto image{ stbi_load_from_memory(data.m_image_bytes, data.m_image_length, (int*)&vec.m_x, (int*)&vec.m_y, NULL, 0) };
		if (image == nullptr) {
			return {};
		}
		return { image, vec };
	}
	std::map<int, image_data> load_gif(fs::path path) {
		std::map<int, image_data> frames{};
		FILE* file{ fopen(path.string().c_str(), ("rb")) };
		if (!file)
			return frames;
		fseek(file, 0L, SEEK_END);
		long size{ ftell(file) };
		fseek(file, 0L, SEEK_SET);
		void* buffer{ malloc(size) };
		fread(buffer, size, 1, file);
		fclose(file);
		int* delays{};
		int width{}, height{}, frameCount{}, comp{};
		auto data{ stbi_load_gif_from_memory((stbi_uc*)buffer, size, &delays, &width, &height, &frameCount, &comp, NULL) };
		free(buffer);
		size_t bytes = width * comp;
		for (size_t i{}; i != frameCount; ++i) {
			frames.insert(std::make_pair(i, write_png_to_memory(width, height, comp, data + bytes * height * i, 0, delays[i])));
		}
		stbi_image_free(data);
		return frames;
	}
	namespace imgui {
		void SetColors() {
			auto&& Style = ImGui::GetStyle();
			auto& Colors = Style.Colors;
			Style.Alpha = 1.f;
			Style.WindowPadding = ImVec2(2, 2);
			Style.PopupRounding = 0.f;
			Style.FramePadding = { 8.f, 4.f };
			Style.ItemSpacing = ImVec2(4, 4);
			Style.ItemInnerSpacing = ImVec2(4, 4);
			Style.TouchExtraPadding = { 0.f, 0.f };
			Style.IndentSpacing = 10.f;
			Style.ScrollbarSize = 0.f;
			Style.ScrollbarRounding = 8.f;
			Style.GrabMinSize = 90.f;
			Style.GrabRounding = 12.25f;
			Style.WindowBorderSize = 0.0f;
			Style.ChildBorderSize = 0.f;
			Style.PopupBorderSize = 0;
			Style.FrameBorderSize = 0.f;
			Style.TabBorderSize = 0.f;
			Style.WindowRounding = 0.f;
			Style.ChildRounding = 3.f;
			Style.FrameRounding = 4.25f;
			Style.TabRounding = 4.25f;
			Style.MouseCursorScale = 0.7f;
			Style.WindowTitleAlign = { 0.5f, 0.5f };
			Style.ButtonTextAlign = { 0.5f, 0.5f };
			Style.DisplaySafeAreaPadding = { 2.f, 2.f };
			Style.GrabMinSize = 20.0;
			// Check if the left mouse button is pressed
			auto mainColor{ ImColor(71, 118, 230, 255) };

			Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
			Colors[ImGuiCol_TextDisabled] = ImVec4(1.00f, 0.90f, 0.19f, 1.00f);
			Colors[ImGuiCol_WindowBg] = ImColor(30, 30, 30, 250);
			Colors[ImGuiCol_ChildBg] = ImColor(77, 78, 82, 101);
			Colors[ImGuiCol_PopupBg] = ImColor(45, 45, 45, 255);
			Colors[ImGuiCol_Border] = mainColor;
			Colors[ImGuiCol_BorderShadow] = ImColor(0, 183, 254, 255);
			Colors[ImGuiCol_FrameBg] = ImColor(77, 78, 82, 101);
			Colors[ImGuiCol_FrameBgActive] = ImColor(77, 78, 82, 101);
			Colors[ImGuiCol_FrameBgHovered] = ImColor(77, 78, 82, 101);
			Colors[ImGuiCol_TitleBg] = ImColor(37, 37, 37, 255);
			Colors[ImGuiCol_TitleBgActive] = ImColor(37, 37, 37, 255);
			Colors[ImGuiCol_TitleBgCollapsed] = ImColor(0, 183, 254, 255);
			Colors[ImGuiCol_MenuBarBg] = ImColor(0, 183, 254, 255);
			Colors[ImGuiCol_ScrollbarBg] = ImColor(0, 0, 0, 0);
			Colors[ImGuiCol_ScrollbarGrab] = ImColor(77, 78, 82, 101);
			Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(77, 78, 82, 101);
			Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(77, 78, 82, 101);
			Colors[ImGuiCol_CheckMark] = ImColor(0, 183, 254, 255);
			Colors[ImGuiCol_SliderGrab] = mainColor;
			Colors[ImGuiCol_SliderGrabActive] = mainColor;
			Colors[ImGuiCol_Button] = ImColor(60, 60, 60, 255);
			Colors[ImGuiCol_ButtonHovered] = ImColor(90, 90, 90, 255);
			Colors[ImGuiCol_ButtonActive] = ImColor(90, 90, 90, 255);
			Colors[ImGuiCol_Header] = ImVec4(0.37f, 0.37f, 0.37f, 0.31f);
			Colors[ImGuiCol_HeaderHovered] = ImVec4(0.38f, 0.38f, 0.38f, 0.37f);
			Colors[ImGuiCol_HeaderActive] = ImVec4(0.37f, 0.37f, 0.37f, 0.51f);
			Colors[ImGuiCol_Separator] = ImColor(100, 100, 100, 200);
			Colors[ImGuiCol_SeparatorHovered] = ImColor(100, 100, 100, 200);
			Colors[ImGuiCol_SeparatorActive] = ImColor(100, 100, 100, 200);
			Colors[ImGuiCol_ResizeGrip] = ImColor(0, 183, 254, 255);
			Colors[ImGuiCol_ResizeGripHovered] = ImColor(0, 183, 254, 255);
			Colors[ImGuiCol_ResizeGripActive] = ImColor(0, 183, 254, 255);
			Colors[ImGuiCol_Tab] = ImColor(25, 25, 25, 245);
			Colors[ImGuiCol_TabHovered] = ImColor(86, 87, 87, 255);
			Colors[ImGuiCol_TabActive] = mainColor;
			Colors[ImGuiCol_TabUnfocused] = ImColor(103, 0, 250, 245);
			Colors[ImGuiCol_TabUnfocusedActive] = ImColor(103, 0, 245, 245);
			Colors[ImGuiCol_PlotLines] = ImColor(103, 0, 255, 255);
			Colors[ImGuiCol_PlotLinesHovered] = ImColor(255, 255, 255, 255);
			Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
			Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
			Colors[ImGuiCol_TextSelectedBg] = ImColor(255, 255, 255, 255);
			Colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
			Colors[ImGuiCol_NavHighlight] = ImColor(255, 255, 255, 255);
			Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
			Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
			Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
		}
		void CreateHandles(ComPtr<ID3D11Device> dev, ComPtr<ID3D11DeviceContext> ctx) {
			dev->GetImmediateContext(ctx.GetAddressOf());
			ImGui::CreateContext();
			SetColors();
			ImGui_ImplDX11_Init(dev.Get(), ctx.Get());
			ImGui_ImplWin32_Init(g_pointers->m_game_window);
		}
		void CreateImFont(ImFontAtlas* atlas, ImFont*& font, fs::path path, float size, ImFontConfig* cfg) {
			font = atlas->AddFontFromFileTTF(path.string().c_str(), size, cfg);
		}
		template <size_t dataSize>
		void CreateImFont(ImFontAtlas* atlas, ImFont*& font, uint8_t(&data)[dataSize], float size, ImFontConfig* cfg) {
			font = atlas->AddFontFromMemoryTTF(data, dataSize, size, cfg);
		}
	}
	void create_imfont(ImFontAtlas* Atlas, ImFont*& font, fs::path path, float size, ImFontConfig* config) {
		font = Atlas->AddFontFromFileTTF(path.string().c_str(), size, config);
	}
	template <size_t dataSize>
	void create_imfont(ImFontAtlas* Atlas, ImFont*& font, uint8_t(&Data)[dataSize], float size, ImFontConfig* config) {
		font = Atlas->AddFontFromMemoryTTF(Data, dataSize, size, config);
	}
	Renderer::Renderer() : swapchain(*g_pointers->m_swapchain) {
		
		m_WndProc = WNDPROC(SetWindowLongPtrA(g_pointers->m_game_window, GWLP_WNDPROC, LONG_PTR(&Renderer::WndProc)));
		if (FAILED(swapchain->GetDevice(__uuidof(ID3D11Device), (void**)m_Device.GetAddressOf())))
			throw std::runtime_error("Failed to get the D3D device!");
		imgui::CreateHandles(m_Device, m_Context);
		fs::path path{ fs::path("C:").append("Windows").append("Fonts") };
		fs::path basePath{ fs::path("C:\\Native\\") };
		fs::path fontPath{ fs::path(basePath).append("Fonts") };
		fs::path resourcePath{ fs::path(basePath).append("Resources") };
		fs::path headerPath{ fs::path(basePath).append("Headers") };
		ImFontAtlas* atlas{ ImGui::GetIO().Fonts };
		float globalSize{ 60.f };
		m_FontCfg.FontDataOwnedByAtlas = false;
		create_imfont(atlas, m_Roboto, fs::path(fontPath).append("Roboto-Regular.ttf"), globalSize, &m_FontCfg);
		create_imfont(atlas, m_RobotoBold, fs::path(fontPath).append("Roboto-Bold.ttf"), globalSize, &m_FontCfg);
		create_imfont(atlas, m_RobotoItalic, fs::path(fontPath).append("Roboto-Italic.ttf"), globalSize, &m_FontCfg);
		create_imfont(atlas, m_Arial, fs::path(path).append("Arial.ttf"), globalSize, &m_FontCfg);
		create_imfont(atlas, m_ArialSmall, fs::path(path).append("Arial.ttf"), 25.f, &m_FontCfg);
		create_imfont(atlas, m_ArialBold, fs::path(path).append("ArialBD.ttf"), globalSize, &m_FontCfg);
		create_imfont(atlas, m_ArialBoldItalic, fs::path(path).append("ArialBI.ttf"), globalSize, &m_FontCfg);
		create_imfont(atlas, m_ArialBlack, fs::path(path).append("AriBLK.ttf"), globalSize, &m_FontCfg);
		create_imfont(atlas, m_ArialItalic, fs::path(path).append("ArialI.ttf"), globalSize, &m_FontCfg);
		create_imfont(atlas, m_Tahoma, fs::path(path).append("Tahoma.ttf"), globalSize, &m_FontCfg);
		m_Arial = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 19.f, &m_FontCfg);
		m_notification_font = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 19.f, &m_FontCfg);
		m_ArialItalic = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\ArialI.ttf", 19.f, &m_FontCfg);
		m_ArialBold = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\ArialBD.ttf", 19.f, &m_FontCfg);
		m_smaller_arial = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 12.0f, &m_FontCfg);
		m_title_font = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 11.5f, &m_FontCfg);
		m_icon_font = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 19.f, &m_FontCfg);
		merge_icons_with_latest_font(22.f, false);
		m_titlebar_font = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 19.f, &m_FontCfg);
		m_resources.add({ "Header", create_texture(fs::path(headerPath).append(g_interface->m_header_image)).first });
		m_resources.add({ "ArrowRight", create_texture(fs::path(resourcePath).append("ArrowRight.png")).first });
		m_resources.add({ "ArrowUp", create_texture(fs::path(resourcePath).append("ArrowUp.png")).first });
		m_resources.add({ "Arrows", create_texture(fs::path(resourcePath).append("Arrows.png")).first });
		m_resources.add({ "ArrowDown", create_texture(fs::path(resourcePath).append("ArrowDown.png")).first });
		m_resources.add({ "ArrowsLeftRight", create_texture(fs::path(resourcePath).append("ArrowsLeftRight.png")).first });
		m_resources.add({ "On", create_texture(fs::path(resourcePath).append("On.png")).first });
		m_resources.add({ "Off", create_texture(fs::path(resourcePath).append("Off.png")).first });
		m_resources.add({ "Keyboard", create_texture(fs::path(resourcePath).append("Keyboard.png")).first });
	}
	Renderer::~Renderer() {
		SetWindowLongPtrA(g_pointers->m_game_window, GWLP_WNDPROC, LONG_PTR(m_WndProc));
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}
	void Renderer::Present() {
		if (g_interface->m_opened && g_settings.lock_mouse) {
			ImGui::GetIO().MouseDrawCursor = true;
			ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
		}
		else {
			ImGui::GetIO().MouseDrawCursor = false;
			ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouse;
		}
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		g_dx_fiber_manager.on_tick();
		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
	ChatData* get_chat_data() {
		return *g_pointers->m_chat_data;
	}
	LRESULT Renderer::WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
		if (g_interface->m_opened && Msg == WM_KEYUP && wParam == 'X')
			g_settings.lock_mouse = !g_settings.lock_mouse;

		if (Msg == WM_KEYUP && wParam == 'U' && !g_interface->m_command_box_opened && !get_chat_data()->m_chat_open) {
			g_interface->m_command_box_opened = !g_interface->m_command_box_opened;
			std::strcpy(g_interface->m_command_box_input, "");
		}

		if (g_renderer.get()) {
			if (ImGui::GetCurrentContext())
				ImGui_ImplWin32_WndProcHandler(hWnd, Msg, wParam, lParam);
			return CallWindowProcA(g_renderer->m_WndProc, hWnd, Msg, wParam, lParam);
		}
		return -1;
	}
	std::pair<shader_data, vec2> Renderer::create_texture(fs::path filePath) {
		vec2 v2;
		unsigned char* imgData = stbi_load(filePath.string().c_str(), (int*)&v2.m_x, (int*)&v2.m_y, NULL, 4);
		if (!imgData)
			return {};
		return std::make_pair(create_shader_data(imgData, v2), v2);
	}
	std::map<int, frame_data> Renderer::create_gif_texture(fs::path path) {
		auto gifData = load_gif(path);
		std::map<int, frame_data> tmpArr{};
		for (auto& fr : gifData) {
			auto img{ load_image_from_memory(fr.second) };
			tmpArr.insert(std::make_pair(fr.first, frame_data({ fr.second.m_frame_delay, create_shader_data(img.m_data, img.m_v2) })));
		}
		return tmpArr;
	}
	shader_data Renderer::create_shader_data(unsigned char* imgData, vec2 imgSize) {
		if (!imgData)
			return {};
		ID3D11ShaderResourceView* resourceView{};
		ID3D11Texture2D* texture{};
		D3D11_TEXTURE2D_DESC desc{ imgSize.m_x, imgSize.m_y, 1, 1, DXGI_FORMAT_R8G8B8A8_UNORM, { 1 }, D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0 };
		D3D11_SUBRESOURCE_DATA subResource{ imgData, desc.Width * 4, 0 };
		m_Device.Get()->CreateTexture2D(&desc, &subResource, &texture);
		if (!texture)
			return {};
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{ DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_SRV_DIMENSION_TEXTURE2D, { 0, desc.MipLevels } };
		m_Device.Get()->CreateShaderResourceView(texture, &srvDesc, (std::add_pointer_t<decltype(resourceView)>) & resourceView);
		return { texture, resourceView };
	}
}