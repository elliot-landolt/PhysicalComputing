/*
Final Project
By: Elliot Landolt

This is an MP3 player and a mini piano. The program features 31 functional songs 
and the piano is the 8 notes in a C scale.
*/

// Library Setup
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Tone.h>

// Speaker Setup
int spkPin = 10;

//Mode Setup
bool menuMode = LOW; // mp3 mode
bool pianoMode = LOW;
bool menu_mode_run = HIGH;
bool main_menu_run = LOW;

// LIBRARY SETUP
bool lib_A = LOW;
bool lib_B = LOW;
bool lib_C = LOW;
bool lib_D = LOW;
bool lib_selected = LOW;

// BLINK W/O DELAY SETUP
unsigned long previousMillis = 0;
const long interval = 2000; // 2 seconds


//KEYPAD SETUP
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// SONG LIST SETUP
char songlistA[10][18] = {"1. The Simpsons ","2. Indiana Jones","3. Take On Me   ","4.TheEntertainer","5. Tom Cruise MI","6. X-Files      ","7. 20th Fox     ","8. Barbie Girl  ", "9. Star Wars    ", "Press 0 to Exit"};
char songlistB[9][18] = {"1. USA Anthem", "2.GalfromIpanema", "3. Oh Canada", "4. All Star", "5. Lose Yourself", "6. 1 2 Step",  "7. ND Fight Song", "8. Olympic Theme", "Press 0 to Exit"};
char songlistC[8][18] = {"1. Sandstorm", "2.TheNextEpisode", "3. I'm Blue", "4. RealSlimShady", "5. Wake Me Up",  "6.ThomasTheTank", "7. SweetChild", "Press 0 to Exit"};
char songlistD[7][18] = {"1. Last Resort", "2. Pokemon", "3. Hips Dont Lie", "4. In Too Deep", "5. Say ItAin'tSo", "6. Creep", "Press 0 to Exit"};
int i = 0;

// LCD Setup
LiquidCrystal_I2C lcd(0x27,16,2); // call library lcd(set LCD address, 16 width, 2 lines display)

// RTTL Setup

Tone tone1;

#define OCTAVE_OFFSET 0

int notes[] = { 0,
NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4,
NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5,
NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6,
NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7
};

// RTTL SONGS

// LIST A
char *simpsons = "The Simpsons:d=4,o=5,b=160:c.6,e6,f#6,8a6,g.6,e6,c6,8a,8f#,8f#,8f#,2g,8p,8p,8f#,8f#,8f#,8g,a#.,8c6,8c6,8c6,c6";
char *indiana = "Indiana:d=4,o=5,b=250:e,8p,8f,8g,8p,1c6,8p.,d,8p,8e,1f,p.,g,8p,8a,8b,8p,1f6,p,a,8p,8b,2c6,2d6,2e6,e,8p,8f,8g,8p,1c6,p,d6,8p,8e6,1f.6,g,8p,8g,e.6,8p,d6,8p,8g,e.6,8p,d6,8p,8g,f.6,8p,e6,8p,8d6,2c6";
char *take_on_me = "TakeOnMe:d=4,o=4,b=160:8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5,8f#5,8e5,8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5";
char *entertainer = "Entertainer:d=4,o=5,b=140:8d,8d#,8e,c6,8e,c6,8e,2c.6,8c6,8d6,8d#6,8e6,8c6,8d6,e6,8b,d6,2c6,p,8d,8d#,8e,c6,8e,c6,8e,2c.6,8p,8a,8g,8f#,8a,8c6,e6,8d6,8c6,8a,2d6";
char *xfiles = "Xfiles:d=4,o=5,b=125:e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,g6,f#6,e6,d6,e6,2b.,1p,g6,f#6,e6,d6,f#6,2b.,1p,e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,e6,2b.";
char *fox = "20thCenFox:d=16,o=5,b=140:b,8p,b,b,2b,p,c6,32p,b,32p,c6,32p,b,32p,c6,32p,b,8p,b,b,b,32p,b,32p,b,32p,b,32p,b,32p,b,32p,b,32p,g#,32p,a,32p,b,8p,b,b,2b,4p,8e,8g#,8b,1c#6,8f#,8a,8c#6,1e6,8a,8c#6,8e6,1e6,8b,8g#,8a,2b";
char *barbie_girl = "BarbieGirl:d=4,o=5,b=125:8g#,8e,8g#,8c#6,a,p,8f#,8d#,8f#,8b,g#,8f#,8e,p,8e,8c#,f#,c#,p,8f#,8e,g#,f#";
char *mission_imp = "MissionImp:d=16,o=6,b=95:32d,32d#,32d,32d#,32d,32d#,32d,32d#,32d,32d,32d#,32e,32f,32f#,32g,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,a#,g,2d,32p,a#,g,2c#,32p,a#,g,2c,a#5,8c,2p,32p,a#5,g5,2f#,32p,a#5,g5,2f,32p,a#5,g5,2e,d#,8d";
char *star_wars = "StarWars:d=4,o=5,b=45:32p,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#.6,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#6";

// LIST B
char *USA_Anthem = "UnitedSt:d=4,o=5,b=130:32p,8g.,16e,c,e,g,2c6,8e6.,16d6,c6,e,f#,2g,g,e6.,8d6,c6,2h,8a.,16h,c6,c6,g,e,c";
char *Ipanema ="GirlFromIpane:d=4,o=5,b=160:g.,8e,8e,d,g.,8e,e,8e,8d,g.,e,e,8d,g,8g,8e,e,8e,8d,f,d,d,8d,8c,e,c,c,8c,a#4,2c";
char *OHCanada = "OhCanada:d=4,o=5,b=100:2g,a#,8p,8a#,2d#,p,f,g,g#,a#,c6,2f,2p,2g,a,8p,8a,2a#,p,c6,2d6,2c6,1a#";
char *Allstar = "AllStar:d=4,o=5,b=40:16g.,32d.6,32b.,16b.,32a.,32g.,32g.,16c.6,32b.,32b.,32a.,32a.,16g.,32g.,32d.6,32b.,32b.,32a.,32a.,32g.,32g.,16e.,d,32g.,32g.,32d.6,32b.,32b.,32a.,32a.,32g.,32g.,16c.6,32b.,32b.,32a.,32a.,32g.,32g.,16d.6,32b.,32b.,16a.,32g.,32g.,16a.,8e";
char *LoseYourself = "LoseYour:d=16,o=5,b=285:4g6,8p,8c,4p,8c,4p,8c,4p,8c,4p,8c,4p,8c,4p,8c,4p,4d#6,8p,8c,4p,8c,4p,8c,4p,4f6,8p,8c,4p,4a#6,8g#6,4g6,8f6,4g6,8p,8c,4p,8c,4p,8c,4p,8c,4p,8c,4p,8c,4p,8c,4p,4d#6,8p,8c,4p,8c,4p,8c,4p,4f6,8p,8c,4p,4a#6,8g#6,4g6,8f6,4g6";
char *Ciara = "1,2Step:d=4,o=5,b=112:g,8d#,8c,g,d#,8g,8g,8g,8g,8g,8f,8g,8g#,8p,8g#,8g#,8g#,8g#,8g#,g#,8g#,8g#,8g#,8g#,a#,8g#,16g#,16g,8c6,8c6,8c,8c,8c,8c,8c,8c,8c6,8c6,8c,8c,8c,8c,c,8c6,8c6,8c,8c,8c,8c,c,g#,g#,a#,8g#,16g#,g";
char *NDFightSong = "FightSon:d=16,o=5,b=35:32e,e,32e,d#,e,32f#,f#,32f,f#.,32p,32f#,f#,32f#,f,f#,32g#,g#,32g,g#.,32p,8a,b,a,g#,g,e,f#,32g#,f#,32f,g#,f#,32f#,f,32f#,8b";
char *OlympicTheme = "OlympicF:d=4,o=5,b=225:32p,1a,2c6,p,8p,8c6,2f,2g,2a,2f,g,p,8g,p,8g,2g,a,g,f,8f,8g,a,f,1g,1a,2c6,p,8p,8c6,2f,2g,2a,f,p,g,p,8g,p,8g,g,p,a,g,8f,8p,8f,8g,8a,8p,8g,8p,2f,p";

// LIST C
char *Sandstorm = "SandStor:d=4,o=5,b=125:16d6,16d6,16d6,16d6,8d6,16d6,16d6,16d6,16d6,16d6,16d6,8d6,16g6,16g6,16g6,16g6,16g6,16g6,16g6,16g6,16f6,16f6,16f6,16f6,16f6,16f6,8f6,16c6,16c6,16d6,16d6,16d6,16d6,8d6,16d6,16d6,16d6,16d6,16d6,16d6,16d6,16d6,16f6,16f6,16d6,16d6,16d6,16d6,16d6";
char *NextEpisode = "NextEpis:d=4,o=5,b=70:32d,8p,32a,8p,32a,16p,32g,16p,32a,8p,32g,16p,32f,16p,32g,8p,32g,16p,32f,16p,32d,16p,32f,16p,32d,8p,32a,8p,32a,16p,32g,16p,32a,8p,32g,16p,32f,16p,32g,8p,32g,16p,32f,16p,32d,16p,32f,8p";
char *Blue = "Blue1:d=4,o=6,b=63:16b,16d#,16g#,16b,16c#7,16f#,16a#,8b,16g#,16b,16d#7,16e7,16g#,16d#7,16c#7,16b,16d#,16g#,16b,16c#7,16f#,16a#,8b,16g#,16b,16d#7,16e7,16g#,16d#7,16c#7,16b,16d#,16g#,16b,16c#7,16f#,16a#,8b,16g#,16b,16d#7,16e7,16g#,16d#7,16c#7,16b,16d#,16g#,16b,16a#,16c#,16f#,8g#,16b5,16f#,8g#,16f#,16g#,16a#,16b,16d#,16g#,16b,16c#7,16f#,16a#,8b,16g#";
char *SlimShady = "TheRealS:d=4,o=5,b=100:16d,16p,16f,16p,16a,16p,16a#,16p,16d6,p,16a#,16p,16a,p,32p,16a#,16p,32a,32a#,32a,8g,16a,16p,16c#,16p,16d,16p,16f,16p,16a,16p,16a#,16p,16d6,p,16a#,16p,16a,p,32p,16a#,16p,32a,32a#,32a,8g,16a,16p,16c#,16p,16d";
char *WakeMeUp = "BringMeT:d=4,o=5,b=180:16d,16p,8p,16d,16p,8p,16d,16p,8p,16d,16p,8a6,16d,16p,8a6,16d,16p,8a6,16d,16p,8g6,16d,16p,g.6,16f,16p,8p,16f,16p,8p,16f,16p,8a6,16f,16p,8a6,16f,16p,8a6,16f,16p,8g6,16f,16p,g.6,16c,16p,8p,16c,16p,8p,16c,16p,8a#6,16c,16p,8p,a6,g6,f6,a#.6,8p,a.6,8p,g.6,8p,a.6,8p,8f6,8e6,2d6";
char *ThomasTank = "ThomasTh:d=4,o=6,b=285:8c,8p,8d,8p,8e,8p,2f,g,2a,2c#,a4,p,a4,p,a4,p,16c#,8d.,a#5,d,c,p,c5,p,c5,16c#,8d.,a#5,a#5,8d,c,c5,8b5,8c,8b5,8c,8p,c.,8p,c,c5,c5,8p,8b5,8c,8b5,8c,8p,c#.,8p,c#,c#5,c#5,g#5,a#5,b5,c,g#5,d#,d#5,a#5,c5,c,d#5,2c#,c#5,p,c#5,c#,c,b5,8a#5,8a#4,8a#5,8p,8c#,8a#4,8c#,8p,8f#,8a#4,8f#,a#.,a#5,8";
char *SweetChild = "SweetChi:d=8,o=5,b=140:c,c6,g,f,f6,g,e6,g,c,c6,g,f,f6,g,e6,g,d,c6,g,f,f6,g,e6,g,d,c6,g,f,f6,g,e6,g,f,c6,g,f,f6,g,e6,g,f,c6,g,f,f6,g,e6,g,c,c6,g,f,f6,g,e6,g,c,c6,g,f,f6,g,e6,g";

// LIST D
char *LastResort = "LastReso:d=4,o=5,b=100:16e,16g,16f#,16g,16b,16g,16f#,16g,16g,16g,16f#,16g,16b,16g,16f#,16g,16c,16g,16f#,16g,16b,16g,16f#,16g,16b,16g,16f#,16g,16a,16g,16f#,16g,16e,16g,16f#,16g,16b,16g,16f#,16g,16d,16g,16f#,16g,16b,16g,16f#,16g,16c,16g";
char *Pokemon = "Pokeman:d=16,o=6,b=112:f5,a#5,c,c#,c,c#,d#,2f,a#5,c,8c#,8f,8d#,32c#,32d#,32p,32c#,8c,8g#.5,f5,a#5,c,c#,c,c#,d#,2f,8a#5,c#,8f,a5,d#,4g#";
char *HipsDontLie = "HipsDon':d=4,o=5,b=100:c6,8a#,16c6,16a#,16p,16a#,16a#,16a#,8g,8a#,8g,8g,16f,16f,16g,16f,16p,16d#,8c,8p,16c,16c,8d#,8c,8p,16p,16c,8d#,8c,8p,16c,16c,8d#,16c,16c,16d#,8c,16c,8d#,8c,p,16p,16c6,16c6,16c6,8a#,16c6,16a#,16p,16a#,16a#,16a#,8g,8a#,8g,8g,16f,16f,16g,16f,16p,16d#,8c,8p,16c,16c,8d#,8c,8p,16p,16c,8d#,8c,8p,16c,16c,8d#,16c,16c,16d#,8c,16c,8d#,8c";
char *InTooDeep = "InTooDee:d=16,o=5,b=125:8b,8c#6,4e6,8f#6,4e6,8b,8c#6,4e6,4f#6,4g#6,8b,8f#6,4e6,8b,8f#6,4e6,4f#6,4g#6,8a6,8g#6,8e6,8f#6,8e6,8b,8c#6,4e6,8f#6,4e6,8b,8c#6,4e6,4f#6,4g#6,8b,8f#6,4e6,8b,8f#6,4e6,4f#6,4g#6,8a6,8g#6,8e6,8f#6,8e6,8f#6,4e6";
char *SayItAintSo = "SayItAin:d=32,o=6,b=320:2c#.,1g#,2g#5,4d#,4g#,4c7,4b,2a.5,2a.,1g#,2e,8f#.,4g#,2b,2c#.,1g#,2g#5,4d#,4g#,4c7,4b,2a.5,2a.,1g#,2e,8f#.,4g#,4b.";
char *Creep = "Creep:d=8,o=5,b=80:32p,32g#.,16g#.,4c.6,2c6,32g#.,16g#.,c.6,c.6,4g,16f,2e,16c.6,32c.6,16c#.6,16c.6,32c.6,16a#.,2c6,16g#.,16a#.,16g#.,b.,1g#";


void setup(){
   Serial.begin(9600);
   //LCD Setup
   lcd.init(); // initialize the LCD
   lcd.backlight(); // turns backlight on
   // Piezo Setup
   pinMode(spkPin, OUTPUT);
   // RTTTL SETUP
   tone1.begin(spkPin);
   // MAIN MENU
   main_menu();
}
// RTTL SONG PLAYING METHOD
#define isdigit(n) (n >= '0' && n <= '9')

void play_rtttl(char *p)
{
  // Absolutely no error checking in here

  byte default_dur = 4;
  byte default_oct = 6;
  int bpm = 63;
  int num;
  long wholenote;
  long duration;
  byte note;
  byte scale;

  // format: d=N,o=N,b=NNN:
  // find the start (skip name, etc)

  while(*p != ':') p++;    // ignore name
  p++;                     // skip ':'

  // get default duration
  if(*p == 'd')
  {
    p++; p++;              // skip "d="
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    if(num > 0) default_dur = num;
    p++;                   // skip comma
  }


  // get default octave
  if(*p == 'o')
  {
    p++; p++;              // skip "o="
    num = *p++ - '0';
    if(num >= 3 && num <=7) default_oct = num;
    p++;                   // skip comma
  }


  // get BPM
  if(*p == 'b')
  {
    p++; p++;              // skip "b="
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    bpm = num;
    p++;                   // skip colon
  }


  // BPM usually expresses the number of quarter notes per minute
  wholenote = (60 * 1000L / bpm) * 4;  // this is the time for whole note (in milliseconds)



  // now begin note loop
  while(*p)
  {
    // first, get note duration, if available
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    
    if(num) duration = wholenote / num;
    else duration = wholenote / default_dur;  // we will need to check if we are a dotted note after

    // now get the note
    note = 0;

    switch(*p)
    {
      case 'c':
        note = 1;
        break;
      case 'd':
        note = 3;
        break;
      case 'e':
        note = 5;
        break;
      case 'f':
        note = 6;
        break;
      case 'g':
        note = 8;
        break;
      case 'a':
        note = 10;
        break;
      case 'b':
        note = 12;
        break;
      case 'p':
      default:
        note = 0;
    }
    p++;

    // now, get optional '#' sharp
    if(*p == '#')
    {
      note++;
      p++;
    }

    // now, get optional '.' dotted note
    if(*p == '.')
    {
      duration += duration/2;
      p++;
    }
  
    // now, get scale
    if(isdigit(*p))
    {
      scale = *p - '0';
      p++;
    }
    else
    {
      scale = default_oct;
    }

    scale += OCTAVE_OFFSET;

    if(*p == ',')
      p++;       // skip comma for next note (or we may be at the end)

    // now play the note

    if(note)
    {
      tone1.play(notes[(scale - 4) * 12 + note]);
      delay(duration);
      tone1.stop();
    }
    else
    {
      delay(duration);
    }
  }
}

//Song Mode
void menu_mode(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Welcome to");
  lcd.setCursor(0,1);
  lcd.print("MP3 Mode");
  delay(2000);
  menu_mode_run = LOW;
}

// MAIN MENU
void main_menu(){
  tone1.stop();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Welcome to");
  lcd.setCursor(0,1);
  lcd.print("Keypad MP3");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Press '*'");
  lcd.setCursor(0,1);
  lcd.print("for Piano Mode");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Press '#'");
  lcd.setCursor(0,1);
  lcd.print("for MP3 Mode");  
  delay(3000);
}
// SONG LIST

void song_listA(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you drew the song list
    previousMillis = currentMillis;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Song List:");
    lcd.setCursor(0,1);
    lcd.print(songlistA[i]);
    i++;
  }
  if (i>9){
    i = 0;
  } 
}
void song_listB(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you drew the song list
    previousMillis = currentMillis;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Song List:");
    lcd.setCursor(0,1);
    lcd.print(songlistB[i]);
    i++;
  }
  if (i>8){
    i = 0;
  } 
}
void song_listC(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you drew the song list
    previousMillis = currentMillis;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Song List:");
    lcd.setCursor(0,1);
    lcd.print(songlistC[i]);
    i++;
  }
  if (i>7){
    i = 0;
  } 
}
void song_listD(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you drew the song list
    previousMillis = currentMillis;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Song List:");
    lcd.setCursor(0,1);
    lcd.print(songlistD[i]);
    i++;
  }
  if (i>6){
    i = 0;
  } 
}
void loop(void){
  char key = keypad.getKey();
  if (key == '*' && menuMode == LOW){
    pianoMode = !pianoMode;
    tone1.stop();
    lcd.clear();
  }
  if (key == '#' && pianoMode == LOW){
    menuMode = !menuMode;
    lcd.clear();
  }
  else if (menuMode == LOW && pianoMode == LOW){
    lcd.setCursor(0,0);
    lcd.print("Piano Mode: '*'");
    lcd.setCursor(0,1);
    lcd.print("MP3 Mode: '#'");
  }
  
  // PIANO MODE
  if (pianoMode == HIGH){
    lcd.setCursor(0,0);
    lcd.print("Piano Mode");
    lcd.setCursor(0,1);
    lcd.print("Press * to exit");
    if (key == '1' && keypad.getState() == PRESSED){
      tone1.play(261.63);
    }
    if (key == '2' && keypad.getState() == PRESSED){
      tone1.play(293.66);
    }
    if (key == '3' && keypad.getState() == PRESSED){
      tone1.play(329.63);
    }
    if (key == '4' && keypad.getState() == PRESSED){
      tone1.play(349.23);
    }
    if (key == '5' && keypad.getState() == PRESSED){
      tone1.play(392.00);
    }
    if (key == '6' && keypad.getState() == PRESSED){
      tone1.play(440.00);
    }
    if (key == '7' && keypad.getState() == PRESSED){
      tone1.play(493.88);
    }
    if (key == '8' && keypad.getState() == PRESSED){
      tone1.play(523.25);
    }
    if (key == '0' && keypad.getState() == PRESSED){
      tone1.stop();
    }
  }
  
  // MENU MODE
  if (menuMode == HIGH){
    if (menu_mode_run == HIGH){
      menu_mode();
      menu_mode_run = LOW;
    }
    else if (menu_mode_run == LOW && lib_A == HIGH){
      song_listA();
    }
    else if (menu_mode_run == LOW && lib_B == HIGH){
      song_listB();
    }
    else if (menu_mode_run == LOW && lib_C == HIGH){
      song_listC();
    }
    else if (menu_mode_run == LOW && lib_D == HIGH){
      song_listD();
    }
    else{
      lcd.setCursor(0,0);
      lcd.print("Press A,B,C Or D");
      lcd.setCursor(0,1);
      lcd.print("Press # to Exit");
    }
    if (key == 'A' && lib_B == LOW && lib_C == LOW && lib_D == LOW && lib_selected == LOW){
      lib_A = HIGH;
      lib_selected = HIGH;
      i = 0;
    }  
    if (key == 'B' && lib_A == LOW && lib_C == LOW && lib_D == LOW && lib_selected == LOW){
      lib_B = HIGH;
      lib_selected = HIGH;
      i = 0;
    }  
    if (key == 'C' && lib_A == LOW && lib_B == LOW && lib_D == LOW && lib_selected == LOW){
      lib_C = HIGH;
      lib_selected = HIGH;
      i = 0;
    }  
    if (key == 'D' && lib_A == LOW && lib_B == LOW && lib_C == LOW && lib_selected == LOW){
      lib_D = HIGH;
      lib_selected = HIGH;
      i = 0;
    }
    if (key == '0' && lib_selected == HIGH){
      lib_A = LOW;
      lib_B = LOW;
      lib_C = LOW;
      lib_D = LOW;
      lib_selected = LOW;
      lcd.clear();
    }
    Serial.println(lib_A);
    // SONG BANK A
    if (key == '1' && lib_A == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("The Simpsons");
      play_rtttl(simpsons);
      lcd.clear();
    }
    if (key == '2'&& lib_A == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("Indiana Jones");
      play_rtttl(indiana);
      lcd.clear();
    }
    if (key == '3'&& lib_A == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("Take on Me");
      play_rtttl(take_on_me);
      lcd.clear();
    }
    if (key == '4'&& lib_A == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("The Entertainer");
      play_rtttl(entertainer);
      lcd.clear();
    }
    if (key == '5'&& lib_A == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("Tom Cruise MI");
      play_rtttl(mission_imp);
      lcd.clear();
    }
    if (key == '6'&& lib_A == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("X-Files");
      play_rtttl(xfiles);
      lcd.clear();
    }
    
    if (key == '7'&& lib_A == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("20th Fox");
      play_rtttl(fox);
      lcd.clear();
    }
    if (key == '8'&& lib_A == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("Barbie Girl");
      play_rtttl(barbie_girl);
      lcd.clear();
    }
    if (key == '9'&& lib_A == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("Star Wars");
      play_rtttl(star_wars);
      lcd.clear();
    }
    // SONG BANK B
    if (key == '1' && lib_B == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("National Anthem");
      play_rtttl(USA_Anthem);
      lcd.clear();
    }
    if (key == '2'&& lib_B == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("Gal From Ipanema");
      play_rtttl(Ipanema);
      lcd.clear();
    }
    if (key == '3'&& lib_B == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("Oh Canada");
      play_rtttl(OHCanada);
      lcd.clear();
    }
    if (key == '4'&& lib_B == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("All Star");
      play_rtttl(Allstar);
      lcd.clear();
    }
    if (key == '5'&& lib_B == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("Lose Yourself");
      play_rtttl(LoseYourself);
      lcd.clear();
    }
    if (key == '6'&& lib_B == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("1 2 Step");
      play_rtttl(Ciara);
      lcd.clear();
    }
    if (key == '7'&& lib_B == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("ND Fight Song");
      play_rtttl(NDFightSong);
      lcd.clear();
    }
    if (key == '8'&& lib_B == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("Olympic Theme");
      play_rtttl(OlympicTheme);
      lcd.clear();
    }
    // SONG BANK C
    if (key == '1' && lib_C == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("Sandstorm");
      play_rtttl(Sandstorm);
      lcd.clear();
    }
    if (key == '2'&& lib_C == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("The Next Episode");
      play_rtttl(NextEpisode);
      lcd.clear();
    }
    if (key == '3'&& lib_C == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("I'm Blue");
      play_rtttl(Blue);
      lcd.clear();
    }
    if (key == '4'&& lib_C == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("TheRealSlimShady");
      play_rtttl(SlimShady);
      lcd.clear();
    }
    if (key == '5'&& lib_C == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("Wake Me Up");
      play_rtttl(WakeMeUp);
      lcd.clear();
    }
    
    if (key == '6'&& lib_C == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("Thomas the Tank");
      play_rtttl(ThomasTank);
      lcd.clear();
    }
    if (key == '7'&& lib_C == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("SweetChildOfMine");
      play_rtttl(SweetChild);
      lcd.clear();
    }
    // SONG BANK D
    if (key == '1' && lib_D == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("Last Resort");
      play_rtttl(LastResort);
      lcd.clear();
    }
    if (key == '2'&& lib_D == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("Pokemon");
      play_rtttl(Pokemon);
      lcd.clear();
    }
    if (key == '3'&& lib_D == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("Hips Don't Lie");
      play_rtttl(HipsDontLie);
      lcd.clear();
    }
    
    if (key == '4'&& lib_D == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("In Too Deep");
      play_rtttl(InTooDeep);
      lcd.clear();
    }
    if (key == '5'&& lib_D == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("Say It Ain't So");
      play_rtttl(SayItAintSo);
      lcd.clear();
    }
    if (key == '6'&& lib_D == HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Playing");
      lcd.setCursor(0,1);
      lcd.print("Creep");
      play_rtttl(Creep);
      lcd.clear();
    }
    
  }  
}