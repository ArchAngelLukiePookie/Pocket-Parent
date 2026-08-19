// POCKET PARENT (tamagotchi and calendar)

// SETUP

#include <WiFi.j>    // basic wifi
#include <ArduinoJson.h> // translates the script for the calendar
#include <TFT_eSPI.h> // controls the screens colour

// DISPLAY + GRAPHICS
TFT_eSPI tft = TFT_eSPI();

TFT_eSprite sprite = TFT_eSPI tft = TFT_eSprite(&tft); //canvas (135 x 240) pixels
TFT_eSprite scrollsprite = TFT_eSPI tft = TFT_eSprite(&tft); // for scrolling text

// colours
#define TFT_SILVER 0xC618
#define TFT_AMBER  0xFEA0

//script when i get idiot google scripts working

// hardware/buttons
//board has built in buttons 
#define BUTTON_1 0 //TOP BUTTON
#define BUTTON_2 35 // BOTTOM BUTTON 

// MACHINE, MENU AND APP VIEW AND STUFF (the fun part)
//^'state machine' acts as traffic light this tells the program which screen to show. can only be in one state at one time
enum AppState {MAIN_VIEW, MENU_VIEW, SELECT_PET_VIEW} //<- This tells the thing which screen to show when
AppState currentState = MAIN_VIEW; //<- tells the code to start on the main screen. this should be the calendar/notifications

int selectedPet = 0; // <- this keeps track of which pet the user uses
const int PET_COUNT = 3; //number of pet options available (may change later)
const char* petName[] = {"DALEK", "TARDIS", "THE DOCTOR"};

//DATA STORAGE (Huzzah)

struct CalendarEvent {
  String timeHeader; // <- clock + day example: MON 21:00
  String eventText;  // <- event name example: DALEK TAKE OVER 
};

#define MAX_EVENTS 10 // Maximum number of events we can store in memory
CalendarEvent eventList[MAX_EVENTS];
int totalEvents = 0;      // How many events we actually downloaded
int currentEventIdx = 0;  // Which event we are currently looking at on screen

