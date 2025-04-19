extern u16 gPal_PlayerInterface_Blue[];
extern u16 gPal_PlayerInterface_Red[];
extern u16 gPal_PlayerInterface_Green[];
#define GE_WIDTH 14
#define GE_HEIGHT 8
#define GE_TILEMAP_PALETTE 3
#define MINIMUG_WIDTH 4
#define MINIMUG_HEIGHT 4
#define MINIMUG_X 1
#define MINIMUG_Y 2
#define MINIMUG_PALETTE 4
#define MINIMUG_BASE_TILE 0x0180
#define NAME_X 5
#define NAME_Y 1
#define NAME_WIDTH 7
#define NAME_COLOR TEXT_COLOR_NORMAL
#define HPORSTATUS_X 5
#define HPORSTATUS_Y 3
#define NUMBER_BASE_TILE 0x02E0
#define NUMBER_PALETTE 8
#define HP_LABEL_BASE_TILE 0x0120
#define HP_LABEL_PALETTE 2
#define HP_DIVIDER_BASE_TILE 0x013E
#define HP_DIVIDER_PALETTE 2
#define STATUS_BASE_TILE 0x016F
#define STATUS_PALETTE 0
#define BG_NUMBER_BASE_TILE 0x0128
#define BG_NUMBER_PALETTE 1
#define ATK_LABEL_X 5
#define ATK_LABEL_Y 4
#define ATK_LABEL_BASE_TILE 0x0169
#define ATK_LABEL_PALETTE 2
#define ATK_X 56
#define ATK_Y 32
#define AS_LABEL_X 5
#define AS_LABEL_Y 5
#define AS_LABEL_BASE_TILE 0x0160
#define AS_LABEL_PALETTE 2
#define AS_X 56
#define AS_Y 40
#define RES_LABEL_X 8
#define RES_LABEL_Y 5
#define RES_LABEL_BASE_TILE 0x0165
#define RES_LABEL_PALETTE 2
#define DEF_X 80
#define DEF_Y 32
#define DEF_LABEL_X 8
#define DEF_LABEL_Y 4
#define DEF_LABEL_BASE_TILE 0x0167
#define DEF_LABEL_PALETTE 2
#define RES_X 80
#define RES_Y 40
extern u16 gAffinityWeaponRankPalette[];
#define AFFINITY_X 96
#define AFFINITY_Y 8
#define AFFINITY_PAGE 2
#define AFFINITY_BASE_TILE 0x030A
#define AFFINITY_PALETTE 21
#define INVENTORY_ICON_X 8
#define INVENTORY_ICON_Y 48
#define INVENTORY_ICON_BASE_TILE 0x0300
#define INVENTORY_ICON_PALETTE 20
#define ITEM_ICON_PAGE 0
#define LEVEL_LABEL_X 1
#define LEVEL_LABEL_Y 1
#define LEVEL_LABEL_BASE_TILE 0x0162
#define LEVEL_LABEL_PALETTE 2
#define LEVEL_X 30
#define LEVEL_Y 8

void TilemapVesly_Static(struct PlayerInterfaceProc* proc, struct UnitDataProc* udp);
void AttackLabelStandard_Static(struct PlayerInterfaceProc* proc, struct UnitDataProc* udp);
void DefenseLabelStandard_Static(struct PlayerInterfaceProc* proc, struct UnitDataProc* udp);
void MinimugStandard_Static(struct PlayerInterfaceProc* proc, struct UnitDataProc* udp);
void LevelLabelStandard_Static(struct PlayerInterfaceProc* proc, struct UnitDataProc* udp);
void NameLeftAligned_Static(struct PlayerInterfaceProc* proc, struct UnitDataProc* udp);
void ResistanceLabelStandard_Static(struct PlayerInterfaceProc* proc, struct UnitDataProc* udp);
void AffinityStandard_Static(struct PlayerInterfaceProc* proc, struct UnitDataProc* udp);
void FullInventoryStandard_Static(struct PlayerInterfaceProc* proc, struct UnitDataProc* udp);
void AttackSpeedLabelStandard_Static(struct PlayerInterfaceProc* proc, struct UnitDataProc* udp);
#define STATIC_CALLS \
  TilemapVesly_Static, \
  AttackLabelStandard_Static, \
  DefenseLabelStandard_Static, \
  MinimugStandard_Static, \
  LevelLabelStandard_Static, \
  NameLeftAligned_Static, \
  ResistanceLabelStandard_Static, \
  AffinityStandard_Static, \
  FullInventoryStandard_Static, \
  AttackSpeedLabelStandard_Static, \
  NULL

void LevelStandard_Dynamic(struct PlayerInterfaceProc* proc, struct UnitDataProc* udp);
void AttackStandard_Dynamic(struct PlayerInterfaceProc* proc, struct UnitDataProc* udp);
void FullInventoryStandard_Dynamic(struct PlayerInterfaceProc* proc, struct UnitDataProc* udp);
void HPOrStatus_Dynamic(struct PlayerInterfaceProc* proc, struct UnitDataProc* udp);
void AffinityStandard_Dynamic(struct PlayerInterfaceProc* proc, struct UnitDataProc* udp);
void DefenseStandard_Dynamic(struct PlayerInterfaceProc* proc, struct UnitDataProc* udp);
void AttackSpeedStandard_Dynamic(struct PlayerInterfaceProc* proc, struct UnitDataProc* udp);
void ResistanceStandard_Dynamic(struct PlayerInterfaceProc* proc, struct UnitDataProc* udp);
#define DYNAMIC_CALLS \
  LevelStandard_Dynamic, \
  AttackStandard_Dynamic, \
  FullInventoryStandard_Dynamic, \
  HPOrStatus_Dynamic, \
  AffinityStandard_Dynamic, \
  DefenseStandard_Dynamic, \
  AttackSpeedStandard_Dynamic, \
  ResistanceStandard_Dynamic, \
  NULL

struct Vec2 DrawVertical_TilemapDestination(struct PlayerInterfaceProc* proc, struct Vec2 coords);
#define TILEMAP_DESTINATION \
  DrawVertical_TilemapDestination, \
  NULL


#define INVALID_POSITION_CALLS \
  NULL

void DrawVertical_Extend(struct PlayerInterfaceProc* proc);
#define EXTEND_CALLS \
  DrawVertical_Extend, \
  NULL

void DrawVertical_Retract(struct PlayerInterfaceProc* proc);
#define RETRACT_CALLS \
  DrawVertical_Retract, \
  NULL

void ResistanceLabelStandard_Init(struct PlayerInterfaceProc* proc);
void DefenseLabelStandard_Init(struct PlayerInterfaceProc* proc);
void LevelLabelStandard_Init(struct PlayerInterfaceProc* proc);
void AttackLabelStandard_Init(struct PlayerInterfaceProc* proc);
void AttackSpeedLabelStandard_Init(struct PlayerInterfaceProc* proc);
#define INIT_CALLS \
  ResistanceLabelStandard_Init, \
  DefenseLabelStandard_Init, \
  LevelLabelStandard_Init, \
  AttackLabelStandard_Init, \
  AttackSpeedLabelStandard_Init, \
  NULL
