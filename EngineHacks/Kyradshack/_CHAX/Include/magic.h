
struct CharacterMagicData {
    /* 00 */ s8 baseMag;
    /* 01 */ s8 growthMag;
};


struct ClassMagicData {
    /* 00 */ s8 baseMag;
    /* 01 */ s8 growthMag;
    /* 02 */ s8 maxMag;
    /* 03 */ u8 promotionMag; 
};

int GetUnitMagic(struct Unit* unit);

extern const struct ClassMagicData MagClassTable[];
extern const struct CharacterMagicData MagCharTable[];