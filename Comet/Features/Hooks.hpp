std::list<void*> hooked_methods; // use this for detach ig

bool hook_func(void* address, void* fake_func, void** out_origin_func) {
	if (MH_CreateHook(address, fake_func, out_origin_func) != MH_OK) {
		fslog::error("Failed to create hook {}", address);
		return false;
	}
	if (MH_EnableHook(address) != MH_OK) {
		fslog::error("Failed to enable hook {}", address);
		return false;
	}
	hooked_methods.push_back(address);
	return true;
}

#define HOOKD(offset, func) hook_func((void*)OFFSET(offset), (void *)func, (void **)&old_##func)
#define HOOKD_IL2CPP(klass, name, func) hook_func(IL2CPP::Class::Utils::GetMethodPointer(OBFUSTR(klass), OBFUSTR(name)), (void *)func, (void **)&old_##func)

void (*old_Debug$$Log)(void* object);
void Debug$$Log(void* object) {
	fslog::debug("[Debug.Log] {}", SerializeObject(object));
	return old_Debug$$Log(object);
}

void (*old_Debug$$LogWarning)(void* object);
void Debug$$LogWarning(void* object) {
	fslog::debug("[Debug.LogWarning] {}", SerializeObject(object));
	old_Debug$$LogWarning(object);
}

void (*old_Debug$$LogError)(void* object);
void Debug$$LogError(void* object) {
	fslog::debug("[Debug.LogError] {}", SerializeObject(object));
	old_Debug$$LogError(object);
}

void (*old_ProcessMouseEvent)(void* self, int id);
void ProcessMouseEvent(void* self, int id) {
	if (menuOpen) {
		return;
	}
 	return old_ProcessMouseEvent(self, id);
}

void (*old_SmartFox$$Send)(void* self, void* request);
void SmartFox$$Send(void* self, void* request) {
	auto message = BaseRequest$$Message(request);
	if (!message) {
		fslog::error("failed to get message");
		return old_SmartFox$$Send(self, request);
	}
	auto content = Message$$Content(message);
	if (!content) {
		fslog::error("failed to get content");
		return old_SmartFox$$Send(self, request);
	}
	auto sfsByteObj = SFSObject$$ToBinary(content);

	if (GetField<bool>(sfsByteObj, 0x1C))
		ByteArray$$Uncompress(sfsByteObj);

	auto realByteArray = ByteArray$$GetBytes(sfsByteObj);

	std::ostringstream ss;

	for (int i = 0; i < realByteArray->m_uMaxLength; i++)
		ss << std::hex << realByteArray->At(i);
	fslog::debug("[SmartFox.Send] {}", ss.str());

	return old_SmartFox$$Send(self, request);
}

bool getfreecases = false;

void (*old_EndGameMenu)(Unity::CObject* self);
void EndGameMenu(Unity::CObject* self) {
	if (getfreecases) {
		self->SetMemberValue<bool>("wonCase", true);
	}
	return old_EndGameMenu(self);
}

bool esp = false;
bool esp_teammates = true;
int timer = 30;
Unity::il2cppArray<void**>* players;

bool triggerbot = false;
bool debug = false;

void UpdateCallback() {
	/*bool f = false;
	IL2CPP::Class::Utils::SetStaticField(self->m_Object.m_pClass, "banned", &f);*/
	if (timer <= 0) {
		if (debug)
			fslog::info("Updated player list");
		players = Unity::Object::FindObjectsOfType<void*>("Health");
		timer = 30;
	}
	timer--;
}

bool firerate = false;
bool RapidEquipment = false;

bool ammo = false;
bool recoil = false;
bool eqcooldown = false;
bool GrenadeBullet = false;
bool coinstest = false;

bool InstaScope = false;
bool LongMelee = false;

bool believable = false;

int my_team = 0;


bool firing = false;
int fireKey;
bool isTeamMode = false;


//0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85 0x85
//0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86 0x86
//0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87 0x87
//0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2 0x16E2
void (*old_WeaponController$$Update)(Unity::CObject* self);
void WeaponController$$Update(Unity::CObject* self) {
	if (self != nullptr) {
		Unity::CObject* health = self->GetMemberValue<Unity::CObject*>("health");
		if (!is_health_mine(health))
			return old_WeaponController$$Update(self);
		my_team = health->GetMemberValue<int>("team");

		Unity::CObject* ModMenu = self->GetMemberValue<Unity::CObject*>("ModMenu"); // ???

		if (coinstest) {
			self->SetMemberValue<float>("coin", 999999999.0f);
		}


		if (ammo) {
			if (!believable) {
				self->SetMemberValue<bool>("unlimitedAmmo", true);
			}
			else {
				self->SetMemberValue<bool>("bottomlessMagazine", true);
			}
		}

		if (GrenadeBullet) { //fedesito fix it [easy to fix but im lazy]
			self->SetMemberValue<float>("weaponType", 5.0f); // 4byte value [1 = Rifle] [2 = Sniper] [3 = Unknown] [5 = Grenade] [6 = Unknown] [7 = Unknown] [8 = Unknown] [9 = Rbg]
		}
		if (InstaScope) {
			self->SetMemberValue<float>("weaponScopeSpeed", 9999.0f);
		}
		if (RapidEquipment) {
			self->SetMemberValue<float>("weaponIndex", 50.0f); //[Glitchy]
		}
		if (LongMelee) {
			self->SetMemberValue<float>("range", 999999999999999999999999999999.0f); //[DNT Work]
		}

		//more stuff coming soon
		Unity::CObject* cur_wep = self->GetMemberValue<Unity::CObject*>("currentWeapon");

		void* cam = self->GetMemberValue<void*>("camera");

		fireKey = SettingsManager$$getSettingKeyBind(IL2CPP::Class::Utils::GetStaticField("SettingsManager", "instance"), CreateIl2cppString("Fire"));

		if (firerate) {
			cur_wep->SetObscuredValue<float>("newFireRate", 0.0f);
		}

		if (recoil) {
			cur_wep->SetObscuredValue<float>("newRecoil", 0.0f);
			cur_wep->SetObscuredValue<float>("newHipRecoil", 0.0f);
		}


		if (eqcooldown) {
			self->SetMemberValue<float>("equipmentCooldown", 0.0f);
			self->SetMemberValue<float>("equipmentTimer", 0.0f);
		}


		if (triggerbot) {
			void* cam = get_player_camera();	
			if (cam != nullptr) {
				void* trn = Component$$get_transform(cam);
				if (trn != nullptr) {
					il2cppVector3 pos = Transform$$get_position(trn);
					il2cppVector3 fw = Transform$$TransformDirection(trn, il2cppVector3::Forward());
					// pos += fw * 1; // offset to avoid player
					RaycastHit rchit = { };
					bool did_ray = Physics$$Raycast(pos, fw, &rchit, 300.0f, self->GetMemberValue<int>("layerMask"));
					if (did_ray) {
						void* rchit_collider = RaycastHit$$get_collider(rchit);
						if (rchit_collider != nullptr) {
							void* rchit_obj = Component$$get_gameObject(rchit_collider);
							if (rchit_obj != nullptr) {
								Unity::System_String* tag = GameObject$$get_tag(rchit_obj);
								bool is_player = (strcmp(tag->ToString().c_str(), "Player") == 0 || strcmp(tag->ToString().c_str(), "Head") == 0);
								if (cur_wep != nullptr && is_player && !firing) {
									if (isTeamMode) {
										void* health = GameObject$$GetComponentInParent(rchit_obj, IL2CPP::Class::GetSystemType("Health"));
										if (health != nullptr && GetField<int>(health, IL2CPP::Class::Utils::GetFieldOffset("Health", "team")) != my_team) {
											firing = true;
										}
									}
									else {
										firing = true;
									}
								}
								else {
									firing = false;
								}
							}
						}
					}
				}
			}
		}
		else {
			firing = false;
		}
	}
	return old_WeaponController$$Update(self);
}

void DrawESP() {
	void* cam = get_player_camera();
	if (esp && cam) {
		for (size_t i = 0; i < players->m_uMaxLength; i++) {
			void* player = players->At(i);
			if (player != nullptr) {
				if (!is_health_mine_voidp(player)) {
					void* transform = Component$$get_transform(player);
					il2cppVector3 position = Transform$$get_position(transform);
					il2cppVector3 w2s_position = Camera$$WorldToScreenPoint(cam, position);
					if (w2s_position.Z > 0) {
						il2cppVector3 w2s = w2s_position;
						il2cppVector3 head = Camera$$WorldToScreenPoint(cam, position + il2cppVector3(0, 3, 0));

						ImVec2 displaySize = ImGui::GetIO().DisplaySize;
						ImVec4 espColor = { 1, 0, 0, 1 };

						if (isTeamMode) {
							if (GetField<int>(player, IL2CPP::Class::Utils::GetFieldOffset("Health", "team")) == my_team) {
								if (esp_teammates)
									espColor = { 0, 1, 0, 1 };
								else
									continue;
							}
						}

						ESP::DrawLine(ImVec2(displaySize.x / 2, 0), ImVec2(head.X, displaySize.y - head.Y), espColor);

						float boxHeight = abs(head.Y - w2s.Y);
						float boxWidth = boxHeight * 0.65f;
						il2cppVector2 vBox = { head.X - (boxWidth / 2), head.Y };

						ESP::DrawFilledRect(vBox.X, displaySize.y - vBox.Y, boxWidth, boxHeight, espColor);
					}
				}
			}
		}
	}
}


bool (*old_InputHook)(int);
bool InputHook(int keyCode) {
	bool is_firing_key = fireKey == keyCode;
	if (firing && is_firing_key) {
		return true;
	}
	return old_InputHook(keyCode);
}

bool (*old_InputHook2)(int);
bool InputHook2(int keyCode) {
	bool is_firing_key = fireKey == keyCode;
	if (firing && is_firing_key) {
		return true;
	}
	return old_InputHook2(keyCode);
}

void (*old_GameShell$$Update)(Unity::CObject* self);
void GameShell$$Update(Unity::CObject* self) {
	isTeamMode = self->CallMethod<bool>("isTeamMode");
	return old_GameShell$$Update(self);
}

void hooks() {
	HOOKD_IL2CPP("Sfs2X.SmartFox", "Send", SmartFox$$Send);
	HOOKD_IL2CPP("UnityEngine.Debug", "Log", Debug$$Log);
	HOOKD_IL2CPP("UnityEngine.Debug", "LogWarning", Debug$$LogError);
	HOOKD_IL2CPP("UnityEngine.Debug", "LogError", Debug$$LogError);
	HOOKD_IL2CPP("WeaponController", "Update", WeaponController$$Update);
	HOOKD_IL2CPP("UnityEngine.Input", "GetKeyDownInt", InputHook);
	HOOKD_IL2CPP("UnityEngine.Input", "GetKeyInt", InputHook2);
	HOOKD_IL2CPP("EndGameMenu", "Update", EndGameMenu);
	HOOKD_IL2CPP("GameShell", "Update", GameShell$$Update);
	HOOKD("0x79E04B0", ProcessMouseEvent); // sadly, we cant use il2cpp hook for this because it has an overload

	IL2CPP::Callback::Initialize();
	IL2CPP::Callback::OnUpdate::Add(UpdateCallback);
}