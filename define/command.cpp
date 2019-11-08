// command.cpp
#include "ascii.cpp"

#define SHIPS_MAX 10
int SHIPS_LENS[] = {4,3,3,2,2,2,1,1,1,1};
int navi_affondate[2] = {0,0};
// DRAW_COMMAND
#define nTURNO_GIOCATORE 1
#define nVITTORIA_GIOCATORE 2
#define nGIOCATORE_COLPISCE_GIOCATORE 3
#define nGIOCATORE_AFFONDA_GIOCATORE 4
#define nGIOCATORE_ACQUA 5
#define nGIOCATORE_AFFONDA1_GIOCATORE 6
#define nGIOCATORE_RISPARA 7

#define EMPTY 0
#define NIGH 2
#define TAKEN 1

#define LAUNCHER 3001
#define SERVER 3002
#define CLIENT 3003

// DIR
#define HORIZONTAL 1
#define VERTICAL 0
#define NONE 2

// CLIENTS
#define nPLAYER_1 0
#define nPLAYER_2 1


// CHAR TO SEND
char cWATER = '0';
char cSHOT = '1';
char cSUNK = '2';
char cSHIP_1 = '3';
char cFAKE = '4';
#define NO_RECV 7612

// COORD
#define sX_TOT 78
#define sY_TOT 62
#define sY_TOT_LAUNCHER 50
#define sX_CENTER 39
#define sY_CENTER 31
#define sY_CENTER_LAUNCHER 25
#define sMRG 3

//MENU
#define mSTART 0
#define mSERVER 1
#define mINFO 2
#define mEXIT 3

//PIXELS
#define pLAUNCHER_X 700
#define pLAUNCHER_Y 380

#define pCLIENT_X 700
#define pCLIENT_Y 820

#define pSERVER_X 700
#define pSERVER_Y 820

const int pCENTER_X = GetSystemMetrics(SM_CXSCREEN)/2;
const int pCENTER_Y = 100;

const int pLAUNCHER_START_X = pCENTER_X-pLAUNCHER_X/2;
const int pCLIENT_START_X = pCENTER_X-pCLIENT_X/2;
const int pSERVER_START_X = pCENTER_X-pSERVER_X/2;

const int pLAUNCHER_END_X = pLAUNCHER_START_X + pLAUNCHER_X;
const int pCLIENT_END_X = pCLIENT_START_X + pCLIENT_X;
const int pSERVER_END_X = pSERVER_START_X + pSERVER_X;

const int pLAUNCHER_END_Y = pCENTER_Y + pLAUNCHER_Y;
const int pCLIENT_END_Y = pCENTER_Y + pCLIENT_Y;
const int pSERVER_END_Y = pCENTER_Y + pSERVER_Y;

const int Y_START_MENU = 11;

