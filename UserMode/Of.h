#pragma once
DWORD64 automatic[]
{
	1545779598, // AK - 47;
	-1758372725, // Томсон
	1796682209, // SMG
	-1812555177,// LR - 300
	1318558775, // MP5
	-2069578888, // M249
	884424049,
};

DWORD64 sniper[]
{
	-778367295, // L96
	1588298435, // Болт
	1443579727, // лук
	884424049, // Блочка
	1443579727, //лук

};

DWORD64 semiautomatic[]{
	-904863145, // Берданка 
	818877484, // Пэшка
	-852563019, // берета
	1373971859, // Питон
	649912614, // револьвер
	28201841, // M39
	1953903201, // Гвоздомёт
	-1123473824, // Гранатомёт
};

DWORD64 meele[]{

	-1966748496, 2040726127, -194509282, 1540934679, 1814288539, 1491189398, 1602646136, -1137865085, 1090916276, -1978999529, 1326180354, 1488979457, 171931394, -1583967946, 200773292, -262590403, -1252059217, 795236088, -196667575, -1506397857, -1302129395, 963906841, 1104520648, -1780802565, -2069578888
};

#define oGameObjectManager 0x17C1F18 // 0x17D69F8
#define oBaseNetworkable   51846112 // BaseNetworkable_c*
#define oConVar 51837016 //ConVar_Graphics_c*
#define oTOD_Sky 51856480 //TOD_Sky_c*
#define oBasePlayer 51848808 //BasePlayer_c*
#define oOcclusionCulling 51847464 //"Signature": "OcclusionCulling_c*"
#define oConClient 51842192 //ConVar_Client_c*
#define ooBaseEntity_c 52240584 //BaseEntity_c*

//class BasePlayer
#define oPlayerFlags 0x678 // public BasePlayer.PlayerFlags playerFlags;
#define oPlayerEyes 0x680 // public PlayerEyes eyes;
#define oPlayerName 0x6D8 // protected string _displayName;
#define oPlayerHealth 0x224 // private float _health;//protected float _health;
#define olastSentTickTime 0x64C // private float lastSentTickTime;
#define oClientTeam 0x598 // public PlayerTeam clientTeam;
#define oLifestate 0x21C // public BaseCombatEntity.LifeState lifestate;
#define oSteamID 0x6C0 // public ulong userID;
#define oPlayerInventory 0x688 // public PlayerInventory inventory;
#define oActiveUID 0x5C8// private uint clActiveItem;
#define oFrozen 0x4C8// public bool Frozen;
#define oWaterBonus 0x750// public float clothingWaterSpeedBonus;
#define oNoBlockAiming 0x748 // public bool clothingBlocksAiming;
#define oSpeedReduction 0x74C// public float clothingMoveSpeedReduction;
#define oClothingAccuracyBonus 0x754 //	public float clothingAccuracyBonus;


//EntityRef
#define oHeld 0x98//private EntityRef heldEntity
#define oStancePenalty 0x31C //private float stancePenalty;
#define	oAimconePenalty	0x320 //private float aimconePenalty;
#define	oHipAimCone 0x2EC //public float hipAimCone;
#define	oAimCone 0x730 //public float aimCone;			(class BaseProjectile)
#define	oAimconePenaltyPerShot 0x2F0 //public float aimconePenaltyPerShot;
#define oSuccessFraction 0x360 // public float successFraction;
#define oAttackRadius 0x294 //public float attackRadius;
#define oEffectiveRange 0x1FC //public float effectiveRange;
#define oIsAutomatic 0x298 //public bool isAutomatic;
#define oMaxDistance 0x290 //public float maxDistance;			(class BaseMelee)
#define oRepeatDelay 0x1F4 //public float repeatDelay;

#define odisplayname 0x28 //public Translate.Phrase displayName;//public class ItemDefinition : MonoBehaviour

//BaseProjectile
#define oAuto 0x288 //public bool automatic;
#define oFastReload 0x2C0 // bool fractionalReload
#define oDistance 0x280 // public float distanceScale
#define oprojectileVelocityScale 0x284 //public float projectileVelocityScale
#define oShortname 0x20// public string shortname;//public class ItemDefinition : MonoBehaviour
#define oModelState 0x5F8// public ModelState modelState; class BasePlayer : BaseCombatEntity
#define owaterLevel 0x38 //public float waterLevel class BucketVMFluidSim : MonoBehaviour //
#define ogravityTestRadius 0x80// public float gravityTestRadius
#define ogroundAngle 0xC4 // private float groundAngle; // 0xC4
#define ocapsuleHeight 0x68// public float capsuleHeight; // 0x68
#define ocapsuleCenter 0x6C// public float capsuleCenter; // 0x6C
#define oGrounded 0x140//private bool grounded;
#define oGravityMultiplierSwimming 0x88 // public float gravityMultiplierSwimming;
#define oClothingBlocksAiming 0x750 // public bool clothingBlocksAiming;
#define oAttackReady 0x360 // protected bool attackReady;
//BaseMovement
#define oPlayerMovement 0x4E8 // public BaseMovement movement;
#define oGravityMultiplier 0x84 // public float gravityMultiplier;

#define oGroundAngle 0xC4// private float groundAngle;
#define oGroundAngleNew 0xC8 // private float groundAngleNew;

//RecoilProperties
#define oRecoilProperties 0x2D8 //public RecoilProperties recoil;
#define oRecoilMinYaw 0x18 //public float recoilYawMin;
#define oRecoilMaxYaw 0x1C //public float recoilYawMax;
#define oRecoilMinPitch 0x20 //public float recoilPitchMin;
#define oRecoilMaxPitch 0x24 //public float recoilPitchMax;


//PlayerModel
#define oPlayerModel 0x4C0 // public PlayerModel playerModel;
#define oVisible 0x278 // internal bool visible;

//PlayerInput
#define oPlayerInput 0x4E0// public PlayerInput input;
#define oBodyAngles 0x3C // private Vector3 bodyAngles;
#define oRecoilAngles 0x64 // public Vector3 recoilAngles;
#define oHasKeyFocus 0x94 // private bool hasKeyFocus;



#define oArrowBack 0x364 // private float arrowBack;
#define oTriggerReady 0x360 // protected bool attackReady;
#define oItemDefinition 0x20 // public ItemDefinition info;
#define oItemid 0x18 // public int itemid;


#define oBlockSprintOnAttack 0x299 //public bool blockSprintOnAttack;