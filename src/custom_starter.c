#include "global.h"
#include "pokemon.h"
#include "constants/pokemon.h"
#include "constants/vars.h"
#include "constants/moves.h"
#include "constants/items.h"
#include "constants/abilities.h"
#include "event_data.h"

extern u8 GiveMonToPlayer(struct Pokemon *mon);

void GiveCustomStarter(void)
{
    struct Pokemon mon;
    u16 species = VarGet(VAR_TEMP_2);
    u32 personality = (u32)VarGet(VAR_TEMP_5);
    u32 ivs = ((u32)VarGet(VAR_TEMP_6) << 16) | (u32)VarGet(VAR_TEMP_7);

    CreateMonWithIVsPersonality(&mon, species, 5, ivs, personality);

    {
        // All-Gen ability override — an explicit ABILITY_ constant picked in the LOTAD tool's
        // ability pool (any of the species' real Ability 1/Ability 2/Hidden Ability slots as of
        // Gen 5), not just whatever vanilla PID-based GetAbilityBySpecies() would produce.
        // ABILITY_NONE (0) means "no override", leaving vanilla assignment untouched.
        u16 abilityOverride = VarGet(VAR_TEMP_0);
        if (abilityOverride != ABILITY_NONE)
            SetMonData(&mon, MON_DATA_ABILITY_OVERRIDE, &abilityOverride);
    }

    {
        // All-Gen level-up learnset override — nonzero means "use the LOTAD tool's All-Gen draft
        // learnset for this mon's current species (src/data/pokemon/level_up_learnset_overrides.h)
        // instead of the real vanilla gLevelUpLearnsets[species] table" for both organic
        // learn-on-levelup and (if a move slot above is ever left MOVE_NONE) the auto-derived
        // initial moveset. Zero (the default for an older scripts.inc predating this feature)
        // leaves vanilla behavior untouched. See MON_DATA_LEVEL_UP_LEARNSET_OVERRIDE's own comment
        // in include/constants/pokemon.h.
        u8 learnsetOverride = VarGet(VAR_TEMP_LEVEL_UP_LEARNSET_OVERRIDE);
        if (learnsetOverride)
            SetMonData(&mon, MON_DATA_LEVEL_UP_LEARNSET_OVERRIDE, &learnsetOverride);
    }

    {
        u16 move;

        move = VarGet(VAR_TEMP_8);
        if (move != MOVE_NONE)
            SetMonMoveSlot(&mon, move, 0);

        move = VarGet(VAR_TEMP_9);
        if (move != MOVE_NONE)
            SetMonMoveSlot(&mon, move, 1);

        move = VarGet(VAR_TEMP_A);
        if (move != MOVE_NONE)
            SetMonMoveSlot(&mon, move, 2);

        move = VarGet(VAR_TEMP_B);
        if (move != MOVE_NONE)
            SetMonMoveSlot(&mon, move, 3);
    }

    {
        u16 item = VarGet(VAR_TEMP_C);
        if (item != ITEM_NONE)
            SetMonData(&mon, MON_DATA_HELD_ITEM, &item);
    }

    {
        // EV headstart — part of the featured Pokemon's origin backstory, same treatment as its
        // held item and egg moves above: a fixed pre-loaded amount, not earned or purchased
        // mid-run. Packed two-per-register (8 bits each) across VAR_TEMP_D/E/F by the LOTAD tool,
        // mirroring how IVs are packed across VAR_TEMP_6/7. The real 100-EV vitamin cap and the
        // tool's total budget are both enforced there, not here — SetMonData below writes
        // whatever byte it's given, with no clamping or validation of its own.
        u16 packedHpAtk = VarGet(VAR_TEMP_D);
        u16 packedDefSpe = VarGet(VAR_TEMP_E);
        u16 packedSpaSpd = VarGet(VAR_TEMP_F);
        u8 hpEV = packedHpAtk & 0xFF;
        u8 atkEV = (packedHpAtk >> 8) & 0xFF;
        u8 defEV = packedDefSpe & 0xFF;
        u8 speEV = (packedDefSpe >> 8) & 0xFF;
        u8 spaEV = packedSpaSpd & 0xFF;
        u8 spdEV = (packedSpaSpd >> 8) & 0xFF;

        SetMonData(&mon, MON_DATA_HP_EV, &hpEV);
        SetMonData(&mon, MON_DATA_ATK_EV, &atkEV);
        SetMonData(&mon, MON_DATA_DEF_EV, &defEV);
        SetMonData(&mon, MON_DATA_SPEED_EV, &speEV);
        SetMonData(&mon, MON_DATA_SPATK_EV, &spaEV);
        SetMonData(&mon, MON_DATA_SPDEF_EV, &spdEV);
    }

    // Recalculates stats now that real EVs are set — CreateMonWithIVsPersonality already ran
    // CalculateMonStats once above, but that pass saw EV 0 for every stat.
    CalculateMonStats(&mon);

    GiveMonToPlayer(&mon);
}