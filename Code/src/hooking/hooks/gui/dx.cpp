#include "src/hooking/hooking.h"

namespace Base {
#define CALL(hook, ...) static_cast<decltype(&hook)>(g_hooking->m_Original##hook)(__VA_ARGS__);
#define VMT_CALL(h, hook, ...) g_hooking->m_##h##vmt.get_original<decltype(&hooks::##hook)>(hooks::##hook##Index)(__VA_ARGS__);

	HRESULT hooks::Present(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) {
		g_renderer->Present();
		return VMT_CALL(dx_, Present, swapChain, syncInterval, flags)
	}
	HRESULT hooks::ResizeBuffers(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) {
		HRESULT Result{};
		ImGui_ImplDX11_InvalidateDeviceObjects();
		Result = VMT_CALL(dx_, ResizeBuffers, swapChain, bufferCount, width, height, newFormat, swapChainFlags);
		if (SUCCEEDED(Result)) {
			ImGui_ImplDX11_CreateDeviceObjects();
		}
		return Result;
	}
}