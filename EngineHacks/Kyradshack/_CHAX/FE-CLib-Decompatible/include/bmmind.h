#ifndef GUARD_BM_MIND_H
#define GUARD_BM_MIND_H

struct ActionData
{
    // unknown stuff (sometimes RNs are pushed here) (maybe an union?)
    /* 00 */ u16 _u00[3];
    /* 06 */ u16 item;

    /* 08 */ u16 unk08;
    /* 0A */ u16 unk0A;

    /* 0C */ u8 subjectIndex;
    /* 0D */ u8 targetIndex;

    /* 0E */ u8 xMove;
    /* 0F */ u8 yMove;

    /* 10 */ u8 moveCount;

    /* 11 */ u8 unitActionType;

    // maybe from this onwards it's an union?

    /* 12 */ u8 itemSlotIndex;

    /* 13 */ u8 xOther;
    /* 14 */ u8 yOther;

    /* 15 */ u8 trapType;

    /* 16 */ u8 suspendPointType;

    /* 18 */ struct BattleHit * scriptedBattleHits;

    /* 1C */ struct BattleHit script_hits[7]; /* equals to sizeof event-queue */

    /* 38 */
};

void StoreRNStateToActionStruct(void);
void LoadRNStateFromActionStruct(void);
unsigned int ApplyUnitAction(ProcPtr proc);
// ??? ActionRescue(???);
// ??? AfterDrop_CheckTrapAfterDropMaybe(???);
// ??? sub_80321C8(???);
// ??? ActionDrop(???);
// ??? ActionVisitAndSeize(???);
// ??? ActionCombat(???);
// ??? ActionArena(???);
// ??? ActionDance(???);
// ??? ActionTalk(???);
// ??? ActionSupport(???);
// ??? ActionSteal(???);
// ??? ActionSummon(???);
// ??? ActionSummonDK(???);
// ??? DeathDropSpriteAnim_Loop(???);
// ??? DeathDropSpriteAnim_ExecAnyTrap(???);
// ??? DeathDropSpriteAnim_End(???);
void DropRescueOnDeath(ProcPtr proc, struct Unit* unit);
// ??? KillUnitOnCombatDeath(???);
// ??? KillUnitOnArenaDeathMaybe(???);
void BATTLE_GOTO1_IfNobodyIsDead(ProcPtr proc);
// ??? DidUnitDie(???);
// ??? BATTLE_PostCombatDeathFades(???);
// ??? BATTLE_DeleteLinkedMOVEUNIT(???);
// ??? BATTLE_HandleCombatDeaths(???);
// ??? sub_80328B0(???);
// ??? BATTLE_HandleItemDrop(???);
// ??? sub_8032974(???);
// ??? BATTLE_HandleArenaDeathsMaybe(???);
// ??? sub_80329C0(???);

#endif // GUARD_BM_MIND_H
