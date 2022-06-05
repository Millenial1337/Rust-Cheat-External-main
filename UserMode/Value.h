#pragma once
namespace Value {
    float menux = 0;
    float menuy = 0;
    namespace bools {
        namespace Aim {
            bool Enable, VisibleCheck, IgnoreTeam, TargetLine, Fov, Smooth, IgnoreSleepers;
            bool PSilent;
        }
        namespace Player {
            bool CustomFov;
            bool Zoom = false;
            bool Longhand = false;
            bool SuperEoka = false;
            namespace PlayerWalk {
                bool Spiderman = true, FakeAdmin, ChangeGravity, InfinityJump;//DebugBypass AntiAim InfinityJump
            }
            namespace PlayerModel {
            }
        }

        namespace Visuals {
            namespace PlayerPanel {
                bool Enable = true, Name, HP, Weapons;
            }
            namespace ESP {
                bool Enable, Player, NPC, IgnoreSleeper, Corpse, Backpack;
                bool Name, Box = true, Distance, SteamID, Health = true, Weapon = true;
            }
            namespace World {
                namespace Items {
                    bool Stash, Hemp, AirDrop, CH47, Minicopter, Patrol;
                    namespace Ore {
                        bool Stone, Iron, Sulfur;
                    }
                }
                bool AlwaysDay, NightModeup, FixAmbient;

            }
            namespace Radar {
                bool Enable, Sleeper;
            }
        }
        namespace Misc {
            bool killhack = false;
            int killhackkey = 0;
            int FlyHackkey = 0;
            bool WalkOnWater = false;
            bool FixCamera = false;
            bool FlyHack = false;
            bool SpeedHack = false;
            bool rapidFire = false;
            bool fastSwitch = false;
            bool instantCompound = false;
        }
        namespace Weapon {
            bool IsAutomatic, NoSpread, NoRecoil, FatBullet, SuperBow;
        }
    }
    namespace floats {
        namespace Aim {
            int Distance = 400;
            int Fov = 50;
            float Smooth = 5;
        }
        namespace Screen {
            float H;
            float W;
        }
        namespace Player {
            float CustomFov = 90;
            float Gravity = 2;
            float Zoomvalue = 20.f;
            int zoomKey = 0;
            int RCSyaw = 0;
            bool LongNeck = false;
            int LongNeckKey = 0;
            int RCSpitch = 0;
        }
        namespace Visuals {
            namespace World {
                int LimitDistance = 100;
                int LimitDistance2 = 2000;
                int Time = 9;
            }
            namespace Radar {
                int Radius = 100;
                int Distance = 100;
            }
        }
    }
    namespace Colors {
        namespace Aim {
            float Fov[] = { 0.7, 0.7, 0.7, 1 };
            float TargetLine[] = { 0.7, 0.7, 0.7, 1 };
        }
        namespace Visuals {
            namespace ESP {
                float Weapon[] = { 0.7, 0.7, 0.7, 1 };
                float Box[] = { 0.7, 0.7, 0.7, 1 };
                float Name[] = { 0.7, 0.7, 0.7, 1 };
                float Health[] = { 0.7, 0.7, 0.7, 1 };
                float Distance[] = { 0.7, 0.7, 0.7, 1 };
            }
            namespace World {
                float Stash[] = { 0, 0.25 , 1, 1 };
                float Hemp[] = { 0, 1 , 0, 1 };
                float AirDrop[] = { 0.4, 0 ,1, 1 };
                float CH47[] = { 1, 0 , 0, 1 };
                float Minicopter[] = { 0.45, 1 ,0, 1 };
                float Patrol[] = { 0, 1 ,1, 1 };
                float Corpse[] = { 0.45, 1 ,0, 1 };
                float Backpack[] = { 0, 1 ,1, 1 };
                namespace Ore {
                    float Stone[] = { 0.86, 0.86 , 0.86, 1 };
                    float Iron[] = { 1, 0.58 ,0, 1 };
                    float Sulfur[] = { 1, 1 , 0, 1 };
                }
            }
        }
    }
}
