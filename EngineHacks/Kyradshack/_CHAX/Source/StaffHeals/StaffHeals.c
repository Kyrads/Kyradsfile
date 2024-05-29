#include "gbafe.h"
#include "magic.h"

int GetUnitItemHealAmount(struct Unit* unit, int item) {
    int result = 0;

    switch (GetItemIndex(item)) {

    case ITEM_STAFF_HEAL:
    result = 8;
    break;

    case ITEM_VULNERARY:
    case ITEM_VULNERARY_2:
        result = 12;
        break;

    case ITEM_STAFF_MEND:
    case ITEM_STAFF_PHYSIC:
    case ITEM_STAFF_FORTIFY:
        result = 16;
        break;

    case ITEM_STAFF_RECOVER:
        result = 32;
        break;
    case ITEM_ELIXIR:
        result = 80;
        break;

    } // switch (GetItemIndex(item))

    if (GetItemAttributes(item) & IA_STAFF) {
        result += GetUnitMagic(unit);

        if (result > 80)
            result = 80;
    }

    return result;
}