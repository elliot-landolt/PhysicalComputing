// A fun sketch to demonstrate the use of the Tone library.

// To mix the output of the signals to output to a small speaker (i.e. 8 Ohms or higher),
// simply use 1K Ohm resistors from each output pin and tie them together at the speaker.
// Don't forget to connect the other side of the speaker to ground!

// You can get more RTTTL (RingTone Text Transfer Language) songs from
// http://merwin.bespin.org/db/rts/index.php

#include <Tone.h>

Tone tone1;

#define OCTAVE_OFFSET 0

int notes[] = { 0,
NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4,
NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5,
NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6,
NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7
};

//char *simpsons = "The Simpsons:d=4,o=5,b=160:c.6,e6,f#6,8a6,g.6,e6,c6,8a,8f#,8f#,8f#,2g,8p,8p,8f#,8f#,8f#,8g,a#.,8c6,8c6,8c6,c6";
//char *indiana = "Indiana:d=4,o=5,b=250:e,8p,8f,8g,8p,1c6,8p.,d,8p,8e,1f,p.,g,8p,8a,8b,8p,1f6,p,a,8p,8b,2c6,2d6,2e6,e,8p,8f,8g,8p,1c6,p,d6,8p,8e6,1f.6,g,8p,8g,e.6,8p,d6,8p,8g,e.6,8p,d6,8p,8g,f.6,8p,e6,8p,8d6,2c6";
//char *take_on_me = "TakeOnMe:d=4,o=4,b=160:8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5,8f#5,8e5,8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5";
//char *entertainer = "Entertainer:d=4,o=5,b=140:8d,8d#,8e,c6,8e,c6,8e,2c.6,8c6,8d6,8d#6,8e6,8c6,8d6,e6,8b,d6,2c6,p,8d,8d#,8e,c6,8e,c6,8e,2c.6,8p,8a,8g,8f#,8a,8c6,e6,8d6,8c6,8a,2d6";
char *muppets = "Muppets:d=4,o=5,b=250:c6,c6,a,b,8a,b,g,p,c6,c6,a,8b,8a,8p,g.,p,e,e,g,f,8e,f,8c6,8c,8d,e,8e,8e,8p,8e,g,2p,c6,c6,a,b,8a,b,g,p,c6,c6,a,8b,a,g.,p,e,e,g,f,8e,f,8c6,8c,8d,e,8e,d,8d,c";
//char *xfiles = "Xfiles:d=4,o=5,b=125:e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,g6,f#6,e6,d6,e6,2b.,1p,g6,f#6,e6,d6,f#6,2b.,1p,e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,e6,2b.";
char *looney_tunes = "Looney:d=4,o=5,b=140:32p,c6,8f6,8e6,8d6,8c6,a.,8c6,8f6,8e6,8d6,8d#6,e.6,8e6,8e6,8c6,8d6,8c6,8e6,8c6,8d6,8a,8c6,8g,8a#,8a,8f";
//char *fox = "20thCenFox:d=16,o=5,b=140:b,8p,b,b,2b,p,c6,32p,b,32p,c6,32p,b,32p,c6,32p,b,8p,b,b,b,32p,b,32p,b,32p,b,32p,b,32p,b,32p,b,32p,g#,32p,a,32p,b,8p,b,b,2b,4p,8e,8g#,8b,1c#6,8f#,8a,8c#6,1e6,8a,8c#6,8e6,1e6,8b,8g#,8a,2b";
char *bond = "Bond:d=4,o=5,b=80:32p,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d#6,16d#6,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d6,16c#6,16c#7,c.7,16g#6,16f#6,g#.6";
//char *star_wars = "StarWars:d=4,o=5,b=45:32p,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#.6,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#6";
char *top_gun = "TopGun:d=4,o=4,b=31:32p,16c#,16g#,16g#,32f#,32f,32f#,32f,16d#,16d#,32c#,32d#,16f,32d#,32f,16f#,32f,32c#,16f,d#,16c#,16g#,16g#,32f#,32f,32f#,32f,16d#,16d#,32c#,32d#,16f,32d#,32f,16f#,32f,32c#,g#";
char *a_team = "A-Team:d=8,o=5,b=125:4d#6,a#,2d#6,16p,g#,4a#,4d#.,p,16g,16a#,d#6,a#,f6,2d#6,16p,c#.6,16c6,16a#,g#.,2a#";
char *flintstones = "Flinstones:d=4,o=5,b=40:32p,16f6,16a#,16a#6,32g6,16f6,16a#.,16f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c6,d6,16f6,16a#.,16a#6,32g6,16f6,16a#.,32f6,32f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c6,a#,16a6,16d.6,16a#6,32a6,32a6,32g6,32f#6,32a6,8g6,16g6,16c.6,32a6,32a6,32g6,32g6,32f6,32e6,32g6,8f6,16f6,16a#.,16a#6,32g6,16f6,16a#.,16f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c.6,32d6,32d#6,32f6,16a#,16c.6,32d6,32d#6,32f6,16a#6,16c7,8a#.6";
char *jeopardy = "Jeopardy:d=4,o=6,b=125:c,f,c,f5,c,f,2c,c,f,c,f,a.,8g,8f,8e,8d,8c#,c,f,c,f5,c,f,2c,f.,8d,c,a#5,a5,g5,f5,p,d#,g#,d#,g#5,d#,g#,2d#,d#,g#,d#,g#,c.7,8a#,8g#,8g,8f,8e,d#,g#,d#,g#5,d#,g#,2d#,g#.,8f,d#,c#,c,p,a#5,p,g#.5,d#,g#";
char *smurfs = "Smurfs:d=32,o=5,b=200:4c#6,16p,4f#6,p,16c#6,p,8d#6,p,8b,p,4g#,16p,4c#6,p,16a#,p,8f#,p,8a#,p,4g#,4p,g#,p,a#,p,b,p,c6,p,4c#6,16p,4f#6,p,16c#6,p,8d#6,p,8b,p,4g#,16p,4c#6,p,16a#,p,8b,p,8f,p,4f#";
//char *mission_imp = "MissionImp:d=16,o=6,b=95:32d,32d#,32d,32d#,32d,32d#,32d,32d#,32d,32d,32d#,32e,32f,32f#,32g,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,a#,g,2d,32p,a#,g,2c#,32p,a#,g,2c,a#5,8c,2p,32p,a#5,g5,2f#,32p,a#5,g5,2f,32p,a#5,g5,2e,d#,8d";
char *sax = "Yaketysax:d=4,o=5,b=125:8d.,16e,8g,8g,16e,16d,16a4,16b4,16d,16b4,8e,16d,16b4,16a4,16b4,8a4,16a4,16a#4,16b4,16d,16e,16d,g,p,16d,16e,16d,8g,8g,16e,16d,16a4,16b4,16d,16b4,8e,16d,16b4,16a4,16b4,8d,16d,16d,16f#,16a,8f,d,p,16d,16e,16d,8g,16g,16g,8g,16g,16g,8g,8g,16e,8e.,8c,8c,8c,8c,16e,16g,16a,16g,16a#,8g,16a,16b,16a#,16b,16a,16b,8d6,16a,16b,16d6,8b,8g,8d,16e6,16b,16b,16d,8a,8g,g;";
char *ymca = "YMCA:d=4,o=5,b=160:8c#6,8a#,2p,8a#,8g#,8f#,8g#,8a#,c#6,8a#,c#6,8d#6,8a#,2p,8a#,8g#,8f#,8g#,8a#,c#6,8a#,c#6,8d#6,8b,2p,8b,8a#,8g#,8a#,8b,d#6,8f#6,d#6,f.6,d#.6,c#.6,b.,a#,g#";
//char *barbie_girl = "BarbieGirl:d=4,o=5,b=125:8g#,8e,8g#,8c#6,a,p,8f#,8d#,8f#,8b,g#,8f#,8e,p,8e,8c#,f#,c#,p,8f#,8e,g#,f#";
char *twinkle = "Twinkle:d=4,o=5,b=60:16c#6,16c#6,16g#6,16g#6,16a#6,16a#6,16g#6,16p,16f#6,16f#6,16e#6,16e#6,16d#6,8c#6,16p,16g#6,16g#6,16f#6,16f#6,16e#6,16e#6,8d#6,16p,16g#6,16f#6,16f#6,16e#6,16e#6,8d#6,16p,16c#6,16c#6,16g#6,16g#6,16a#6,16g#6,16p,16f#6,16f#6,16e#6,16e#6,16d#6,16d#6,8c#6";
char *Ipanema ="GirlFromIpane:d=4,o=5,b=160:g.,8e,8e,d,g.,8e,e,8e,8d,g.,e,e,8d,g,8g,8e,e,8e,8d,f,d,d,8d,8c,e,c,c,8c,a#4,2c";
char *Wonka = "Willy Wonk:d=4,o=5,b=120:86c,172g#,172p,86c#,172a,172p,86d,43p,172c,43p,172d#,172c#,172p,172c6,57p,57p,172d#6,57p,43c,57p,16p,16p,16p,172b,172e4,57b4,43p,57c,57a,172f#,172p,57p,57p,43p,172g#,86d#,86g#4,17p,86d#,172g#,16p.,16p.,16p.,86g#,172b,57p,57p,43p,86b,16p.,57g#,p.,2p,2p,2p,172g6,172p,86c,86p,86p,86p,86p,57p,57p,25p,43g#,86p,57b,86p,172b,57d#,29p,172e,86a4,86p,25f,19p,14p,172f,86d,172g4,8p,172c6,57a,29p,57d#,17p,86c#,172a,172p,172f,43p,43p,86a#,86c#,2p,172a,86f,8p.,172a,172p,32p.,19d#7,10p,6p,172a#4,172d#6,172p,172g,172b3,86p,57p,43p,34p,29p,86a#2,86p,86a#4,34a#2,9d#6,10d#8,34p,7p,7p,7p,6p,172c3,57p,172b2,172a#3,86p,57p,57p,57c7,8p.,43d7,19g#,29d#7,86p,19p,19p,17p,16p,14p,172d#3,172p,172c3,57p,34p,172g4,172d#6,86p,172f3,86p,43p,17d#3,17d#6,172p,86d#3,172p,86d#6,172d#7,43g,43d#8,86d7,172p,172g,14p,13p,12p,172g3,172p,86p,57p,43p,43p,172d#4,172f3,86p,57p,57e3,34p,7f,57d#7,57b,86p,172f,172g#6,172p,172p,86c8,172d#7,12p,10p,9p,9p,8p,7p,7p,172a#4,172p,172d#4,43p,172g,172p,172d#6,86p,86p,57p,57p,57p,172c6,172p,86p,57p,43p,34p,34p,172g7,172g6,10p,17d#7,17d#.8,10p,172g6,172g#7,172g#6,86p,86p,86p,86p,57p,34p,29p,29p,172d#4,86p,34p,172g6,172p,172a2,172c4,172p,172p,172g#,172p,172d7,57p,29p,86g6";
char *USA_Anthem = "UnitedSt:d=4,o=5,b=130:32p,8g.,16e,c,e,g,2c6,8e6.,16d6,c6,e,f#,2g,g,e6.,8d6,c6,2h,8a.,16h,c6,c6,g,e,c";
char *cent = "P.I.M.P:d=4,o=6,b=160:8d_,8d_,8d_,f_,8f_,f_,8f,d_,a_5,p,8p,8d_,8d_,8d_,f_,8f_,f_,8f,d_,f,p,8p,8f,8f,8f,g_,8g_,g_,8f_,f,a_5,p,8p,8f,8f,8f,8g_,8g_,8g_,8g_,8g_,8f_,f,d_";
char *cent2 = "InDaClub:d=4,o=5,b=160:d#6,16d,16p,8d6,p,16d,16p,16d,16p,p,16d,16p,16d,16p,p,16d,16p,16d,16p,d6,16d#,16p,8d#6,p,16d#,16p,16d#,16p,c6,16c,16p,8d6,p,16c,16p,16c,16p,d#6,16d,16p,8d6,p,16d,16p,16d,16p,p,16d,16p,16d,16p,p,16d,16p,16d,16p,d6,16d#,16p,8d#6,p,16d#,16p,16d#,16p,c6,16c,16p,8d6,p,16c,16p,16c,16p";
char *kanye = "GoldDigg:d=4,o=5,b=180:g,c6,8c6,c6,8d#6,1p,g,c6,8a#,c6,8a#,8g,8d#,c,2p,g,c6,8c6,c.6,d#6,2p,p,g,c6,8a#,c6,8a#,8g,8d#,c,2p,8p,c.,8d#,8c,f,8d#,8c,2p,p,8p,c.,8d#,8c,f,8d#,8c,2p,p,8p,c.,8d#,8c,f,8d#,8c,2p,p,8p,c.,8d#,8c,f,8d#,8c";
char *weezer = "SayItAin:d=32,o=6,b=320:2c#.,1g#,2g#5,4d#,4g#,4c7,4b,2a.5,2a.,1g#,2e,8f#.,4g#,2b,2c#.,1g#,2g#5,4d#,4g#,4c7,4b,2a.5,2a.,1g#,2e,8f#.,4g#,4b.";
char *fire = "RingOfFi:d=16,o=6,b=56:4d#,32d#,32d#,f,c#,4d#,8p,8d#,8g,8a#,32a#,a#.,32g#,8g#,g#,g#,f,8d#,32c,c#,8d#,8g,8a#,32g,g.,8g#,8g#,f,8d#,32c,c,8g#5,8c,4d#,c,c#,a#5,c,4d#,g#5,a#5,g5,8g#5";
char *roads = "CountryR:d=4,o=6,b=225:1c#.,8c#,8b5,a5,1b.,c#,b5,1a.,c#,e,1f#.,f#,f#,e,1c#.,8c#,8b5,a5,b5,1c#.,8c#,8b5,a5,1a.,a5,b5,1a.,p,8c#,8b5,a5,1b.,8c#,8b5,a5,1a.,8c#,8b5,a5,1b.,8c#";
char *fins = "Finns:d=1,o=6,b=160:8d,p,8d,8p,8e,f,p,f#,4p,8f#,p,8f#,p,8f,8p,e,p,d,4p,8d,p,8d,p,8e,p,f,p,f#,4p,c,p,b5,p,a5,p,f#,p,8b5,8p,a5,p,d#,e,8f,p,8e,p,a5,p,8d,p,8d,p,8e,8p,8f,p,f#,4p,8f#,p,8f#,p,8f,p,e,p,d,4p,8d,p,8d,8p,8e,p,f,p,8f#,4p,b5,c,p,f#,a5,p,8b.5,8p,a5,p,e,8f,p,e,p,d,p,c5,c5,c5,c5,c5,c5,8a5,8p,b5,p,2";
char *jimi = "AllAlong:d=16,o=5,b=140:8b,16a,p.,16b,p.,8p,b,8p.,8d6.,p,16a,p.,b,p,2p.,8a,b,p,16d6,p.,p.,8b,8b,8b,2p,8b,16a,p.,b,p,8a,d6,8p.,8b,4p,2p.,8a,b,p,16d6,4p,p.,8b,4b";
char *toxic = "Toxic:d=4,o=5,b=140:8f,8g#,c6,8a#,8g#,g#,f,8d#,8c#,2g#.,p,a#,f,a#,f,8a#,8a#,f,8f,8g#,c6,8a#,8g#,g#,f,8d#,8c#,2g#,8c#,8d#,e,8d#,8c#,c#,8c#,8d#,e,8d#,8c#,d#,e,p,2p,8f,8g#,c6,8a#,8g#,g#,f,8d#,8c#,2g#.,p,a#,f,a#,f,8a#,8a#,f,8f,8g#,c6,8a#,8g#,g#,f,8d#,8c#,2g#,8c#,8d#,e,8d#,8c#,c#,8c#,8d#,e,8d#,8c#,d#,e";
char *peas = "Let'sGet:d=4,o=6,b=100:16f_7,16p,16f_7,16p,16f_7,16p,8f_7,8d7,8b,8d7,8p,16f_7,16p,16f_7,16p,16f_7,16p,8f_7,8d7,8g7,8f_7,8p,16f_7,16p,16f_7,16p,16f_7,16p,8f_7,8d7,8b,8d7,8p,16f_7,16p,16f_7,16p,16f_7,16p,8f_7,8d7,8g7,8f_7,8p";
char *canada = "OhCanada:d=4,o=5,b=100:2g,a#,8p,8a#,2d#,p,f,g,g#,a#,c6,2f,2p,2g,a,8p,8a,2a#,p,c6,2d6,2c6,1a#";
char *ussr = "Unknown:d=4,o=5,b=100:8g#6,16p,8c#7,16p,8g#6,16a#6,8a#6,16p,8e#6,16e#6,8a#6,16p,16g#6,8g#6,16p,8c#6,16c#6,8d#6,16p,8d#6,16e#6,8f#6,16p,8f#6,8g#6,16p,8g#6,16c#7,8d#7,8p";
char *moonlight = "DancingI:d=4,o=5,b=140:g,8f,g,8p,8g,8f,g,f,a,g,g,f,a.,8g,2f,a,8g,8g,8f,f,a.,8g,8f,g,f,a,g,g,f,f,d,d,f,a.,8g,g,8f,g,8p,8g,8f,g,f,a,g,g,f,a.,8g,2f";
char *tribute = "Tribute:d=16,o=5,b=100:a#,a#,8a#,8a#,8g#,4g#,4f#,8a#,8a#,8g#,8g#,4g#,4f#,8a#,8a#,8a#,8g#,4g#,4f#,8a#,8a#,8a#,8g#,4g#,4f#,a#,a#,8a#,8a#,8g#,4g#,4f#,8a#,8a#,8g#,8g#,4g#,4f#,8a#,8a#,8a#,8g#,4g#,4f#,8a#,8a#,8a#,8g#,4g#,4f#,a#,a#,8a#,8a#,8g#,4g#,4f#,8a#,8a#,8g#,8g#,4g#,4f#,8a#,8a#,8a#,8g#,4g#,4f#,8a#,8a#,8a#,8g#,4g#,4f#";
char *IronMan = "IronMan:d=4,o=5,b=100:8c#6,8p,8d#6,8p,8d#6,8f#6,8f#6,8p,16g#6,16g#6,16g#6,16g#6,8g#6,8d#6,8f#6,8f#6";
char *Venga = "WeLikeTo:d=32,o=6,b=40:16c#7,a#,g#,16c#7,a#,g#.,c#7,a#,g#,c#7.,a#,g#,c7.,d#7.,c7.,g#,c7.,c7,d#7,d#7,c7.,a#,g#,c#7.,a#,g#,c#7.,a#,g#.,c#7,a#,g#,c#7.,a#,g#,c7.,d#7.,c7.,a#,16g#,g#,f#,g#,f#,g#,f,f,g#,f#,g#,f#,g#,f,f,f,f#,f,f#,f,g#,g#,f,f#,f#,f#,f,g#,g#,g#,f#,g#,f#,g#,f,f,g#,f#,g#,f#,g#,f,f,f,f#,f,f#,f,g#,g#,f,f#,f#,f#,f,g#,g#";
char *USA = "Usa:d=4,o=6,b=90:8g.5,16e5,c5,e5,g5,2c,8e.,16d,c,e5,f_5,2g5,8g5,8g5,e.,8d,c,2b5,8a5,8b5,c,c,g5,e5,c5,8g.5,16e5,c5,e5,g5,2c,8e.,16d,c,e5,f_5,2g5,8g5,8g5,e.,8d,c,2b5,8a5,8b5,c,c,g5,2c.5";
char *Tokyo = "Theme:d=4,o=6,b=80:16d_5,16f_5,16g_5,16f_5,16g_5,16a_5,16b5,16a_5,16b5,16c_,8d_,16d_,16d_,16f_,8d_.,16p,8g_,16f_,16d_,8f_.,16d_,16c_,16b5,8g_5,16f_.5,32p,16d_5,16f_5,16g_5,16f_5,16g_5,16a_5,16b5,16a_5,16b5,16c_,8d_,16d_,16f_,8d_.,16p,8g_,16f_,16d_,8f_.,16d_,16c_,16b5,8g_5,16f_.5,32p";
char *Wii = "Wii:d=4,o=5,b=80:129d6.,32p.,128p,172e6,32p.,128p,8f6.,172e6,172a3,8p.,32p,172d6,57g3,16p,65c6.,8p,64p,65e6.,172f6,64p,129f#6.,128p,64p,172g6,1p,16p.,64p.,129b.,4p.,16p.,64p,57c6,8p.,32p,128p.,57c6";
char *Sponge = "Sponge:d=4,o=5,b=80:c6,a,g,e,c6,a,g,e,c6,a,g,e,8g.,16g,2a,b,2c6,2p,c6,a,g,e,c6,a,g,e,c6,a,g,e,8g.,16g,2a,b,2c6,2p,c6,a,g,e,c6,a,g,e,c6,a,g,e,8g.,16g,2a,b,2c6,2p,c6,a,g,e,c6,a,g,e,c6,a,g,e,8g.,16g,2a,b,2c6";


void setup(void)
{
  Serial.begin(9600);
  tone1.begin(10);
  pinMode(10, OUTPUT);
}

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

void loop(void)
{
  play_rtttl(Sponge);
  while(1);
}