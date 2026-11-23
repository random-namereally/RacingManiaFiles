#ifndef GENERICFUNCTIONS_H_INCLUDED
#define GENERICFUNCTIONS_H_INCLUDED

void clear_screen();
void getflush();
int std_get_int(int min, int max, MenuInputs *input, void (*display)(int, int), void (*status_msg)(int, int, int));
void std_status_msg(int min, int max, int status);
void std_header(const char *header);
void std_prompt(const char *prompt, int min, int max);
void std_overview(GameData *gamedata);


#endif
