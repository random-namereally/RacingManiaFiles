#include "GameHeaders.h"

static int execute(MenuInputs *input, GameData *gamedata);
static void display(int min, int max, GameData *gamedata, MenuInputs *input);
static void ttrain_racer(Racer *trainee, Trainer *trainer, Actions identifier, GameData *gamedata, MenuInputs *input);
static float calculate_base(Racer *trainee, Actions identifier);
static int train_chance(int chance, int energy);
static void training_gain( float *primary_change, float *secondary_change, float *tertiary_change,
                    float primary_mult, float secondary_mult, float tertiary_mult,
                    float mood, float *energy_change, Actions identifier);
static void training_loss( float *primary_change, float *secondary_change, float *tertiary_change,
                    float mood, float *mood_change, float *energy_change, Actions identifier);
static void apply_changes(Racer *trainee, Trainer *trainer, float primary_change, float secondary_change, float tertiary_change,
                          float mood_change, float energy_change, Actions identifier);
static void draw_result (const char *name, float primary_change, float secondary_change, float tertiary_change,
                        float mood_change, float energy_change, Actions identifier, int failed);
static void draw_middle_success(int first, int second, int third, int energy,
                                const char* main, const char* side, const char* minor);
static void draw_middle_failure(int first, int second, int third, int mood,
                                int energy, const char* main, const char* side, const char* minor);
static void draw_fail_event(const char *name, Actions identifier, int fail_level, GameData *gamedata, MenuInputs *input);
static void display_fail_1(int min, int max, GameData *gamedata, MenuInputs *input);
static void display_fail_2(int min, int max, GameData *gamedata, MenuInputs *input);


int main_training_hub(GameData *gamedata)
{
    int min = 1, max = 6;
    MenuInputs input;
    reset_inputs(&input);

    clear_screen();
    display(min, max, gamedata, &input);

    int status = std_get_int(min, max, &input, gamedata, display, std_status_msg);
    if (status == IntEOF) return SceneError;

    return execute(&input, gamedata);
}

static void display(int min, int max, GameData *gamedata, MenuInputs *input)
{
    std_header("Training Grounds");
    printf("1. Run as quickly as possible on the track (Speed)\n");
    printf("2. Run around the track repeatedly (Stamina)\n");
    printf("3. Run 100 meters as fast as possible (Power)\n");
    printf("4. Run for as long as possible (Guts)\n");
    printf("5. Maneuver around obstacles (Wit)\n");
    printf("6. Stop Training\n");
    printf("--------------------------------------------------\n");
    std_prompt("selection", min, max);
}

static int execute(MenuInputs *input, GameData *gamedata)
{
    switch (input->choice)
    {
        case 1: ttrain_racer(&gamedata->trainee, &gamedata->trainer, TrainSpeed, gamedata, input);    break;
        case 2: ttrain_racer(&gamedata->trainee, &gamedata->trainer, TrainStamina, gamedata, input);  break;
        case 3: ttrain_racer(&gamedata->trainee, &gamedata->trainer, TrainPower, gamedata, input);    break;
        case 4: ttrain_racer(&gamedata->trainee, &gamedata->trainer, TrainGuts, gamedata, input);     break;
        case 5: ttrain_racer(&gamedata->trainee, &gamedata->trainer, TrainWit,gamedata, input);       break;
        case 6: return 1;
    }

    return SceneTrainingHub;
}

static void ttrain_racer(Racer *trainee, Trainer *trainer, Actions identifier, GameData *gamedata, MenuInputs *input)
{
    // Initialize values
    float primary_change = 0, secondary_change = 0, tertiary_change = 0;
    float primary_mult = 0, secondary_mult = 0, tertiary_mult = 0;

    float energy_change = 0, mood_change = 0;
    float mood = (float)trainee->mood, energy = (float)trainee->current_energy;

    // Set type specific values
    switch (identifier)
{
    case TrainSpeed:
        primary_mult  = trainee->speed_multiplier;
        secondary_mult= trainee->power_multiplier;
        tertiary_mult = trainee->wit_multiplier;
        break;

    case TrainStamina:
        primary_mult  = trainee->stamina_multiplier;
        secondary_mult= trainee->guts_multiplier;
        tertiary_mult = trainee->wit_multiplier;
        break;

    case TrainPower:
        primary_mult  = trainee->power_multiplier;
        secondary_mult= trainee->stamina_multiplier;
        tertiary_mult = trainee->wit_multiplier;
        break;

    case TrainGuts:
        primary_mult  = trainee->guts_multiplier;
        secondary_mult= trainee->speed_multiplier;
        tertiary_mult = trainee->power_multiplier;
        break;

    case TrainWit:
        primary_mult  = trainee->wit_multiplier;
        secondary_mult= trainee->speed_multiplier;
        tertiary_mult = trainee->stamina_multiplier;
        break;

    default:
        primary_mult  = 1.0f;
        secondary_mult= 1.0f;
        tertiary_mult = 1.0f;
        break;
}
    // Calculate chance of failure
    float base_chance = calculate_base(trainee, identifier);

    // Roll for failure
    int failed = train_chance(base_chance, trainee->current_energy);

    if (failed==false)
    {
        training_gain( &primary_change, &secondary_change, &tertiary_change,
                       primary_mult,  secondary_mult,  tertiary_mult,
                       mood, &energy_change, identifier);
    }

    else{training_loss(&primary_change, &secondary_change, &tertiary_change,
                       mood, &mood_change, &energy_change, identifier);}

    apply_changes(trainee, trainer, primary_change, secondary_change, tertiary_change, mood_change, energy_change, identifier);

    draw_result (trainee->name, primary_change, secondary_change, tertiary_change, mood_change, energy_change, identifier, failed);
    if (failed!=0) {draw_fail_event(trainee->name, identifier,failed , gamedata, input);}
}


static float calculate_base(Racer *trainee, Actions identifier)
{
    float safe = 0, max = 0;

    switch (identifier)
    {
        case TrainSpeed:
        case TrainStamina:
        case TrainPower:
            safe = 50; max = 99;
            break;
        case TrainGuts:
            safe = 58; max = 99;
            break;
        case TrainWit:
            safe = 50; max = 70;
            break;
        default:
            return 0;
    }

    // Mood and Debuffs
    // Assuming mood is 1-7, 4 is neutral.
    int bonus = (4 * (4 - trainee->mood) + (trainee->has_practice_poor * 2));

    // Calculation
    int result = (max * (safe - trainee->current_energy) / safe) + bonus;

    // Clamping and fitting to 100
    return clamp(result, 0, max);


}

static int train_chance(int chance, int energy)
{
    int roll = (rand() % 100) + 1; // Generates from 1 to 100
    if (roll>chance) {return 0;}
    else
    {
        roll = (rand() % 100) + 1; // Generates from 1 to 100

        if (roll<=(100*energy/50)) {return 1;}
        else {return 2;}
    }

}

static void training_gain( float *primary_change, float *secondary_change, float *tertiary_change,
                    float primary_mult, float secondary_mult, float tertiary_mult,
                    float mood, float *energy_change, Actions identifier)

{
    float main = 0, side = 0;
    mood = 1+((mood - 4.0f)/10); // High mood = Higher stats
    switch (identifier)
    {
        case TrainSpeed: case TrainPower:   *energy_change = -20;    break;
        case TrainStamina:                  *energy_change = -19;    break;

        case TrainGuts:                     *energy_change = -22;    break;
        case TrainWit:                     *energy_change = +5;     break;
    }

    switch (identifier)
    {
        case TrainSpeed:    main = 10;  side = 5;   break;
        case TrainStamina:  main = 9;   side = 4;   break;
        case TrainPower:    main = 8;   side = 5;   break;
        case TrainGuts:     main = 8;   side = 4;   break;
        case TrainWit:     main = 9;   side = 2;   break;
    }

    *primary_change    = main*primary_mult     *mood;
    *secondary_change  = side*secondary_mult   *mood;
    *tertiary_change   = side*tertiary_mult    *mood;
}

static void training_loss( float *primary_change, float *secondary_change, float *tertiary_change,
                    float mood, float *mood_change, float *energy_change, Actions identifier)
{
    float main = -5, side = -2;
    mood = 1-((mood - 4.0f)/10);// High mood = lower penalties
    *primary_change    = main  *   mood;
    *secondary_change  = side  *   mood;
    *tertiary_change   = side  *   mood;
    *mood_change       = -1;
    *energy_change     = 5;
}

static void apply_changes(Racer *trainee, Trainer *trainer, float primary_change, float secondary_change, float tertiary_change, float mood_change, float energy_change, Actions identifier)
{
    int main_type = -1;
    int side_type = -1;
    int minor_type = -1;

    switch (identifier)
    {
        case TrainSpeed:    main_type = NumSpeed;   side_type = NumPower;                           break;
        case TrainStamina:  main_type = NumStamina; side_type = NumGuts;                            break;
        case TrainPower:    main_type = NumPower;   side_type = NumStamina;                         break;
        case TrainGuts:     main_type = NumGuts;    side_type = NumSpeed; minor_type = NumPower;    break;
        case TrainWit:     main_type = NumWit;     side_type = NumSpeed;                           break;
    }


    update_racer_stat   (trainee, main_type, primary_change);
    update_racer_stat   (trainee, side_type, secondary_change);
    update_racer_stat   (trainee, minor_type, tertiary_change);
    update_racer_stat   (trainee, NumCurrentEnergy, energy_change);
    update_racer_stat   (trainee, NumMood, mood_change);
    update_trainer_stat (trainer, NumCash, -TRAINING_COST_CASH);
}

static void draw_result (const char *name, float primary_change, float secondary_change, float tertiary_change, float mood_change, float energy_change, Actions identifier, int failed)
{

    int first = round_up(primary_change);
    int second = round_up(secondary_change);
    int third = round_up(tertiary_change);
    int mood = round_up(mood_change);
    int energy = round_up(energy_change);
    const char *main = "";
    const char *side = "";
    const char *minor = "";
    char header[100];

    switch (identifier)
        {
            case TrainSpeed:
                main = "Speed";
                side = "Power";
                break;
            case TrainStamina:
                main = "Stamina";
                side = "Guts";
                break;
            case TrainPower:
                main = "Power";
                side = "Stamina";
                break;
            case TrainGuts:
                main = "Guts";
                side = "Speed";
                minor = "Power";
                break;
            case TrainWit:
                main = "Wit";
                side = "Speed";
                break;
        }

    clear_screen();

    if (failed)
    {

        snprintf(header, sizeof(header), "%s training failure!", main);
        std_header(header);
        printf("\n\n\n");
        printf("%s failed %s training", name, main);
        draw_middle_failure(first, second, third, mood, energy, main, side, minor);
    }
    else
    {
        snprintf(header, sizeof(header), "%s training success!", main);
        std_header(header);
        printf("\n\n\n");
        printf("%s succeeds %s training", name, main);
        draw_middle_success(first, second, third, energy, main, side, minor);
    }

    printf("\n");
    printf("--------------------------------------------------\n");
    std_prompt("to continue", 0, 0);
    getflush();

}

static void draw_middle_success(int first, int second, int third, int energy, const char* main, const char* side, const char* minor)
{
    printf("\n");
    printf("%s +%d", main, first);
    printf("  %s +%d", side, second);
    if (strlen(minor)){printf("  %s +%d", minor, third);}
    printf("  Cash: -%d", TRAINING_COST_CASH);
    printf("  %s %d", "Energy", energy);
}

static void draw_middle_failure(int first, int second, int third, int mood, int energy, const char* main, const char* side, const char* minor)
{
    printf("\n");
    printf("%s %d", main, first);
    printf("  %s %d", side, second);
    if (strlen(minor)){printf("  %s %d", minor, third);}
    printf("  Cash: -%d", TRAINING_COST_CASH);
    printf("  %s %d", "Mood", mood);
    printf("  %s +%d", "Energy", energy);
}

static void draw_fail_event(const char *name, Actions identifier, int fail_level, GameData *gamedata, MenuInputs *input)
{
    clear_screen();
    int roll= (rand() % 100) + 1;
    int min = 1, max = 2;

    int main_type = -1;
    int side_type = -1;
    int minor_type = -1;

    int main_penalty = -25;
    int side_penalty = -10;
    int minor_penalty = -10;

    switch (identifier)
    {
        case TrainSpeed:    main_type = NumSpeed;   side_type = NumPower;                           break;
        case TrainStamina:  main_type = NumStamina; side_type = NumGuts;                            break;
        case TrainPower:    main_type = NumPower;   side_type = NumStamina;                         break;
        case TrainGuts:     main_type = NumGuts;    side_type = NumSpeed; minor_type = NumPower;         break;
        case TrainWit:     main_type = NumWit;     side_type = NumSpeed;                           break;
    }

    // Normal failure event
    if (fail_level == 1)
    {
        display_fail_1(min, max, gamedata, input);
        std_get_int(min, max, input, gamedata, display_fail_1, std_status_msg);

        clear_screen();
        std_header("Get Well Soon!");

        switch (input->choice)
        {
            case 1:

                printf("%s rests carefully.\n\n", name);
                printf("-1 Mood   -5 Stat");
                update_racer_stat(&gamedata->trainee, NumMood, -1);
                update_racer_stat(&gamedata->trainee, main_type, main_penalty*0.2);

                if (roll <= 50)
                {
                    printf("Gained Practice Poor");
                    update_racer_stat(&gamedata->trainee, NumHasPracticePoor, 1);
                }
                printf("\n");
                break;

            case 2:
                if (roll <= 30)
                {
                    printf("%s got on their feet, ready to push forward!\n\n", name);
                    printf("+30 Energy\n");
                    update_racer_stat(&gamedata->trainee, NumCurrentEnergy, 30);
                }
                else
                {
                    printf("%s tried to get up but just embarrassed themselves\n\n", name);
                    printf("-1 Mood   -10 Stat\n");
                    update_racer_stat(&gamedata->trainee, NumMood, -1);
                    update_racer_stat(&gamedata->trainee, main_type, main_penalty*0.4);
                }
                break;
        }

    }

    // Badder Event for failure
    else
    {
        display_fail_2(min, max, gamedata, input);
        std_get_int(min, max, input, gamedata, display_fail_2, std_status_msg);

        clear_screen();
        std_header("Don't Overdo It!");

        switch (input->choice)
        {
            case 1:
                update_racer_stat(&gamedata->trainee, main_type, main_penalty);
                update_racer_stat(&gamedata->trainee, side_type, side_penalty);
                if (minor_type >= 0) update_racer_stat(&gamedata->trainee, minor_type, minor_penalty);
                update_racer_stat(&gamedata->trainee, NumCurrentEnergy, 5);

                if (roll <= 50)
                {
                    printf("%s rests demoralized.\n\n", name);
                    printf("-2 Mood   +5 Energy\n");
                    update_racer_stat(&gamedata->trainee, NumMood, -2);
                }
                else
                {
                    printf("%s rests demoralized and frustrated.\n\n", name);
                    printf("-3 Mood   +5 Energy   Gained Practice Poor\n");
                    update_racer_stat(&gamedata->trainee, NumMood, -3);
                    update_racer_stat(&gamedata->trainee, NumHasPracticePoor, 1);
                }
                break;

            case 2:
                if (roll <= 10)
                {
                    printf("%s shot back up like the sun in the morning!\n\n", name);
                    printf("+30 Energy\n");
                    update_racer_stat(&gamedata->trainee, NumCurrentEnergy, 30);
                }

                else if (roll <= 75)
                {
                    printf("Stars burn out, you know.\n\n");
                    printf("-2 Mood   +10 Energy   Stats Down   Lost Stats\n"); // FIXED
                    update_racer_stat(&gamedata->trainee, main_type, main_penalty);
                    update_racer_stat(&gamedata->trainee, side_type, side_penalty);
                    if (minor_type >= 0) update_racer_stat(&gamedata->trainee, minor_type, minor_penalty);
                    update_racer_stat(&gamedata->trainee, NumCurrentEnergy, 10);
                    update_racer_stat(&gamedata->trainee, NumMood, -2);
                }

                else
                {
                    printf("Stars burn out... more so for %s.\n\n", name);
                    printf("-3 Mood   +10 Energy   Stats Down   Gained Practice Poor\n");
                    update_racer_stat(&gamedata->trainee, main_type, main_penalty * 2);
                    update_racer_stat(&gamedata->trainee, side_type, side_penalty * 2);
                    if (minor_type >= 0) update_racer_stat(&gamedata->trainee, minor_type, minor_penalty * 2);
                    update_racer_stat(&gamedata->trainee, NumCurrentEnergy, 10);
                    update_racer_stat(&gamedata->trainee, NumMood, -3);
                    update_racer_stat(&gamedata->trainee, NumHasPracticePoor, 1);
                }
                break;
        }

    printf("--------------------------------------------------\n");
    std_prompt("to continue", 0, 0);
    getflush();
    }
}

static void display_fail_1(int min, int max, GameData *gamedata, MenuInputs *input)
{
    clear_screen();
    std_header("Get Well Soon!");
    printf("%s had to go to the infirmary\ndue to the training incident.\n\n", gamedata->trainee.name);
    printf("1. Take it easy for now.\n");
    printf("2. We can go farther!.\n");
    printf("--------------------------------------------------\n");
    std_prompt("Selection", min, max);
}

static void display_fail_2(int min, int max, GameData *gamedata, MenuInputs *input)
{
    clear_screen();
    std_header("Don't Overdo It!");
    printf("%s collapsed and got admitted to the infirmary!!!\n\n", gamedata->trainee.name);
    printf("1. That was too far\n");
    printf("2. Stars aren't built without pressure!!!\n");
    printf("--------------------------------------------------\n");
    std_prompt("Selection", min, max);
}
