//Cesar Ruiz & Sean Snyder
//COP 3223H
//Final Project

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_MONSTERS_IN_AREA 5
#define MAX_NUM_MONSTER_STATS 2

typedef struct{
    char name[30];
    char gender[6];
    char job[10];
    char race[20];
    int level;
    int experience;
    int gold;
    int physicalPower;
    int speed;
    int hpMax;
    int hpCurrent;
    int magicalPower;
    int maxMana;
    int currentMana;
} charInformation;

//void allocateProtagStats(int hpMod);

void encounterMonster();

//This function is used whenever the player chooses the option to explore, in this case, the forest
void exploreForest();

//Character information struct is used to set the base attributes
//and information of various entities.
//NOTE: all variables for characterInformation may not be used for a
//given variable.

int main(){
    //The protagonist variable is the character the plays controls.
    //Any information directly regarding the playable character
    //should edit only the protagonist variable.
    charInformation protagonist;
    char keypress;

    //Here we set up the randomizer for later in the program
    srand(time(0));

    printf("You find yourself in a thick forest, unsure of where you are. You can't seem to recall anything... besides who you are.\n");
    printf("What is your name?\n");
    scanf("%s", protagonist.name);

    //Repeats the choices until the user selects a valid one, then
    //sets protagonist as needed.
    printf("What is your gender? (Press the button that corresponds with your choice).\n");
    do {
        printf("1. Male    2. Female\n");
        scanf(" %c", &keypress);

        switch(keypress){
            case '1':
                strcpy(protagonist.gender, "male");
                break;
            case '2':
                strcpy(protagonist.gender, "female");
                break;
            default:
                printf("Say again?\n");
        }
    } while( !( (keypress >= '1') && (keypress <= '2') ) );

    //Since the variable keypress was reused multiple times, do-
    //while was used in order to prevent a leftover keypress value
    //from preventing a while loop from running
    printf("You are a %s named %s. You walk over to a nearby pond and look at your reflection. What do you see?\n", protagonist.gender, protagonist.name);
    do {
        printf("1. Human    2. Elf    3. Ork\n");
        scanf(" %c", &keypress);

        switch(keypress){
            case '1':
                strcpy(protagonist.race, "Human");
                printf("Humans are an all-around race. They tend to favor all play styles, though not as much as more restrictive races.\n");
                protagonist.hpMax = 15;
                break;
            case '2':
                strcpy(protagonist.race, "Elf");
                printf("Eves are a race that excel in magic and feats of dexterity. They tend to favor mobile and magic orientated play styles.\n");
                protagonist.hpMax = 11;
                break;
            case '3':
                strcpy(protagonist.race, "Ork");
                printf("Orks are brutal race. They prefer to use their brawn to solve most issues. They tend to favor melee and defensive play styles.\n");
                protagonist.hpMax = 19;
                break;
            default:
                printf("Say again?\n");
        }
    } while( !( (keypress >= '1') && (keypress <= '3')  ) );

    //Player sets their job/class
    printf("You are an %s. Before waking up here you recall that you were a...\n", protagonist.race);
    do {
        printf("1. Paladin    2. Mage   3. Archer    4. Berserker\n");
        scanf(" %c", &keypress);

        switch(keypress){
            case '1':
                strcpy(protagonist.job, "Paladin");
                break;
            case '2':
                strcpy(protagonist.job, "Mage");
                break;
            case '3':
                strcpy(protagonist.job, "Archer");
                break;
            case '4':
                strcpy(protagonist.job, "Berserker");
                break;
            default:
                printf("Say again?\n");
        }
    } while( !( ( (keypress >= '1') && (keypress <= '4') ) ) );

    //Main gameplay loop, where player either encounters monsters to fight
    //or explores the world.
    do {
        do{
            printf("You are in a thick forest. What do you do?\n");
            printf("1. Explore    2. Check Stats\n");

            scanf(" %c", &keypress);

            switch(keypress){
                case '1':
                    if((rand() % 100) >= 50){
                        encounterMonster();
                    } else{
                        exploreForest();
                    }
                    break;
                case '2':
                        printf("Your current stats are: \n");
                    break;
                default:
                    printf("Say again?\n");
            }
        }while(keypress == '1');
    } while( !( (keypress >= '1') && (keypress <= '2') ) );

    return 0;
}

/*void allocateProtagStats(int hpMod){

}*/

void exploreForest(){
    int random;
    char insideKeypress;

    //We use a random number to determine the outcome of each exploration
    random = (rand() % 100);

    //If the number rolls 66 or above, the player finds loot
    if (random >= 66){
        printf("You found some loot!\n");
    }
    //If the number is between 33 and 65, the player advances
    else if (random >= 33){
        printf("You found a hidden path deep into the forest\nWhat will you do?\n");
        do{
            printf("1. Follow the path    2. Turn back\n");
            scanf(" %c", &insideKeypress);

            switch(insideKeypress){
            case '1':
                printf("You venture further down the path and find yourself lost in a strange land.\n");
                break;
            case '2':
                printf("You turn around and retrace your steps.\n");
                break;
            default:
                printf("Say again?\n");
            }

        } while( !( (insideKeypress >= '1') && (insideKeypress <= '2') ) );
    }
    //If the number is between 0 and 32, nothing happens
    else{
        printf("You found nothing and keep moving.\n");
    }

}

void encounterMonster(){
    //2D array of strings storing filenames of all possible monsters
    //player could encounter in the area they are in.
    FILE *monsterFile;
    FILE *monsterInfo;
    char possibleMonsters[MAX_MONSTERS_IN_AREA][50];
    int i, monsterStats[MAX_NUM_MONSTER_STATS];
    char monsterName[30];

    //This opens up a text document that contains the names of the text files of all possible monsters in a given area
    monsterFile = fopen("possibleMonstersInForest.txt", "r");

    //This runs a loop that records the name of each text files inside of the array
    for(i = 0; i < MAX_MONSTERS_IN_AREA; i++){
        fscanf(monsterFile, "%s", possibleMonsters[i]);
    }
    //Now we are done with this particular file so we must close it
    fclose(monsterFile);

    //Now that each array is filled with the names of each monster's text file,
    //we use a randomizer to pick a monster out of the possible files
    monsterInfo = fopen(possibleMonsters[ (rand() % MAX_MONSTERS_IN_AREA) ], "r");

    //Here we access the monster's name from the appropriate file
    fscanf(monsterInfo, "%s", &monsterName);
    printf("Monster name is: %s\n", monsterName);

    //Here we we retrieve the Monster's stats
    for(i = 0; i < MAX_NUM_MONSTER_STATS; i++){
        fscanf(monsterInfo, "%d", &monsterStats[i]);
        printf("Monster Stat is: %d\n", monsterStats[i]);
    }

    /*do{

    } while();*/


    //Again, we are done with the file and finish by closing it
    fclose(monsterInfo);
}
