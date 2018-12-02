#include <Adafruit_GFX.h>    // Core graphics library
#include <MCUFRIEND_kbv.h>   // Hardware-specific library
MCUFRIEND_kbv tft;

//#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
//#include <Fonts/FreeSerif12pt7b.h>

//#include <FreeDefaultFonts.h>

#define BLACK   0x0000
#define RED     0xF800
#define GREEN   0x07E0
#define WHITE   0xFFFF
#define GREY    0x8410

int height = tft.width();
int width = tft.height();
int ballSize = 5;
int ballX = width / 2;
int ballY = height / 2;
int oldBallX;
int oldBallY;

int paddleWidth = 10;
int paddleHeight = 90;
int paddleX = width - paddleWidth - 10;
int paddleY = height / 2 - paddleHeight / 2;
int oldPaddleY;
int paddleSpeed = 5;

int ballSpeed = 10;

int ballSpeedX = 5;
int ballSpeedY = 1;



void setup(void)
{
    Serial.begin(9600);
    uint16_t ID = tft.readID();
    if (ID == 0xD3) ID = 0x9481;
    tft.reset(),
    tft.begin(ID);
    tft.setRotation(1);
    tft.fillScreen(BLACK);
//    tft.setTextColor(WHITE);
//    tft.setTextSize(5);
//    tft.setCursor(100, 110);
//    tft.print("PONG");
//    delay(1000);
//    tft.fillScreen(BLACK);

    drawPaddle();
}

void loop(void)
{
    
  moveBall();

  movePaddle();
    
  delay(ballSpeed);
  
}

void moveBall() {
  
  if(ballX > width + 50 || ballX < 0) {
    ballSpeedX = -ballSpeedX;
  }
  if(ballY > height - ballSize || ballY < 0) {
    ballSpeedY = -ballSpeedY;
  }
  if((ballY + ballSize / 2 >= paddleY && ballY + ballSize / 2 <= paddleY + paddleHeight) && ballX + ballSize >= paddleX && ballSpeedX > 0) {
    ballSpeedX = -ballSpeedX;
//    Serial.println("hit");
  }
  
  ballX += ballSpeedX;
  ballY += ballSpeedY;
  
  if (oldBallX != ballX || oldBallY != ballY) {
    tft.fillCircle(oldBallX, oldBallY, ballSize, BLACK);
  }

  tft.fillCircle(ballX, ballY, ballSize, WHITE);
  drawPaddle();

  oldBallX = ballX;
  oldBallY = ballY;

  
}

void drawPaddle() {
    
  tft.fillRect(paddleX, paddleY, paddleWidth, paddleHeight, WHITE);  
  
}

void movePaddle() {
  int sensorValueD = analogRead(A15);
  
  if(sensorValueD < 2) {
    paddleY += paddleSpeed;
  
  if (oldPaddleY != paddleY) {
    tft.fillRect(paddleX, oldPaddleY, paddleWidth, paddleHeight, BLACK);
  }

  tft.fillRect(paddleX, paddleY, paddleWidth, paddleHeight, WHITE);

  oldPaddleY = paddleY;
    
//    Serial.println("ok");
  }

  int sensorValueU = analogRead(A14);
  
  if(sensorValueU < 2) {
    paddleY -= paddleSpeed;
  
  if (oldPaddleY != paddleY) {
    tft.fillRect(paddleX, oldPaddleY, paddleWidth, paddleHeight, BLACK);
  }

  tft.fillRect(paddleX, paddleY, paddleWidth, paddleHeight, WHITE);

  oldPaddleY = paddleY;
    
//    Serial.println("ok");
  }
  
}
