 #include <TFT_ILI9163C.h>

#include <Barricade.h>

TFT_ILI9163C display = TFT_ILI9163C(10,9);

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0  
#define WHITE   0xFFFF


int joyY = A0;
int joyX = A1;
int y, x;
int positionY = 0;
int positionX = 0;
int max_width = display.width(); // set chars that can be showed on your display
int max_height = 150; // set lines that your display have
int delayTime = 100 ;
Barricade listOfBarricade[6] = {Barricade(0, 0, 0), Barricade(0, 0, 0), Barricade(0, 0, 0), Barricade(0, 0, 0), Barricade(0, 0, 0), Barricade(0, 0, 0)};
int readX = 0;
int readY = 0;
long lastAddTime = 0;
long totalTime = 0;
String gameover = "no";

void setup() {
  display.begin();
  display.setCursor(0, 0);
  Serial.begin(9600);
}

void initialize () {
  y = joyY;
  x  = joyX;
  y = analogRead(joyY);
  x = analogRead(joyX);
  readY = ((y * 9 / 1012) + 48);
  readX = ((x * 9 / 1012) + 48);
}

void add () {
  Serial.print(readY);
  if (readY > 52)
  {
    positionY-= 25;
    if (positionY <= 0) positionY = 0;
  }
  if (readY < 50) 
  {
    positionY+=25;
    if (positionY >= max_height-25) positionY = max_height-25;
  }

  display.setCursor(display.width()/2-5, positionY);
}

void drawBarricade () {
   for (int x = 0; x < sizeof(listOfBarricade)/sizeof(listOfBarricade[0]); x++) {
      if (listOfBarricade[x].returnDelete()==1 && listOfBarricade[x].returnX()!=NULL)
      {
        listOfBarricade[x] = Barricade(0, 0, 0);
      } else {
      if (listOfBarricade[x].returnDelete() != 1)
      listOfBarricade[x].updateBarricade();
      if (listOfBarricade[x].checkColision(display.width()/2, positionY) == 1)
        gameover = "Game over!";
      if (listOfBarricade[x].returnX() >= 0 && listOfBarricade[x].returnX() < (display.width()-17))
        {
          if (listOfBarricade[x].returnX()!=0) {
            display.setCursor(listOfBarricade[x].returnX(), listOfBarricade[x].returnY());
            display.print("|");
          }
        }
      }
  }
}

float counter = 1.0;

void loop() {
  if ( gameover != "Game over!" ) {
    initialize();
    add();
    display.setTextSize(3);
    display.setTextColor(YELLOW);
    display.print("O");
    display.setTextColor(CYAN);
    drawBarricade();
    totalTime += delayTime;
    if (totalTime >= ((delayTime*counter)+lastAddTime)) {
      lastAddTime = totalTime;
      counter-=1;
      if (counter <= 0) counter = random(1,10);
      for (int i = 0; i < sizeof(listOfBarricade)/sizeof(listOfBarricade[0]); i++) {
        if (listOfBarricade[i].returnDelete() == 1)
        {
          listOfBarricade[i] = Barricade(max_width, max_height, delayTime);
        }
        totalTime += 60;
      } 
    }
    delay(delayTime);
    display.fillRect(0, 0, max_width, max_height, BLACK);
  }
  else
  {
    display.clearScreen();
    display.setTextColor(RED);
    display.setTextSize(2);
    display.setCursor(5, 10);
    display.print(gameover);
    display.setTextColor(BLUE);
    display.setTextSize(2);
    display.setCursor(2,40);
    display.print("Total time");
    display.setTextColor(GREEN);
    display.setCursor((display.width()/2-15), 80);
    display.setTextSize(3);
    display.print(totalTime/1000);
    display.setTextSize(2);
    display.setTextColor(MAGENTA);
    display.setCursor((display.width()/2-45), 110);
    display.print("seconds");
    delay(10000);
  }
}
