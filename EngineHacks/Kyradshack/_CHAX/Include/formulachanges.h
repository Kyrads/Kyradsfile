bool CanBattleUnitGainExp(struct BattleUnit* actor, struct BattleUnit* target);
bool CanBattleUnitGainLevels(struct BattleUnit* battleUnit);
int GetLevelDifference(struct BattleUnit* actor, struct BattleUnit* target);
int GetNPCStatIncrease(int growth);
int GetFatigueLevel(struct Unit* unit);

#define CA_NO_EXP CA_NEGATE_LETHALITY