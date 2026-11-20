#include "GameHeaders.h"
#include "SaveManager.h"
#include <limits.h>
#include <errno.h>


// FIELD LISTS- draft to be updated 
// To save a new value, add ONE line here. It is then written,
// read and range-checked automatically.
// Format: X("file_key", struct_path, min, max)
// Ranges are guesses: adjust them to match your game balance.

#define INT_FIELDS(X) \
    X("trainee_named",     trainee.is_trainee_named, 0, 1) \
    X("current_energy",    trainee.current_energy,   0, 10000) \
    X("max_energy",        trainee.max_energy,       1, 10000) \
    X("mood",              trainee.mood,             0, 100) \
    X("speed",             trainee.speed,            0, 9999) \
    X("stamina",           trainee.stamina,          0, 9999) \
    X("power",             trainee.power,            0, 9999) \
    X("guts",              trainee.guts,             0, 9999) \
    X("wit",               trainee.wit,              0, 9999) \
    X("frontrunner_aff",   trainee.frontrunner_affinity, 0, 20) \
    X("pacechaser_aff",    trainee.pacechaser_affinity,  0, 20) \
    X("latesurger_aff",    trainee.latesurger_affinity,  0, 20) \
    X("endcloser_aff",     trainee.endcloser_affinity,   0, 20) \
    X("dirt_aff",          trainee.dirt_affinity,    0, 20) \
    X("turf_aff",          trainee.turf_affinity,    0, 20) \
    X("sprint_aff",        trainee.sprint_affinity,  0, 20) \
    X("mile_aff",          trainee.mile_affinity,    0, 20) \
    X("medium_aff",        trainee.medium_affinity,  0, 20) \
    X("long_aff",          trainee.long_affinity,    0, 20) \
    X("popularity",        trainee.popularity,       0, 100000000) \
    X("fans",              trainee.fans,             0, 100000000) \
    X("trainer_named",     trainer.is_trainer_named, 0, 1) \
    X("cash",              trainer.cash,             -1000000000, 1000000000) \
    X("debt",              trainer.debt,             0, 1000000000) \
    X("debt_limit",        trainer.debt_limit,       0, 1000000000) \
    X("credit_score",      trainer.credit_score,     -1000000, 1000000) \
    X("turn",              date.turn,                1, 73) \
    X("biweek",            date.biweek,              1, 2) \
    X("month",             date.month,               1, 12) \
    X("season",            date.season,              1, 4) \
    X("year",              date.year,                1, 4) \
    X("rain_chance",       rain_chance,              0, 100)

#define FLOAT_FIELDS(X) \
    X("speed_mult",    trainee.speed_multiplier,   0.0, 100.0) \
    X("stamina_mult",  trainee.stamina_multiplier, 0.0, 100.0) \
    X("power_mult",    trainee.power_multiplier,   0.0, 100.0) \
    X("guts_mult",     trainee.guts_multiplier,    0.0, 100.0) \
    X("wit_mult",      trainee.wit_multiplier,     0.0, 100.0)


// HELPERS

static int make_path(int slot, char *buf, size_t size, const char *ext)
{
    if (slot < 1 || slot > SAVE_SLOTS) return 0;
    snprintf(buf, size, "save%d%s", slot, ext);
    return 1;
}

static int parse_int(const char *s, int *out, long lo, long hi)
{
    char *end;
    errno = 0;
    long v = strtol(s, &end, 10);
    if (errno != 0 || end == s || *end != '\0' || v < lo || v > hi) return 0;
    *out = (int)v;
    return 1;
}

static int parse_float(const char *s, float *out, double lo, double hi)
{
    char *end;
    errno = 0;
    double v = strtod(s, &end);
    if (errno != 0 || end == s || *end != '\0' || v < lo || v > hi) return 0;
    *out = (float)v;
    return 1;
}

// Copies a name, replacing line breaks so one name cannot span two lines
static void clean_name(const char *src, char *dst, size_t size)
{
    size_t i;
    for (i = 0; i + 1 < size && src[i] != '\0'; i++)
        dst[i] = (src[i] == '\n' || src[i] == '\r') ? ' ' : src[i];
    dst[i] = '\0';
}

// Returns 1 = applied, 0 = bad value, -1 = unknown key (ignored)
static int apply_key(GameData *g, const char *key, const char *val)
{
    #define X(k, f, lo, hi) if (strcmp(key, k) == 0) return parse_int(val, &g->f, lo, hi);
    INT_FIELDS(X)
    #undef X

    #define X(k, f, lo, hi) if (strcmp(key, k) == 0) return parse_float(val, &g->f, lo, hi);
    FLOAT_FIELDS(X)
    #undef X

    if (strcmp(key, "trainee_name") == 0)
    {
        if (strlen(val) >= NAMESIZE) return 0;
        strcpy(g->trainee.name, val);
        return 1;
    }
    if (strcmp(key, "trainer_name") == 0)
    {
        if (strlen(val) >= NAMESIZE) return 0;
        strcpy(g->trainer.name, val);
        return 1;
    }
    return -1;
}


// PUBLIC FUNCTIONS

int save_exists(int slot)
{
    char path[32];
    if (!make_path(slot, path, sizeof(path), ".txt")) return 0;

    FILE *fp = fopen(path, "r");
    if (fp == NULL) return 0;
    fclose(fp);
    return 1;
}

int save_game(const GameData *gamedata, int slot)
{
    char path[32], tmp_path[32];
    if (!make_path(slot, path, sizeof(path), ".txt")) return SaveErrBadSlot;
    make_path(slot, tmp_path, sizeof(tmp_path), ".tmp");

    // Write to a temp file first so a crash cannot ruin an existing save
    FILE *fp = fopen(tmp_path, "w");
    if (fp == NULL) return SaveErrOpen;

    char name[NAMESIZE];
    fprintf(fp, "version=%d\n", SAVE_VERSION);

    clean_name(gamedata->trainee.name, name, sizeof(name));
    fprintf(fp, "trainee_name=%s\n", name);
    clean_name(gamedata->trainer.name, name, sizeof(name));
    fprintf(fp, "trainer_name=%s\n", name);

    #define X(k, f, lo, hi) fprintf(fp, k "=%d\n", gamedata->f);
    INT_FIELDS(X)
    #undef X

    #define X(k, f, lo, hi) fprintf(fp, k "=%.3f\n", (double)gamedata->f);
    FLOAT_FIELDS(X)
    #undef X

    int failed = ferror(fp);
    if (fclose(fp) != 0) failed = 1;
    if (failed)
    {
        remove(tmp_path);
        return SaveErrWrite;
    }

    // rename() will not overwrite on Windows, so remove the old file first
    remove(path);
    if (rename(tmp_path, path) != 0)
    {
        remove(tmp_path);
        return SaveErrWrite;
    }
    return SaveOk;
}

int load_game(GameData *gamedata, int slot)
{
    char path[32];
    if (!make_path(slot, path, sizeof(path), ".txt")) return SaveErrBadSlot;

    FILE *fp = fopen(path, "r");
    if (fp == NULL) return SaveErrNoFile;

    // Work on a copy: the real game data is only replaced if the WHOLE file is valid
    GameData tmp = *gamedata;
    char line[256];
    int version = 0;
    int result = SaveOk;

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // A line with no newline that is not the last one means it was too long
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] != '\n' && !feof(fp)) { result = SaveErrCorrupt; break; }
        while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) line[--len] = '\0';

        if (len == 0 || line[0] == '#') continue;

        char *eq = strchr(line, '=');
        if (eq == NULL) { result = SaveErrCorrupt; break; }
        *eq = '\0';
        const char *key = line;
        const char *val = eq + 1;

        if (strcmp(key, "version") == 0)
        {
            if (!parse_int(val, &version, 1, INT_MAX)) { result = SaveErrCorrupt; break; }
            if (version != SAVE_VERSION)               { result = SaveErrVersion; break; }
            continue;
        }

        if (version == 0) { result = SaveErrCorrupt; break; }   // version must be the first line

        if (apply_key(&tmp, key, val) == 0) { result = SaveErrCorrupt; break; }
    }
    fclose(fp);

    if (result == SaveOk && version == 0) result = SaveErrCorrupt;

    // Cross-field checks that single ranges cannot catch
    if (result == SaveOk && tmp.trainee.current_energy > tmp.trainee.max_energy)
        result = SaveErrCorrupt;

    if (result != SaveOk) return result;

    *gamedata = tmp;
    return SaveOk;
}

const char *save_result_message(int result)
{
    switch (result)
    {
    case SaveOk:          return "Saved/loaded successfully.";
    case SaveErrBadSlot:  return "Invalid save slot.";
    case SaveErrOpen:     return "Could not open the save file.";
    case SaveErrWrite:    return "Could not write the save file (disk full?).";
    case SaveErrNoFile:   return "No save found in that slot.";
    case SaveErrVersion:  return "That save was made by a different game version.";
    case SaveErrCorrupt:  return "The save file is damaged or has invalid data.";
    default:              return "Unknown save error.";
    }
}
