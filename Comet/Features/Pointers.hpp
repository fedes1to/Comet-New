#define CreateIl2cppString(str) IL2CPP::String::New(str) // porting should be easier this way

Pointer<Unity::System_String* ()> Application$$Version;
Pointer<Unity::System_String* (void*)> SerializeObject;
Pointer<Unity::CObject* (Unity::CObject*)> Instantiate;
Pointer<Unity::CObject* (Unity::System_String*)> Resources$$Load;
Pointer<Unity::il2cppArray<Unity::CComponent*>* (void*)> Resources$$FindObjectsOfTypeAll;
Pointer<Unity::il2cppArray<uint8_t>* (void*)> ByteArray$$GetBytes;
Pointer<void (void*)> ByteArray$$Uncompress;
Pointer<void* (void*)> SFSObject$$ToBinary;
Pointer<void* (void*)> BaseRequest$$Message;
Pointer<void* (void*)> Message$$Content;
Pointer<bool (void*)> NewWeapon$$fire;
Pointer<bool (il2cppVector3, il2cppVector3, RaycastHit*, float, int)> Physics$$Raycast;
Pointer<void* (void*)> Component$$get_transform;
Pointer<void* (void*)> Component$$get_gameObject;
Pointer<Unity::System_String* (void*)> GameObject$$get_tag;
Pointer<il2cppVector3 (void*)> Transform$$get_position;
Pointer<il2cppVector3 (void*, il2cppVector3)> Transform$$TransformDirection;
Pointer<il2cppVector3 (void*, il2cppVector3)> Camera$$WorldToScreenPoint;
Pointer<void (void*)> OfflineModeMenu$$open;
Pointer<bool (void*)> GameShell$$isTeamMode;
Pointer<void* (void*, Unity::il2cppObject*)> GameObject$$GetComponentInParent;
Pointer<void* (RaycastHit)> RaycastHit$$get_collider;
Pointer<int (void*, Unity::System_String*)> SettingsManager$$getSettingKeyBind;

void initPointers() {
	// declare pointers here
	Application$$Version = IL2CPP_METHOD("UnityEngine.Application", "get_version");
	SerializeObject = IL2CPP_METHOD("PlayFab.Json.PlayFabSimpleJson", "SerializeObject");
	Instantiate = OFFSET("0x76F2480");
	Resources$$Load = OFFSET("0x76EA3F0");
	SFSObject$$ToBinary = IL2CPP_METHOD("Sfs2X.Entities.Data.SFSObject", "ToBinary");
	BaseRequest$$Message = IL2CPP_METHOD("Sfs2X.Requests.BaseRequest", "get_Message");
	Message$$Content = IL2CPP_METHOD("Sfs2X.Bitswarm.Message", "get_Content");
	ByteArray$$GetBytes = IL2CPP_METHOD("Sfs2X.Util.ByteArray", "get_Bytes");
	ByteArray$$Uncompress = IL2CPP_METHOD("Sfs2X.Util.ByteArray", "Uncompress");

	Resources$$FindObjectsOfTypeAll = IL2CPP_METHOD("UnityEngine.Resources", "FindObjectsOfTypeAll");
	NewWeapon$$fire = IL2CPP_METHOD("NewWeapon", "fire");
	Component$$get_transform = IL2CPP_METHOD("UnityEngine.Component", "get_transform");
	Component$$get_gameObject = IL2CPP_METHOD("UnityEngine.Component", "get_gameObject");
	Transform$$get_position = IL2CPP_METHOD("UnityEngine.Transform", "get_position");
	Transform$$TransformDirection = IL2CPP_METHOD_ARGS("UnityEngine.Transform", "TransformDirection", 1);
	Camera$$WorldToScreenPoint = IL2CPP_METHOD_ARGS("UnityEngine.Camera", "WorldToScreenPoint", 1);
	OfflineModeMenu$$open = IL2CPP_METHOD("OfflineModeMenu", "open");
	Physics$$Raycast = OFFSET("0x7773B70"); // since it has like a trillion other methods with different arguments, offset is NECESSARY for this :(
	GameShell$$isTeamMode = IL2CPP_METHOD("GameShell", "isTeamMode");
	GameObject$$GetComponentInParent = IL2CPP_METHOD_ARGS("UnityEngine.GameObject", "GetComponentInParent", 1);
	GameObject$$get_tag = IL2CPP_METHOD_ARGS("UnityEngine.GameObject", "get_tag");
	RaycastHit$$get_collider = IL2CPP_METHOD("UnityEngine.RaycastHit", "get_collider");
	SettingsManager$$getSettingKeyBind = IL2CPP_METHOD("SettingsManager", "getSettingKeyBind");
}