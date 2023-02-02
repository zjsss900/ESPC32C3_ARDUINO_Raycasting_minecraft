#include <TFT_eSPI.h>
#include "texture/mapTextures.c"
#include "texture/liewen.c"
#include "texture/chutou.c"
#include "texture/jntm.c"
#include "texture/badapple.c"


#define LCD_BUTTON_UP         5       //定义按钮针脚
#define LCD_BUTTON_L         13
#define LCD_BUTTON_R          8
#define LCD_BUTTON_CENTER     4
#define LCD_BUTTON_DOWN       9

#define screenWidth 160
#define screenHeight 80
#define mapWidth 24
#define mapHeight 24

#define blockup                1        // 按钮返回值定义
#define blockdown              2        //
#define blocklift              3        //
#define blockright             4        //
#define blockc                 5        //


int8_t worldMap[mapWidth][mapHeight] =
{
  {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7, 7, 7, 7, 7, 7, 7, 7},
  {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
  {4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
  {4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
  {4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
  {4, 0, 4, 0, 0, 0, 0, 9, 10, 10, 10, 10, 10, 10, 10, 10, 7, 7, 0, 7, 7, 7, 7, 7},
  {4, 0, 5, 0, 0, 0, 0, 9, 0, 10, 0, 10, 0, 10, 0, 10, 7, 0, 0, 0, 7, 7, 7, 1},
  {4, 0, 6, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 9, 7, 0, 0, 0, 0, 0, 0, 8},
  {4, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 1},
  {4, 0, 8, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 9, 7, 0, 0, 0, 0, 0, 0, 8},
  {4, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 9, 7, 0, 0, 0, 7, 7, 7, 1},
  {4, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 9, 9, 7, 7, 7, 7, 7, 7, 7, 1},
  {6, 6, 6, 6, 6, 14, 13, 12, 11, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10, 10},
  {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12},
  {6, 6, 6, 6, 6, 6, 0, 0, 6, 6, 0, 0, 0, 0, 9, 9, 9, 9, 10, 10, 11, 11, 11, 11},
  {4, 4, 4, 4, 4, 4, 0, 0, 4, 4, 1, 0, 0, 11, 9, 2, 2, 2, 2, 2, 3, 3, 3, 3},
  {4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 0, 11, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
  {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
  {4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 9, 0, 0, 10, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
  {4, 0, 14, 0, 15, 0, 0, 0, 0, 4, 9, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 2},
  {4, 0, 0, 15, 0, 0, 0, 0, 0, 4, 9, 0, 0, 10, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
  {4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 9, 0, 0, 10, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
  {4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 9, 0, 0, 10, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
  {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 10, 17, 16, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3}
};

void setup_buttons();
unsigned int down_up();

TFT_eSPI tft = TFT_eSPI(80, 160);


double posX = 22, posY = 12;
double dirX = -1, dirY = 0;
double planeX = 0, planeY = 1;
long nowFrame = 0, oldFrame = 0, t1 = 0, t2 = 0, t3 = 0,t4=0,t5=0;
uint16_t frameImage[screenWidth][screenHeight], ddd[screenWidth * screenHeight], mixTex[textureData / 2];
double fps=0;
double targetDistance = 0;
int8_t pitch = 0, targetMapX, targetMapY;
uint8_t stepTemp = 0, attackActoinGroup[4] = {0, 1, 0, 2}, attackTemp = 0,jntmFrame=0,badappleFrame=0;



void DRAW_BACKGROUND();

void wddd();

uint16_t CHANGE_SIDE_TEX_COLOR(uint16_t color);

void TRANSFOR_INT8_TO_INT16(uint8_t i);

void DO_MIX(uint8_t tex, int8_t lw);

void MIX_TOW_TEX(int8_t texNum);

void DRAW_TEX(int8_t texNum);

void WEAPONHIT();

void RAYCASTING();

void DRAW_WEAPONS_TO_SCREEN(int typeOfWeapon);

bool CHECK_MAP_SIDE();

void PLAY_JNTM(int8_t MapX, int8_t MapY);

void PLAY_BADAPPLE(int8_t texNum);

/*void PRINT_SOMETHING(){
  if(millis()+t1>=5000){
    t1=millis();
    Serial.print("targetDistance: ");
    Serial.println(targetDistance);
    Serial.println("    ");
  }
  }*/


void setup() {
  // put your setup code here, to run once:
  //Serial.begin(15200);
  tft.init();
  tft.setRotation(0);
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_BLACK);
  setup_buttons();
}

void loop() {
  // put your main code here, to run repeatedly:
  DRAW_BACKGROUND();
  RAYCASTING();
  DRAW_WEAPONS_TO_SCREEN(1);
  wddd();
  tft.pushImage(0, 0, 80, 160, ddd);
  //PRINT_SOMETHING();
}
