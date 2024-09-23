static bool menuOpen = true;

struct RaycastHit
{
	il2cppVector3 m_Point;
	il2cppVector3 m_Normal;
	unsigned int m_FaceID;
	float m_Distance;
	il2cppVector2 m_UV;
	int m_Collider;
};

bool is_health_mine(Unity::CObject* health) {
	return health->GetMemberValue<Unity::CObject*>("photonView")->GetMemberValue<bool>("isMine") == true;
}

bool is_health_mine_voidp(void* health) {
	return GetField<bool>(GetField<void*>(health, IL2CPP::Class::Utils::GetFieldOffset("Health", "photonView")), IL2CPP::Class::Utils::GetFieldOffset("NetworkEntity", "isMine")) == true;
}

Unity::CCamera* get_player_camera() {
	return Unity::Camera::GetMain();
}