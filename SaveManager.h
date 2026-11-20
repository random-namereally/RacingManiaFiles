#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

/*
SaveManager: plain-text save files (save1.txt, save2.txt, ...).

Format is one "key=value" per line, starting with "version=1".
Unknown keys are ignored and missing keys keep their current value,
so adding a field to GameData later will not break old saves.

NOTE: this header uses GameData, so include it AFTER DataManager.h
(GameHeaders.h already does this for the other headers).
*/

#define SAVE_SLOTS   3
#define SAVE_VERSION 1

// 0 means success, anything else is an error
typedef enum
{
    SaveOk,
    SaveErrBadSlot,     // slot not between 1 and SAVE_SLOTS
    SaveErrOpen,        // could not create the file
    SaveErrWrite,       // disk full / write failed
    SaveErrNoFile,      // slot is empty
    SaveErrVersion,     // save made by a different version
    SaveErrCorrupt,     // bad line, bad value, or out of range data
} SaveResult;

int  save_game(const GameData *gamedata, int slot);  // returns SaveOk on success
int  load_game(GameData *gamedata, int slot);        // gamedata is untouched unless SaveOk
int  save_exists(int slot);                          // 1 if the slot has a file, else 0
const char *save_result_message(int result);        // text you can print to the player

#endif // SAVEMANAGER_H

