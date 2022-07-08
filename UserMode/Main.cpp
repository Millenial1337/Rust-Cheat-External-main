#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>  
#include "Process/Process.h"
#include <Windows.h>
#include <string>
#include <cassert>
#include <emmintrin.h>
#include <tlhelp32.h>
#include <winternl.h>
#include <signal.h>

#include "Menu.h"
#include "skCrypt.h"
#include "Driver/driver.h"


typedef struct _UncStr
{
	char stub[0x10];
	int len;
	wchar_t str;
} *pUncStr;

using namespace std;


uint64_t game_assembly, unity_player;
int pid;

long long firstentry = 0;
UINT64 TodCycle = 0;
c_menu_framework* menu_framework = new c_menu_framework;

inline HANDLE DriverHandle;
inline HWND hwnd = NULL;
inline DWORD processID;

inline int wLeft, wTop;

#define CHECK_VALID( _v ) 0
#define Assert( _exp ) ((void)0)

#define FastSqrt(x)			(sqrt)(x)

#define M_PI 3.14159265358979323846264338327950288419716939937510

#include <msxml.h>    
#include <atomic>
#include <mutex>
#include <Windows.h>
#include <TlHelp32.h>
#include <cstdint>
#include <vector>
#include <random>
#include <memoryapi.h>
#include <string>
#include <thread>
#include <chrono>
#include <iostream>

#pragma once
#include <Windows.h>


HWND Wnd = NULL;
RECT GameRect = { NULL };
HWND GameWnd = NULL;
IDirect3D9Ex* pObject = NULL;
IDirect3DDevice9Ex* pDevice = NULL;
D3DPRESENT_PARAMETERS pParams = { NULL };

DWORD ScreenCenterX;
DWORD ScreenCenterY;
int Width = GetSystemMetrics(SM_CXSCREEN);
int Height = GetSystemMetrics(SM_CYSCREEN);
MSG Message = { NULL };
bool ShowMenu = false;
bool Initialised = false;

void ClearD3D()
{
	if (pDevice != NULL)
	{
		pDevice->EndScene();
		pDevice->Release();
	}
	if (pObject != NULL)
	{
		pObject->Release();
	}
}



constexpr DWORD init_code = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x775, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
constexpr DWORD read_code = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x776, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
constexpr DWORD write_code = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x777, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);

class driver_manager {
	HANDLE m_driver_handle = nullptr;

	struct info_t {
		UINT64 target_pid = 0;
		UINT64 target_address = 0x0;
		UINT64 buffer_address = 0x0;
		UINT64 size = 0;
		UINT64 return_size = 0;
		UINT64 GA = 0;
		UINT64 UP = 0;
	};

public:
	driver_manager(const char* driver_name, DWORD target_process_id) {
		m_driver_handle = CreateFileA(driver_name, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		attach_to_process(target_process_id);
	}

	void attach_to_process(DWORD process_id) {
		info_t io_info;

		io_info.target_pid = process_id;

		DeviceIoControl(m_driver_handle, init_code, &io_info, sizeof(io_info), &io_info, sizeof(io_info), nullptr, nullptr);
		game_assembly = io_info.GA;
		unity_player = io_info.UP;
		Sleep(10000);
	}

	template<typename T> T RPM(const UINT64 address) {
		info_t io_info;
		T read_data;

		io_info.target_address = address;
		io_info.buffer_address = (UINT64)&read_data;
		io_info.size = sizeof(T);

		DeviceIoControl(m_driver_handle, read_code, &io_info, sizeof(io_info), &io_info, sizeof(io_info), nullptr, nullptr);
		if (!io_info.buffer_address)
		return read_data;
	}

	template<typename T> bool WPM(const UINT64 address, const T buffer) {
		info_t io_info;

		io_info.target_address = address;
		io_info.buffer_address = (UINT64)&buffer;
		io_info.size = sizeof(T);

		DeviceIoControl(m_driver_handle, write_code, &io_info, sizeof(io_info), &io_info, sizeof(io_info), nullptr, nullptr);
		return io_info.return_size == sizeof(T);
	}
};

driver_manager* gDriver;



#define safe_read(Addr, Type) gDriver->RPM<Type>(Addr)
#define safe_write(Addr, Data, Type) gDriver->WPM<Type>(Addr, Data)


int length(uintptr_t addr) { return safe_read(addr + 0x10, int); }

std::string readstring(uintptr_t addr) {
	try {
		static char buff[128] = { 0 };
		buff[length(addr)] = '\0';

		for (int i = 0; i < length(addr); ++i) {
			if (buff[i] < 128) {
				buff[i] = safe_read(addr + 0x14 + (i * 2), char);
			}
			else {
				buff[i] = '?';
				if (buff[i] >= 0xD800 && buff[i] <= 0xD8FF)
					i++;
			}
		}
		return std::string(&buff[0], &buff[length(addr)]);
	}
	catch (const std::exception& exc) {}
	return "Error";
}
struct monostr
{
	char buffer[128];
};

std::string readchar(uintptr_t addr) {
	std::string str = safe_read(addr, monostr).buffer;
	if (!str.empty())
		return str;
	else
		return NULL;
}

#include "Of.h"

#include "Main.h"
#include "Overlay.h"



bool CreateConsole = true;

#include "Value.h"
#include "SDK/Math.h"
#include "SDK/BaseProjectile.h"
#include "SDK/BasePlayer.h"
#include "SDK/Misc.h"
#include "SDK/Aim.h"


BasePlayer* AimEntity = nullptr;
BasePlayer localclass;
BasePlayer currentent;
BasePlayer currentplayer;
BaseProjectile wep;
//bool OnServer;

#include <mutex>
inline std::mutex          entity_mutex;
inline std::vector<BasePlayer*> otherplayers;
inline std::vector<Vector3> Stash;
inline std::vector<Vector3> hemp;
inline std::vector<Vector3> backpack;
inline std::vector<Vector3> corpse;
inline std::vector<Vector3> vehicles;
inline std::vector<Vector3> DroppedItem;
inline std::vector<Vector3> Airdrop;
inline std::vector<Vector3> patrol_heli;
inline std::vector<Vector3> hackable_crate;
inline std::vector<Vector3> high_tier_crates;
inline std::vector<Vector3> low_tier_crates;
inline std::vector<Vector3> SulfurNodes;
inline std::vector<Vector3> StoneNodes;
inline std::vector<Vector3> MetalNodes;
void WeaponFix(BaseProjectile* weapon)
{
	int ItemID = 0;
	if (weapon)
		ItemID = weapon->GetItemID();
	if (!ItemID) return;

	for (DWORD64 val : semiautomatic) {
		if (ItemID == val) {
			weapon->Recoil();
			weapon->Spread();
			weapon->SAutomatic();
			weapon->FBullet();
			weapon->rapidFire();
			weapon->fastSwitch();
			weapon->instantCompound();

			return;
		}
	}
	for (DWORD64 val : sniper) {
		if (ItemID == val) {
			weapon->Recoil();
			weapon->Spread();
			weapon->FBullet();
			weapon->rapidFire();
			weapon->fastSwitch();
			weapon->instantCompound();
			weapon->SuperBow();

			return;
		}
	}
	for (DWORD64 val : automatic) {
		if (ItemID == val) {
			weapon->Recoil();
			weapon->Spread();
			weapon->FBullet();
			weapon->rapidFire();
			weapon->fastSwitch();
			weapon->instantCompound();
			return;
		}
	}

	if (ItemID == -75944661)
	{
		weapon->SuperEoka();
		weapon->fastSwitch();
		return;
	}

	for (DWORD64 val : meele) {
		if (ItemID == val) {
			weapon->LongHand();
			return;
		}
	}
}




bool cunter = false;
void InitPlayer()
{
	long long i = 0;

	const auto camera_manager_offset = safe_read(unity_player + 0x1762E80, UINT64);
	const auto camera_manager = safe_read(camera_manager_offset, UINT64);
	const auto camera = safe_read(camera_manager, UINT64);
	const auto camera_object = safe_read(camera + 0x30, UINT64);
	const auto object_class = safe_read(camera_object + 0x30, UINT64);
	const auto entity = safe_read(object_class + 0x18, UINT64);
	LocalPlayer.pViewMatrix = (Matrix4x4*)(entity + 0x2E4);
	cunter = true;
	return;
}




void Draw() {
	char fpsinfo[64];
	sprintf(fpsinfo, skCrypt("Winhack.fun"));
	
	if (Value::bools::Aim::Fov) {

		DrawCircle(Value::floats::Screen::W / 2, Value::floats::Screen::H / 2, Value::floats::Aim::Fov, 1, 255, 255, 255, 255, false);
	}
	
}
#include <comdef.h>
Vector2 Penis;




void ESP(BasePlayer* BP, BasePlayer* LP) {
	if (Value::bools::Visuals::ESP::Enable) {
		Vector2 tempFeetR, tempFeetL;
		if (LocalPlayer.WorldToScreen(BP->GBoneByID2(r_foot), tempFeetR) && LocalPlayer.WorldToScreen(BP->GBoneByID2(penis), Penis) && LocalPlayer.WorldToScreen(BP->GBoneByID2(l_foot), tempFeetL)) {
			Vector2 tempHead;
			if (LocalPlayer.WorldToScreen(BP->GBoneByID2(jaw) + Vector3(0.f, 0.16f, 0.f), tempHead))
			{
				Vector2 tempFeet = (tempFeetR + tempFeetL) / 2.f;
				float Entity_h = tempHead.y - tempFeet.y;
				float w = Entity_h / 4;
				float Entity_x = tempFeet.x - w;
				float Entity_y = tempFeet.y;
				float Entity_w = Entity_h / 2;

				bool PlayerWounded = BP->Flags(64);
				bool PlayerSleeping = BP->Flags(16);

				if (PlayerSleeping && Value::bools::Visuals::ESP::IgnoreSleeper)
					return;

				static float screenW = GetSystemMetrics(SM_CXSCREEN);
				static float screenH = GetSystemMetrics(SM_CYSCREEN);

				if (Value::bools::Visuals::ESP::Health) {
					char Health[64];
					sprintf(Health, skCrypt("%0.f HP"), BP->Health());
					DrawString(Health, 12, tempFeet.x, (tempFeet.y + 25), 1.f, 1.f, 1.f);
				}
				if (Value::bools::Visuals::ESP::Box && !PlayerSleeping && !PlayerWounded) {
					DrawBox(Entity_x + 1, Entity_y + 1, Entity_w - 2, Entity_h - 2, 1.f, 1.f, 1.f, 1.f, 1.f, false);
				}
				if (Value::bools::Visuals::ESP::Distance) {
					char Distance[64];
					sprintf(Distance, skCrypt("%d M"), (int)Math::Calc3D_Dist(LP->GBoneByID2(head), BP->GBoneByID2(head)));
					DrawString(Distance, 12, tempFeet.x, (tempFeet.y + 4), 1.f, 1.f, 1.f);
				}
				if (Value::bools::Visuals::ESP::Name) {
					DrawString(BP->GetNamecChars().c_str(), 14, tempFeet.x + 1, (tempFeet.y + 15), 1.f, 1.f, 1.f);
				}
				if (Value::bools::Visuals::ESP::Weapon) {
					DrawString(BP->GetActiveWeaponcChars().c_str(), 12, tempFeet.x, (tempFeet.y + 2), 1.f, 1.f, 1.f);
				}
			}
		}
	}
}
float W = 200.f, H = 140;;


float FOV = 1000000.f;
int EntityCount;
int RenderedEntityCount;
int RenderedPlayerCount;
void entity_esp_thread() {
	
	RenderedEntityCount = NULL; RenderedEntityCount = NULL;

	
		if (Value::bools::Visuals::World::Items::Stash) {
			for (Vector3 Pos : Stash) {
				Vector2 pos;
				if (LocalPlayer.WorldToScreen(Pos, pos)) {
					int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GBoneByID2(head), Pos);
					char text[0x100];
					sprintf(text, skCrypt("Stash [%d m]"), distation);
					if (distation <= Value::floats::Visuals::World::LimitDistance) {
						RenderedEntityCount++;
						DrawString(text, 12, pos.x, pos.y, 1.f, 1.f, 1.f);
					}
				}
			}
		}
		if (Value::bools::Visuals::World::Items::Hemp) {
			for (Vector3 Pos : hemp) {
				Vector2 pos;
				if (LocalPlayer.WorldToScreen(Pos, pos)) {
					int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GBoneByID2(head), Pos);
					char text[0x100];
					sprintf(text, skCrypt("Hemp [%d m]"), distation);
					if (distation <= Value::floats::Visuals::World::LimitDistance) {
						RenderedEntityCount++;
						DrawString(text, 12, pos.x, pos.y, 1.f, 1.f, 1.f);
					}
				}
			}
		}
		if (Value::bools::Visuals::World::Items::AirDrop) {
			for (Vector3 Pos : Airdrop) {
				Vector2 pos;
				if (LocalPlayer.WorldToScreen(Pos, pos)) {
					int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GBoneByID2(head), Pos);
					char text[0x100];
					sprintf(text, skCrypt("AirDrop [%d m]"), distation);
					if (distation <= Value::floats::Visuals::World::LimitDistance2) {
						RenderedEntityCount++;
						DrawString(text, 12, pos.x, pos.y, 1.f, 1.f, 1.f);
					}
				}
			}
		}
		if (Value::bools::Visuals::World::Items::CH47) {
			for (Vector3 Pos : hackable_crate) {
				Vector2 pos;
				if (LocalPlayer.WorldToScreen(Pos, pos)) {
					int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GBoneByID2(head), Pos);
					char text[0x100];
					sprintf(text, skCrypt("CH47 [%d m]"), distation);
					if (distation <= Value::floats::Visuals::World::LimitDistance2) {
						RenderedEntityCount++;
						DrawString(text, 12, pos.x, pos.y, 1.f, 1.f, 1.f);
					}
				}
			}
		}
		if (Value::bools::Visuals::World::Items::Minicopter) {
			for (Vector3 Pos : vehicles) {
				Vector2 pos;
				if (LocalPlayer.WorldToScreen(Pos, pos)) {
					int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GBoneByID2(head), Pos);
					char text[0x100];
					if (distation <= Value::floats::Visuals::World::LimitDistance2) {
						RenderedEntityCount++;
						sprintf(text, skCrypt("Minicopter [%d m]"), distation);
						DrawString(text, 12, pos.x, pos.y, 1.f, 1.f, 1.f);
					}
				}
			}
		}
		if (Value::bools::Visuals::World::Items::Patrol) {
			for (Vector3 Pos : patrol_heli) {
				Vector2 pos;
				if (LocalPlayer.WorldToScreen(Pos, pos)) {
					int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GBoneByID2(head), Pos);
					char text[0x100];
					if (distation <= Value::floats::Visuals::World::LimitDistance2) {
						RenderedEntityCount++;
						sprintf(text, skCrypt("Patrol [%d m]"), distation);
						DrawString(text, 12, pos.x, pos.y, 1.f, 1.f, 1.f);
					}
				}
			}
		}
		if (Value::bools::Visuals::World::Items::Ore::Stone) {
			for (Vector3 Pos : StoneNodes) {
				Vector2 pos;
				if (LocalPlayer.WorldToScreen(Pos, pos)) {
					int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GBoneByID2(head), Pos);
					char text[0x100];
					sprintf(text, skCrypt("Stone [%d m]"), distation);
					if (distation <= Value::floats::Visuals::World::LimitDistance) {
						RenderedEntityCount++;
						DrawString(text, 12, pos.x, pos.y, 1.f, 1.f, 1.f);
					}
				}
			}
		}
		if (Value::bools::Visuals::World::Items::Ore::Iron) {
			for (Vector3 Pos : MetalNodes) {
				Vector2 pos;
				if (LocalPlayer.WorldToScreen(Pos, pos)) {
					int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GBoneByID2(head), Pos);
					char text[0x100];
					sprintf(text, skCrypt("Metal [%d m]"), distation);
					if (distation <= Value::floats::Visuals::World::LimitDistance) {
						RenderedEntityCount++;
						DrawString(text, 12, pos.x, pos.y, 1.f, 1.f, 1.f);
					}
				}
			}
		}
		if (Value::bools::Visuals::World::Items::Ore::Sulfur) {
			for (Vector3 Pos : SulfurNodes) {
				Vector2 pos;
				if (LocalPlayer.WorldToScreen(Pos, pos)) {
					int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GBoneByID2(head), Pos);
					char text[0x100];
					sprintf(text, skCrypt("Sulfur [%d m]"), distation);
					if (distation <= Value::floats::Visuals::World::LimitDistance) {
						RenderedEntityCount++;
						DrawString(text, 12, pos.x, pos.y, 1.f, 1.f, 1.f);
					}
				}
			}
		}

		if (Value::bools::Visuals::ESP::Corpse) {
			for (Vector3 Pos : corpse) {
				Vector2 pos;
				if (LocalPlayer.WorldToScreen(Pos, pos)) {
					int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GBoneByID2(head), Pos);
					char text[0x100];
					sprintf(text, skCrypt("Corpse [%d m]"), distation);
					if (distation <= Value::floats::Visuals::World::LimitDistance) {
						RenderedEntityCount++;
						DrawString(text, 12, pos.x, pos.y, 1.f, 1.f, 1.f);
					}
				}
			}
		}


		if (Value::bools::Visuals::ESP::Backpack) {
			for (Vector3 Pos : backpack) {
				Vector2 pos;
				if (LocalPlayer.WorldToScreen(Pos, pos)) {
					int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GBoneByID2(head), Pos);
					char text[0x100];
					sprintf(text, skCrypt("Backpack [%d m]"), distation);
					if (distation <= Value::floats::Visuals::World::LimitDistance) {
						RenderedEntityCount++;
						DrawString(text, 12, pos.x, pos.y, 1.f, 1.f, 1.f);
					}
				}
			}
		}
		if (Value::bools::Visuals::ESP::Enable) {
			for (BasePlayer* Player : otherplayers) {
				if (!Player->IsValid())
					continue;
				ESP(Player, LocalPlayer.BasePlayer);
			

				if (Value::bools::Aim::IgnoreSleepers && Player->Flags(16))
					continue;
				if (Player->IsVisible() && (AimFov(Player) < Value::floats::Aim::Fov))
				{
					AimEntity = Player;
					Aim(AimEntity);
				}
			}
		}
}




#include <vector>
#include <string>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string.h>

std::vector<BasePlayer*> local_players;
std::vector<Vector3> local_Stash;
std::vector<Vector3> local_hemp;
std::vector<Vector3> local_corpse;
std::vector<Vector3> local_backpack;
std::vector<Vector3> local_vehicles;
std::vector<Vector3> local_Airdrop;
std::vector<Vector3> local_patrol_heli;
std::vector<Vector3> local_hackable_crate;
std::vector<Vector3> local_high_tier_crates;
std::vector<Vector3> local_low_tier_crates;
std::vector<Vector3> local_DroppedItem;
std::vector<Vector3> local_SulfurNodes;
std::vector<Vector3> local_StoneNodes;
std::vector<Vector3> local_MetalNodes;



DWORD WINAPI EntityT1(LPVOID lpParameter) {
	while (true) {

		auto oBaseEntity = gDriver->RPM<uintptr_t>(gDriver->RPM<uintptr_t>(game_assembly + ooBaseEntity_c) + 0xB8);//BaseEntity_c*

		auto unk1 = gDriver->RPM<uintptr_t>(oBaseEntity + 0x10);

		auto client_entities = gDriver->RPM<uintptr_t>(gDriver->RPM<uintptr_t>(unk1 + 0x10) + 0x28);

		auto objectList = gDriver->RPM<uintptr_t>(client_entities + 0x18);

		auto objectListSize = gDriver->RPM<uint32_t>(client_entities + 0x10);


		for (int i = 0; i <= objectListSize; i++)
		{
			DWORD64 Entity = safe_read(objectList + 0x20 + (i * 0x8), DWORD64);

			if (Entity <= 100000) continue;
			DWORD64 Object = safe_read(Entity + 0x10, DWORD64); //BaseObject
			if (Object <= 100000) continue;
			DWORD64 ObjectClass = safe_read(Object + 0x30, DWORD64); //Object
			//
			WORD tag = safe_read(ObjectClass + 0x54, WORD);
			//
			if (ObjectClass <= 100000) continue;
			uintptr_t name = safe_read(ObjectClass + 0x60, uintptr_t);
			if (!name) continue;
			auto buff = readchar(name);
			if (buff.find(skCrypt("Local")) != std::string::npos) {
				auto Player = (BasePlayer*)safe_read(Object + 0x28, DWORD64);
				if (!safe_read((uintptr_t)Player + 0x4C0, DWORD64)) continue; // public PlayerModel playerModel;??? 0x4B0
				LocalPlayer.BasePlayer = Player;
			}

			else

				if (strstr(buff.c_str(), skCrypt("small_stash_deployed.prefab"))) {
					auto flag = safe_read(Entity + 0x130, uintptr_t);//private float traveledDistance; // 0x130
					if (flag != 2048)
						continue;
					DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
					DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
					DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
					Vector3 pos = safe_read(Vec + 0x90, Vector3);

					local_Stash.push_back(pos);
				}
				else
					if (strstr(buff.c_str(), skCrypt("hemp-collectable.prefab"))) {
						DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
						DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
						DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
						Vector3 pos = safe_read(Vec + 0x90, Vector3);

						local_hemp.push_back(pos);
					}
					else
						if (strstr(buff.c_str(), skCrypt("supply_drop.prefab"))) {
							DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
							DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
							DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
							Vector3 pos = safe_read(Vec + 0x90, Vector3);

							local_Airdrop.push_back(pos);
						}
						else
							if (strstr(buff.c_str(), skCrypt("codelockedhackablecrate.prefab"))) {
								DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
								DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
								DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
								Vector3 pos = safe_read(Vec + 0x90, Vector3);

								local_hackable_crate.push_back(pos);
							}
							else
								if (strstr(buff.c_str(), skCrypt("player_corpse.prefab"))) {
									DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
									DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
									DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
									Vector3 pos = safe_read(Vec + 0x90, Vector3);

									local_corpse.push_back(pos);
								}
								else
									if (strstr(buff.c_str(), skCrypt("item_drop_backpack.prefab"))) {
										DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
										DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
										DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
										Vector3 pos = safe_read(Vec + 0x90, Vector3);

										local_backpack.push_back(pos);
									}
									else
										if (strstr(buff.c_str(), skCrypt("minicopter.entity.prefab"))) {
											DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
											DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
											DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
											Vector3 pos = safe_read(Vec + 0x90, Vector3);

											local_vehicles.push_back(pos);
										}
										else
											if (strstr(buff.c_str(), skCrypt("patrolhelicopter.prefab"))) {
												DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
												DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
												DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
												Vector3 pos = safe_read(Vec + 0x90, Vector3);

												local_patrol_heli.push_back(pos);
											}
											else
												if (strstr(buff.c_str(), skCrypt("stone-ore.prefab"))) {
													DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
													DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
													DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
													Vector3 pos = safe_read(Vec + 0x90, Vector3);

													local_StoneNodes.push_back(pos);
												}
												else
													if (strstr(buff.c_str(), skCrypt("metal-ore.prefab"))) {
														DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
														DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
														DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
														Vector3 pos = safe_read(Vec + 0x90, Vector3);

														local_MetalNodes.push_back(pos);
													}
													else
														if (strstr(buff.c_str(), skCrypt("sulfur-ore.prefab"))) {
															DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
															DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
															DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
															Vector3 pos = safe_read(Vec + 0x90, Vector3);

															local_SulfurNodes.push_back(pos);
														}
		}

		//InitPlayer();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		std::lock_guard<std::mutex>lk(entity_mutex);
		//otherplayers = std::move(local_players);
		Stash = std::move(local_Stash);
		corpse = std::move(local_corpse);
		vehicles = std::move(local_vehicles);
		DroppedItem = std::move(local_DroppedItem);
		//Animal = std::move(local_Animal);
		SulfurNodes = std::move(local_SulfurNodes);
		StoneNodes = std::move(local_StoneNodes);
		MetalNodes = std::move(local_MetalNodes);

		Airdrop = std::move(local_Airdrop);
		patrol_heli = std::move(local_patrol_heli);
		//tool_cupboard = std::move(local_tool_cupboard);
		hackable_crate = std::move(local_hackable_crate);
		hemp = std::move(local_hemp);
		backpack = std::move(local_backpack);

		//food = std::move(local_food);
		//cargo_ship = std::move(local_cargo_ship);
		high_tier_crates = std::move(local_high_tier_crates);
		low_tier_crates = std::move(local_low_tier_crates);


	}
}





DWORD WINAPI EntityT(LPVOID lpParameter) {
	while (true) {

		auto val = gDriver->RPM<uintptr_t>(gDriver->RPM<uintptr_t>(gDriver->RPM<uintptr_t>(game_assembly + ooBaseEntity_c) + 0xB8) + 0x10);
		UINT64 EntityRealm = gDriver->RPM<DWORD64>(val + 0xB8);
		auto ClientEntities = gDriver->RPM<uintptr_t>(gDriver->RPM<uintptr_t>(val + 0x10) + 0x28);
		EntityCount = safe_read(ClientEntities + 0x10, int);
		if (!EntityCount)
			continue;
		auto EntityBuffer = safe_read(ClientEntities + 0x18, uintptr_t);

		if (!EntityBuffer)
			continue;

		for (int i = 0; i < EntityCount; i++)
		{
			DWORD64 Entity = safe_read(EntityBuffer + 0x20 + (i * 0x8), DWORD64);
			if (Entity <= 100000) continue;
			DWORD64 Object = safe_read(Entity + 0x10, DWORD64); //BaseObject
			if (Object <= 100000) continue;
			DWORD64 ObjectClass = safe_read(Object + 0x30, DWORD64); //Object

			WORD tag = safe_read(ObjectClass + 0x54, WORD);

			if (ObjectClass <= 100000) continue;
			uintptr_t name = safe_read(ObjectClass + 0x60, uintptr_t);
			if (!name) continue;
			auto buff = readchar(name);


			if (buff.find(skCrypt("player.prefab")) != std::string::npos || buff.find(skCrypt("scientist")) != std::string::npos/* && (!strstr(buff.c_str(), "prop") && !strstr(buff.c_str(), "corpse"))*/)
			{
				BasePlayer* Player = (BasePlayer*)safe_read(Object + 0x28, DWORD64); //public ulong playerID;
				if (!safe_read((uintptr_t)Player + oPlayerModel, DWORD64)) continue;// 0x4A8 public PlayerModel playerModel;
				if (!Player->IsValid()) continue;
				local_players.push_back(Player);
			}


		}

		InitPlayer();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		std::lock_guard<std::mutex>lk(entity_mutex);
		otherplayers = std::move(local_players);
	}
}

#include <TlHelp32.h>


void Loop()
{
	
		bool valid = LocalPlayer.BasePlayer->IsValid(true);
		if (LocalPlayer.BasePlayer && valid) {
			std::lock_guard<std::mutex>lk(entity_mutex);
			entity_esp_thread();
			Misc(TodCycle);

			int WeaponId = 0;
			int last = -1;
			auto* active = LocalPlayer.BasePlayer->ActiveWeapon();
			if (active) {
				if (active->UID() != 0)
				{
					if (WeaponId != active->GetItemID())
					{
						WeaponId = active->GetItemID();
					}
					last = active->UID();
					if (last)
					{
						WeaponFix(active);
					}
				}
				else if (!last)
					last = active->UID();
			}
			if (!(AimEntity->Dead()) && Value::bools::Aim::TargetLine) {
				Vector2 ScreenPos;
				if (LocalPlayer.WorldToScreen(AimEntity->GBoneByID2(spine1), ScreenPos))
				DrawLine(Value::floats::Screen::W / 2, Value::floats::Screen::H / 2, Penis.x, Penis.y, 1.f, 1.f, 1.f, 1.f, 1);
			}
		}
		else
			if (!LocalPlayer.BasePlayer)
				InitPlayer();
	
}

HANDLE memory_read = NULL, memory_write = NULL, memory_esp_write = NULL;
bool Checccck = true;



inline void drawLoop(int width, int height)
{
	menu_framework->do_menu_controls();
	Loop();

}

inline void OverlaySetup()
{
	DirectOverlaySetup(drawLoop, FindWindow(NULL, "Rust"));
}

int main() {

	

	
	if (CreateConsole == false)
	{
		ShowWindow(::GetConsoleWindow(), SW_HIDE);
	}
	else
	{
		ShowWindow(::GetConsoleWindow(), SW_SHOW);
	}

	if (Checccck == true)
	{
		pid = GetProcessIdByName(skCrypt("RustClient.exe"));
		gDriver = new driver_manager(skCrypt("\\\\.\\AUzwL9x61HxK"), pid);
		cout << "p1d: \t" << pid << endl;
		if (!gDriver) {
			std::cout << "p1d failed" << std::endl;
			Sleep(10000);
			return 0;
		}
		cout<<"GameAssembly.dll : \t"<< game_assembly << endl;
		cout <<"UnityPlayer.dll : \t" << unity_player << endl;
		if (game_assembly == NULL || unity_player == NULL)
		{
			cout << "Eror: Driver issue" << endl;
		}
		std::thread(OverlaySetup).detach();
		InitPlayer();
		Value::floats::Screen::W = GetSystemMetrics(SM_CXSCREEN);  
		Value::floats::Screen::H = GetSystemMetrics(SM_CYSCREEN);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)EntityT, 0, 0, 0);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)EntityT1, 0, 0, 0);

		while (true) { // Cringe :D
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	
	}
}

