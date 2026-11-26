#ifndef DEFINES_H
#define DEFINES_H
// for at lave coden mere læsebar og nemmere at holde styr på har vi lavet true and flase til definet variabler
#define True 1
#define False 0

#define POPULATION 40
#define MATRIX_SIZE_X 8
#define MATRIX_SIZE_Y 8
#define TRANSMISSION_RISK_PERCENT 10
#define TRANSMISSION_RISK_MASK_PERCENT 2
#define EMPTY -1
#define INFECTION_DURATION 10
#define TIMESTEP 1
#define MAX_SIMULATION_TIMESTEPS 1000
#define VISUAL_MODE 1
#define PRINT_DELAY 0.5

typedef enum {
    SUSCEPTIBLE,
    INFECTED,
    RECOVERED,
    VACCINATED
} State;

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    int wearingMask; // is used as a true/false varible
    int keepingDistabce; // is used as a true/false varible
    int isInQuarantine; // is used as a true/false varible
} MitigationPolicies;

typedef struct {
    State state;
    MitigationPolicies activeMitigationPolicies;
    int infectionTime;
    Position position;
    Position hub1;
    Position hub2;
    Position target;
    int wearsMask;
} Agent;

#endif
