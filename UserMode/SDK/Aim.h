
float GetBulletSpeed()
{
	switch (LocalPlayer.BasePlayer->ActiveWeapon()->GetItemID())
	{
	case 1796682209: //smg
		return 240.f;
	case 1588298435: //bolt
		return 656.25f;
	case -778367295: //l96
		return 1125.f;
	case 28201841: //m39
		return 469.f;
	case 1953903201: //nailgun
		return 50.f;
	case 649912614: //revolver
		return 300.f;
	case 818877484: //p250
		return 300.f;
	case -1367281941: //waterpipe, 250-green ammo, 100-other
		return 100.f;
	case -765183617: //double barrel, 250-green ammo, 100-other
		return 100.f;
	case -1812555177: //lr300
		return 375.f;
	case -852563019: //m92
		return 300.f;
	case -1123473824: //grenade launcher, shotgun - 250, other - 100
		return 100.f;
	case 442886268: //rocket launcher, unknown
		return 250.f;
	case -904863145: //semiautomatic rifle
		return 375.f;
	case -41440462: //spas12, 250-green ammo, 100-other
		return 100.f;
	case 1545779598: //ak47
		return 375.f;
	case 1443579727: //bow, 80-high speed arrow, 40 - fire arrow, 50 - normal
		return 50.f;
	case -75944661: //eoka, 250-green ammo, 100-other
		return 100.f;
	case 1318558775: //mp5a4
		return 240.f;
	case 795371088: //pomp shotgun, 250-green ammo, 100-other
		return 100.f;
	case 1965232394: //crossbow, 75 - normal, 120-high velocity, 60 - fire
		return 75.f;
	case -2069578888:
		return 488.f;
	case 1373971859: //python
		return 300.f;
	case -1758372725: //tompson
		return 300.f;
	default:
		return 250.f;
	}
}

float AimFov(BasePlayer* Entity)
{
	Vector2 ScreenPos;
	if (!LocalPlayer.WorldToScreen(Entity->GetBoneByID(), ScreenPos)) return 1000.f;
	return Math::Calc2D_Dist(Vector2(Value::floats::Screen::W / 2, Value::floats::Screen::H / 2), ScreenPos);
}

Vector3 Prediction(const Vector3& LP_Pos, BasePlayer* Player, BoneList Bone)
{
	Vector3 BonePos = Player->GetBoneByID();
	float Dist = Math::Calc3D_Dist(LP_Pos, BonePos);

	if (Dist > 0.001f) {
		float BulletTime = Dist / GetBulletSpeed();
		Vector3 vel = Player->GVelocity();
		Vector3 PredictVel = vel * BulletTime * 0.75f;
		BonePos += PredictVel; BonePos.y += (4.905f * BulletTime * BulletTime);
	} return BonePos;
}

void Normalize(float& Yaw, float& Pitch) {
	if (Pitch < -89) Pitch = -89;
	else if (Pitch > 89) Pitch = 89;
	if (Yaw < -360) Yaw += 360;
	else if (Yaw > 360) Yaw -= 360;
}

Vector2 ClampAngle(Vector2 qaAng)
{
	if (qaAng.x > 89.0f)
		qaAng.x = 89.0f;
	if (qaAng.x < -89.0f)
		qaAng.x = -89.0f;
	while (qaAng.y > 180.0f)
		qaAng.y -= 360.0f;
	while (qaAng.y < -180.0f)
		qaAng.y += 360.0f;
	return qaAng;
}

Vector2 ClampAngles(Vector2 vec)
{
	if (vec.x > 89.0f && vec.x <= 180.0f)
	{
		vec.x = 89.0f;
	}
	while (vec.x > 180.f)
	{
		vec.x -= 360.f;
	}
	while (vec.x < -89.0f)
	{
		vec.x = -89.0f;
	}
	while (vec.y > 180.f)
	{
		vec.y -= 360.f;
	}
	while (vec.y < -180.f)
	{
		vec.y += 360.f;
	}
	return vec;
}

void AimBotTarget(BasePlayer* player)
{
	Vector3 Local = LocalPlayer.BasePlayer->GetBoneByID();
	Vector3 PlayerPos = Prediction(Local, player, BoneList(neck));

	Vector2 current_angle = LocalPlayer.BasePlayer->GVA();
	Vector2 angle = Math::CalcAngle(Local, PlayerPos) - LocalPlayer.BasePlayer->GVA();
	Vector2 FinalAngle = LocalPlayer.BasePlayer->GVA() + angle;
	ClampAngles(FinalAngle);

	if (Value::bools::Aim::Smooth) {
		Vector2 delta = ClampAngle(FinalAngle - current_angle);
		ClampAngles(delta);
		FinalAngle.x = current_angle.x += delta.x / Value::floats::Aim::Smooth;
		FinalAngle.y = current_angle.y += delta.y / Value::floats::Aim::Smooth;
		FinalAngle = ClampAngles(FinalAngle);
	}

	Normalize(FinalAngle.y, FinalAngle.x);
	LocalPlayer.BasePlayer->SetVA(FinalAngle);

}

double ToRad(double degree)
{
	double pi = 3.14159265359;
	return (degree * (pi / 180));
}

Vector4 ToQuat(Vector3 Euler) {

	double heading = ToRad(Euler.x);
	double attitude = ToRad(Euler.y);
	double bank = ToRad(Euler.z);

	double c1 = cos(heading / 2);
	double s1 = sin(heading / 2);
	double c2 = cos(attitude / 2);
	double s2 = sin(attitude / 2);
	double c3 = cos(bank / 2);
	double s3 = sin(bank / 2);
	double c1c2 = c1 * c2;
	double s1s2 = s1 * s2;
	Vector4 Quat;
	Quat.w = c1c2 * c3 - s1s2 * s3;
	Quat.x = c1c2 * s3 + s1s2 * c3;
	Quat.y = s1 * c2 * c3 + c1 * s2 * s3;
	Quat.z = c1 * s2 * c3 - s1 * c2 * s3;
	Vector4 Quat2;
	Quat2 = { Quat.y, Quat.z, (Quat.x * -1), Quat.w };
	return Quat2;
}

void Aim(BasePlayer* player)
{
	if (Value::bools::Aim::Enable)
	{
		if (GetAsyncKeyState(0x58)) {
			//std::cout << "Target " << player->SteamID() << std::endl;
			BaseProjectile* ActWeapon = LocalPlayer.BasePlayer->ActiveWeapon();
			AimBotTarget(player);
		}
	}

	if (Value::bools::Aim::PSilent) {
		auto TargetBonePos = Prediction(LocalPlayer.BasePlayer->GBoneByID2(head), player, penis);

		Vector2 TargetAngles = Math::CalcAngle(LocalPlayer.BasePlayer->GBoneByID2(head), TargetBonePos);

		Vector2 Angles; Angles.x = TargetAngles.x, Angles.y = TargetAngles.y;

		UINT64 PlayerEyes = safe_read((uintptr_t)LocalPlayer.BasePlayer + oPlayerEyes, UINT64);
		Vector4 QuatAngles = ToQuat({ Angles.x, Angles.y, 0.0f });
		safe_write(PlayerEyes + 0x44, QuatAngles, Vector4);
		//LocalPlayer.BasePlayer->SetVA(FinalAngle);
	}
}