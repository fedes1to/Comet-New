#define CURL_STATICLIB

#pragma comment (lib,"external/libcurl/lib/libcurl_a.lib")
#pragma comment (lib,"Normaliz.lib")
#pragma comment (lib,"Ws2_32.lib")
#pragma comment (lib,"Wldap32.lib")
#pragma comment (lib,"Crypt32.lib")

#include "includes.h"
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;
WNDPROC originalWindowProcess = nullptr;
HWND hwnd;
HANDLE pHandle;

static float imguifontsize = 23.0f;
bool hasSetWindowSize = false;

void createConsole() {
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
}

void InitImGui() {
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

	ImFontConfig config;
	config.FontDataOwnedByAtlas = false;
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", imguifontsize, &config);

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}


bool init = false;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
	if (!init) {
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice))) {
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}
		else {
			return oPresent(pSwapChain, SyncInterval, Flags);
		}
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (!hasSetWindowSize) {
		ImGui::SetNextWindowSize(ImVec2(900, 650));
		hasSetWindowSize = true;
	}
	SetupImGuiStyle();
	DrawESP();
	if (menuOpen)
		DrawMenu();
	
	ImGui::Render();
	
	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}


DWORD WINAPI MainThread(LPVOID lpReserved) {
	bool init_hook = false;
	do {
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success) {
			fslog::info("Initializing il2cpp");
			IL2CPP::Initialize();
			fslog::info("Il2cpp initialized");
			createConsole();
			fslog::info("*Credit [fedesito], [0SD47 - Useless]", 1); //if you delete 0SD47 you are gay
			fslog::info("*Do not make a selection on this console!*\n\tPress the HOME button to close/open Comet!\n\n", 1);

			fslog::info("Initializing pointers");
			initPointers();
			fslog::info("Pointers initialized");

			kiero::bind(8, (void**)&oPresent, hkPresent);
			fslog::info("Calling hooks");
			hooks();
			fslog::info("Hooks called");
			init_hook = true;
			hwnd = FindWindowA(0, ("PixelStrike3D"));
			GetWindowThreadProcessId(hwnd, &pid);
			pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

			fslog::info("[Info] Comet loaded, PID: {}", pid);
		}
	} while (!init_hook);

	std::thread keyStateThread([]() {
		while (true) {
			if ((GetAsyncKeyState(VK_HOME) & 1)) {
				menuOpen = !menuOpen;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
	});

	keyStateThread.join();

	return TRUE;
}

//Freeze
//Freeze
//Freeze
//UnFreeze
BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}
