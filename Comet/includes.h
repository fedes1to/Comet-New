#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <random>
#include <dxgi.h>
#include "external/kiero/kiero.h"
#include "external/imgui/imgui.h"
#include "external/imgui/imgui_impl_win32.h"
#include "external/imgui/imgui_impl_dx11.h"
#include "external/imgui/imgui_stdlib.h"
#include <cstdio>
#include <memoryapi.h>
#include <cstdlib>
#include <winhttp.h>
#include <vector>
#include <sstream>
#include <iostream>
#include <thread>
#include <iomanip>
#include <memory.h>

#include "Headers/obfusheader.h"
#include "Headers/Misc.h"
#include "external/kiero/minhook/include/MinHook.h"
#include "external/IL2CPP_Resolver/IL2CPP_Resolver.hpp"
#include "external/IL2CPP_Resolver/Unity/API/Camera.hpp"
#include "Headers/Memory.hpp"
#include "Headers/MemoryPatch.hpp"
#include "external/libcurl/include/curl/curl.h"
#include "Headers/fslog.h"
#include "Headers/json.hpp" // it had to happen
#include "Headers/Vectors.h"

#include "Headers/Drawing.h"

// feature/menu includes
#include "lists.hpp"
#include "Features/Helpers.hpp"
#include "Features/Pointers.hpp"
#include "Features/Requests.hpp"
#include "Features/Patches.hpp"
#include "Features/Hooks.hpp"
#include "Menu.hpp"

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;