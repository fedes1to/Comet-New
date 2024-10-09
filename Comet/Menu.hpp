#pragma once

std::string version, objectName;

typedef void (*CommandFunction)();

HINSTANCE hDll;

void LoadFunctions() {
	hDll = LoadLibrary("IpConfigCommands.dll");
}

void UnloadFunctions() {
	if (hDll) {
		FreeLibrary(hDll);
	}
}

CommandFunction GetFunction(const char* funcName) {
	return (CommandFunction)GetProcAddress(hDll, funcName);
}











int buyAmount = 0;

void SetupImGuiStyle()
{
	// Deep Dark style by janekb04 from ImThemes
	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha = 1.0f;
	style.DisabledAlpha = 0.6000000238418579f;
	style.WindowPadding = ImVec2(8.0f, 8.0f);
	style.WindowRounding = 7.0f;
	style.WindowBorderSize = 1.0f;
	style.WindowMinSize = ImVec2(32.0f, 32.0f);
	style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_Left;
	style.ChildRounding = 4.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 4.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(5.0f, 2.0f);
	style.FrameRounding = 3.0f;
	style.FrameBorderSize = 1.0f;
	style.ItemSpacing = ImVec2(6.0f, 6.0f);
	style.ItemInnerSpacing = ImVec2(6.0f, 6.0f);
	style.CellPadding = ImVec2(6.0f, 6.0f);
	style.IndentSpacing = 25.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 15.0f;
	style.ScrollbarRounding = 9.0f;
	style.GrabMinSize = 10.0f;
	style.GrabRounding = 3.0f;
	style.TabRounding = 4.0f;
	style.TabBorderSize = 1.0f;
	style.TabMinWidthForCloseButton = 0.0f;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.4980392158031464f, 0.4980392158031464f, 0.4980392158031464f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.1882352977991104f, 0.9200000166893005f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.1882352977991104f, 0.2899999916553497f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.239999994635582f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.0470588244497776f, 0.0470588244497776f, 0.0470588244497776f, 0.5400000214576721f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.1882352977991104f, 0.5400000214576721f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2274509817361832f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.05882352963089943f, 0.05882352963089943f, 0.05882352963089943f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.1372549086809158f, 0.1372549086809158f, 0.1372549086809158f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.0470588244497776f, 0.0470588244497776f, 0.0470588244497776f, 0.5400000214576721f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.3372549116611481f, 0.3372549116611481f, 0.3372549116611481f, 0.5400000214576721f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.4000000059604645f, 0.4000000059604645f, 0.4000000059604645f, 0.5400000214576721f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.5568627715110779f, 0.5568627715110779f, 0.5568627715110779f, 0.5400000214576721f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.3294117748737335f, 0.6666666865348816f, 0.8588235378265381f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.3372549116611481f, 0.3372549116611481f, 0.3372549116611481f, 0.5400000214576721f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.5568627715110779f, 0.5568627715110779f, 0.5568627715110779f, 0.5400000214576721f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.0470588244497776f, 0.0470588244497776f, 0.0470588244497776f, 0.5400000214576721f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.1882352977991104f, 0.5400000214576721f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2274509817361832f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.0f, 0.0f, 0.0f, 0.5199999809265137f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.0f, 0.0f, 0.0f, 0.3600000143051147f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2274509817361832f, 0.3300000131130219f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.2784313857555389f, 0.2784313857555389f, 0.2784313857555389f, 0.2899999916553497f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.4392156898975372f, 0.4392156898975372f, 0.4392156898975372f, 0.2899999916553497f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.4000000059604645f, 0.4392156898975372f, 0.4666666686534882f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.2784313857555389f, 0.2784313857555389f, 0.2784313857555389f, 0.2899999916553497f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.4392156898975372f, 0.4392156898975372f, 0.4392156898975372f, 0.2899999916553497f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.4000000059604645f, 0.4392156898975372f, 0.4666666686534882f, 1.0f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.0f, 0.0f, 0.0f, 0.5199999809265137f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.1372549086809158f, 0.1372549086809158f, 0.1372549086809158f, 1.0f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2000000029802322f, 0.3600000143051147f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.0f, 0.0f, 0.0f, 0.5199999809265137f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.1372549086809158f, 0.1372549086809158f, 0.1372549086809158f, 1.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.5199999809265137f);
	style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.0f, 0.0f, 0.0f, 0.5199999809265137f);
	style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2784313857555389f, 0.2784313857555389f, 0.2784313857555389f, 0.2899999916553497f);
	style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.05999999865889549f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2274509817361832f, 1.0f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.3294117748737335f, 0.6666666865348816f, 0.8588235378265381f, 1.0f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 0.0f, 0.0f, 0.699999988079071f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.0f, 0.0f, 0.0f, 0.2000000029802322f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.0f, 0.0f, 0.0f, 0.3499999940395355f);
	style.FramePadding = ImVec2(4, 2);
	style.ItemSpacing = ImVec2(4, 2);
	style.ScrollbarSize = 12;
}

void DrawMenu() {
	ImVec2 displaySize = ImGui::GetIO().DisplaySize;
	ImVec2 windowSize = ImVec2(displaySize.x * 0.3f, displaySize.y * 0.66f);
	ImGui::SetNextWindowSize(windowSize);
	ImGuiWindowFlags windowflags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar |
									ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize;
	ImGui::Begin("Comet", &menuOpen, windowflags);
	{
		ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_NoTooltip;
		ImGuiStyle& style = ImGui::GetStyle();
		style.FrameRounding = 10.0f;
		style.WindowRounding = 10.0f;
		style.ScrollbarRounding = 10.0f;

		if (ImGui::BeginTabBar(OBFUSTR("Menu"), tab_bar_flags)) {
			if (ImGui::BeginTabItem(OBFUSTR("Gameplay"))) {
				ImGui::Separator();

				ImGui::Checkbox("Triggerbot", (bool*)&triggerbot);
				ImGui::Checkbox("Rapid Fire", (bool*)&firerate);
				ImGui::Checkbox("Grenade Bullet", (bool*)&GrenadeBullet);
				ImGui::Checkbox("Insta Scope", (bool*)&InstaScope);
				ImGui::Checkbox("Long Melee", (bool*)&LongMelee);
				ImGui::Checkbox("Rapid Equipment", (bool*)&RapidEquipment);
				ImGui::Checkbox("Unlimited Ammo", (bool*)&ammo);
				ImGui::Checkbox("No Recoil", (bool*)&recoil);
				ImGui::Checkbox("Infinite Equipment", (bool*)&eqcooldown);

				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Checkbox("Fake Head Pos", (bool*)&FakeHeadPos);
				ImGui::Checkbox("Fly Hack", (bool*)&FlyHack);
				ImGui::Checkbox("Bonus Speed Hack", (bool*)&bonusSpeedHack);
				ImGui::SameLine();
				ImGui::Text("[Risk it?]");
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Checkbox("Always get free cases at end of match", (bool*)&getfreecases);
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(OBFUSTR("Visual"))) {
				ImGui::Checkbox("ESP", (bool*)&esp);

				ImGui::Separator();
				if (ImGui::CollapsingHeader("ESP - Properties")) {
					ImGui::Checkbox("ESP: Show teammates", (bool*)&esp_teammates);
				}

				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(OBFUSTR("Account"))) {

				if (ImGui::Button("Add item"))
					addItem(410);

				if (ImGui::Button("attempt to add all items"))
					addAllItems();

				if (ImGui::Button("get vip"))
					buyVIP();

				if (ImGui::Button("get mvp"))
					buyMVP();

				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(OBFUSTR("Info"))) {
				ImGui::TextUnformatted(OBFUSTR("Version:"));
				if (version.empty())
					version = Application$$Version()->ToString();
				ImGui::Text(version.c_str());

				ImGui::Checkbox("debug", &debug);
				if (ImGui::Button("reset ip")) {
					CommandFunction releaseIP = GetFunction("ReleaseIP");
					if (releaseIP) releaseIP();
					CommandFunction renewIP = GetFunction("RenewIP");
					if (renewIP) renewIP();
					CommandFunction flushDNS = GetFunction("FlushDNS");
					if (flushDNS) flushDNS();


				}
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(OBFUSTR("Testing"))) {
				ImGui::InputText("object name", &objectName);
				ImGui::Checkbox("index Bullet", (bool*)&test16);
				ImGui::Checkbox("clip", (bool*)&test15);
				ImGui::Checkbox("BulletSpeed", (bool*)&test17);




				if (ImGui::Button("instantiate")) {
					auto res = Resources$$Load(CreateIl2cppString(objectName.c_str()));
					if (res)
						Instantiate(res);
					else
						fslog::error("couldn't find object");
				}

				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
	}
	ImGui::End();

}