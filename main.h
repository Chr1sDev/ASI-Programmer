#include "stdint.h"
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"
#include "TouchScreen.h"
#include "bitmaps.h"

// Fonts
#include <Fonts/FreeSans12pt7b.h>
#define NUMPAD_TEXT_SIZE 1
#define INPUT_BOX_TEXT_SIZE 2
#define NUMPAD_PADDING_WIDTH -5
#define NUMPAD_PADDING_HEIGHT 10

// Pins for display
#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8
#define MIN_PRESSURE 10
#define MAX_PRESSURE 1000

// Pins for touch screen
#define YP A2
#define XM A3
#define YM 13
#define XP 12

// Touch screen boundaries
#define TS_MINX 150
#define TS_MAXX 840
#define TS_MINY 120
#define TS_MAXY 900

enum ButtonState
{
  Unpressed,
  Pressed
};

int xpos, ypos = {0};

typedef struct View
{
  int16_t height;
  int16_t width;
  int anchor[2];
  ButtonState state;
} view;

typedef struct NumPad
{
  View buttons[12];
  int buttonCount;
  int number;       // 0-30
  const char *mode; // a/b/O
} numpad;

static NumPad numbers = {0};
static View inputBox = {0};

// Button state (0 = No Button Pressed, 1 = Button One Pressed, 2 = Button Two Pressed...)
static int state = 0;

static boolean aButtonIsPressed = false;

static boolean buttoneOnePressed = false;

void mapTouchWithRotation(TSPoint point);
void checkButtonState(int state);

void buttonDepress(int button);
unsigned changeNumber(unsigned number);
void changeMode(const char *mode);

// Number helpers
int getNumberLength(int x);
unsigned concatenate(unsigned x, unsigned y);

// Graphics Helpers
void clearInputbox();
void clearInputNumbers();
void clearInputMode();