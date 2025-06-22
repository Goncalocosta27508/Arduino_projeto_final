#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pinos
#define BOTAO_PIN 2

// Bird
int birdY = 30;
int birdVelocidade = 0;
const int GRAVIDADE = 1;
const int PULO = -5;

// Cano
int canoX = SCREEN_WIDTH;
int canoGap = 20;
int canoAltura = 30;
const int canoLargura = 10;

// Estado
bool jogoAtivo = true;

void setup() {
  pinMode(BOTAO_PIN, INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(10, 10);
  display.println("FLAPPY BIRD");
  display.setCursor(10, 30);
  display.println("Pressiona o botao");
  display.display();
  delay(2000);
}

void loop() {
  if (!jogoAtivo) {
    display.clearDisplay();
    display.setCursor(30, 20);
    display.println("GAME OVER");
    display.display();
    delay(2000);
    reiniciarJogo();
    return;
  }

  // Entrada
  if (digitalRead(BOTAO_PIN) == LOW) {
    birdVelocidade = PULO;
  }

  // Atualizações
  birdVelocidade += GRAVIDADE;
  birdY += birdVelocidade;
  canoX -= 2;

  if (canoX < -canoLargura) {
    canoX = SCREEN_WIDTH;
    canoAltura = random(10, 40);
  }

  // Colisão
  if (birdY <= 0 || birdY >= SCREEN_HEIGHT ||
     (canoX < 20 && (birdY < canoAltura || birdY > canoAltura + canoGap))) {
    jogoAtivo = false;
  }

  // Desenhar
  display.clearDisplay();

  // Bird
  display.fillCircle(15, birdY, 3, SSD1306_WHITE);

  // Cano
  display.fillRect(canoX, 0, canoLargura, canoAltura, SSD1306_WHITE);
  display.fillRect(canoX, canoAltura + canoGap, canoLargura, SCREEN_HEIGHT, SSD1306_WHITE);

  display.display();
  delay(30);
}

void reiniciarJogo() {
  birdY = 30;
  birdVelocidade = 0;
  canoX = SCREEN_WIDTH;
  jogoAtivo = true;
}
