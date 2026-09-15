// All-Gen level-up learnset overrides.
//
// Per-SPECIES alternates to the real vanilla gLevelUpLearnsets[species] table
// (data/pokemon/level_up_learnsets.h) — that file is never included, edited, or otherwise
// touched by this one. Consulted only for a mon instance with
// MON_DATA_LEVEL_UP_LEARNSET_OVERRIDE set (see GetLevelUpLearnsetForBoxMon/GetLevelUpLearnsetForMon
// in src/pokemon.c), which nothing but the featured Pokemon's own instance data ever has —
// every other mon of the same species, including trainer parties auto-derived via
// GiveBoxMonInitialMoveset, is completely unaffected and keeps reading the real table.
//
// Keyed by species (not a flat slot number) because the override needs to keep resolving
// correctly as the featured mon evolves mid-run — Squirtle -> Wartortle -> Blastoise each need
// their own array here, exactly mirroring how gLevelUpLearnsets itself is indexed by species.
//
// LEVEL_UP_MOVE/LEVEL_UP_END come from level_up_learnsets.h, already #included by src/pokemon.c
// above this file's own #include — not redefined here.
//
// Content sourced from the already-drafted src/data/pokemon/level_up_learnsets_gen5_draft.h
// (built via the LOTAD tool's Level-Up Moveset tab). That draft file remains the scratch/staging
// area the tool writes to; this is the first array from it actually wired into the running game.

static const u16 sLevelUpLearnsetOverride_Squirtle[] = {
    LEVEL_UP_MOVE(1, MOVE_TACKLE),
    LEVEL_UP_MOVE(4, MOVE_TAIL_WHIP),
    LEVEL_UP_MOVE(7, MOVE_BUBBLE),
    LEVEL_UP_MOVE(10, MOVE_WITHDRAW),
    LEVEL_UP_MOVE(13, MOVE_WATER_GUN),
    LEVEL_UP_MOVE(16, MOVE_BITE),
    LEVEL_UP_MOVE(19, MOVE_RAPID_SPIN),
    LEVEL_UP_MOVE(22, MOVE_PROTECT),
    LEVEL_UP_MOVE(25, MOVE_WATER_PULSE),
    LEVEL_UP_MOVE(28, MOVE_AQUA_TAIL),
    LEVEL_UP_MOVE(31, MOVE_SKULL_BASH),
    LEVEL_UP_MOVE(34, MOVE_IRON_DEFENSE),
    LEVEL_UP_MOVE(37, MOVE_RAIN_DANCE),
    LEVEL_UP_MOVE(40, MOVE_HYDRO_PUMP),
    LEVEL_UP_END
};

static const u16 sLevelUpLearnsetOverride_Wartortle[] = {
    LEVEL_UP_MOVE(1, MOVE_TACKLE),
    LEVEL_UP_MOVE(1, MOVE_TAIL_WHIP),
    LEVEL_UP_MOVE(1, MOVE_BUBBLE),
    LEVEL_UP_MOVE(4, MOVE_TAIL_WHIP),
    LEVEL_UP_MOVE(7, MOVE_BUBBLE),
    LEVEL_UP_MOVE(10, MOVE_WITHDRAW),
    LEVEL_UP_MOVE(13, MOVE_WATER_GUN),
    LEVEL_UP_MOVE(16, MOVE_BITE),
    LEVEL_UP_MOVE(20, MOVE_RAPID_SPIN),
    LEVEL_UP_MOVE(24, MOVE_PROTECT),
    LEVEL_UP_MOVE(28, MOVE_WATER_PULSE),
    LEVEL_UP_MOVE(32, MOVE_AQUA_TAIL),
    LEVEL_UP_MOVE(36, MOVE_SKULL_BASH),
    LEVEL_UP_MOVE(40, MOVE_IRON_DEFENSE),
    LEVEL_UP_MOVE(44, MOVE_RAIN_DANCE),
    LEVEL_UP_MOVE(48, MOVE_HYDRO_PUMP),
    LEVEL_UP_END
};

static const u16 sLevelUpLearnsetOverride_Blastoise[] = {
    LEVEL_UP_MOVE(1, MOVE_FLASH_CANNON),
    LEVEL_UP_MOVE(1, MOVE_TACKLE),
    LEVEL_UP_MOVE(1, MOVE_TAIL_WHIP),
    LEVEL_UP_MOVE(1, MOVE_BUBBLE),
    LEVEL_UP_MOVE(1, MOVE_WITHDRAW),
    LEVEL_UP_MOVE(4, MOVE_TAIL_WHIP),
    LEVEL_UP_MOVE(7, MOVE_BUBBLE),
    LEVEL_UP_MOVE(10, MOVE_WITHDRAW),
    LEVEL_UP_MOVE(13, MOVE_WATER_GUN),
    LEVEL_UP_MOVE(16, MOVE_BITE),
    LEVEL_UP_MOVE(20, MOVE_RAPID_SPIN),
    LEVEL_UP_MOVE(24, MOVE_PROTECT),
    LEVEL_UP_MOVE(28, MOVE_WATER_PULSE),
    LEVEL_UP_MOVE(32, MOVE_AQUA_TAIL),
    LEVEL_UP_MOVE(39, MOVE_SKULL_BASH),
    LEVEL_UP_MOVE(46, MOVE_IRON_DEFENSE),
    LEVEL_UP_MOVE(53, MOVE_RAIN_DANCE),
    LEVEL_UP_MOVE(60, MOVE_HYDRO_PUMP),
    LEVEL_UP_END
};

struct LevelUpLearnsetOverrideEntry
{
    u16 species;
    const u16 *learnset;
};

static const struct LevelUpLearnsetOverrideEntry sLevelUpLearnsetOverrides[] = {
    { SPECIES_SQUIRTLE,  sLevelUpLearnsetOverride_Squirtle },
    { SPECIES_WARTORTLE, sLevelUpLearnsetOverride_Wartortle },
    { SPECIES_BLASTOISE, sLevelUpLearnsetOverride_Blastoise },
};

#define LEVEL_UP_LEARNSET_OVERRIDES_COUNT (sizeof(sLevelUpLearnsetOverrides) / sizeof(sLevelUpLearnsetOverrides[0]))
