#pragma once

void Misc(UINT64 TodCycle)
{
	if (Value::bools::Visuals::World::AlwaysDay)
		safe_write(TodCycle + 0x10, Value::floats::Visuals::World::Time, float);

	if (Value::bools::Player::PlayerWalk::Spiderman)
		LocalPlayer.BasePlayer->SpiderMan();

	if (Value::bools::Player::PlayerWalk::FakeAdmin)
		LocalPlayer.BasePlayer->FakeAdmin();


	if (Value::floats::Player::LongNeck && GetAsyncKeyState(0x59)) {
		LocalPlayer.BasePlayer->LongNeck();
	}

	if (Value::bools::Misc::FlyHack)
		LocalPlayer.BasePlayer->FlyHack();

	if (Value::bools::Misc::SpeedHack)
		LocalPlayer.BasePlayer->SpeedHack();

	if (Value::bools::Misc::WalkOnWater)
		LocalPlayer.BasePlayer->WalkWater();

	if (Value::bools::Misc::killhack)
		LocalPlayer.BasePlayer->KillHack();

	if (Value::bools::Misc::FixCamera)
		LocalPlayer.BasePlayer->FixCamera();

	if (Value::bools::Player::PlayerWalk::ChangeGravity)
		LocalPlayer.BasePlayer->GravituMod();

	if (Value::bools::Player::PlayerWalk::InfinityJump)
		LocalPlayer.BasePlayer->InfinityJump();

	if (Value::bools::Player::CustomFov)
		LocalPlayer.BasePlayer->SetFov();

	if (Value::bools::Player::Zoom)
		LocalPlayer.BasePlayer->Zoom();

	if (Value::bools::Visuals::World::NightModeup)
		LocalPlayer.BasePlayer->todsky();

	if (Value::bools::Visuals::World::FixAmbient)
		LocalPlayer.BasePlayer->UpdateAmbient();

}