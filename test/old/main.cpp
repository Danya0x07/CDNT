#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET  -1
#define SCREEN_ADDRESS 0x3C

#define TFT_RST 3
#define TFT_CS 5
#define TFT_DC 4

#define CS_LAMPS 8
#define CS_DRAWINGS 7

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

void spi_write(uint8_t cs_pin, uint8_t *data, size_t len)
{

    SPI.beginTransaction(SPISettings(14000000, LSBFIRST, SPI_MODE0));
    digitalWrite(cs_pin, 0);
    while (len--)
    {
        SPI.transfer(*data++);
        //shiftOut(11, 13, LSBFIRST, *data++);
    }
    digitalWrite(cs_pin, 1);
    SPI.endTransaction();
}

void test_lamps()
{
    uint8_t data[4] = {0};

    for (uint8_t i = 0; i < 4; i++)
    {
        for (uint8_t j = 0; j < 8; j++)
        {
            data[i] |= 1 << j;
            spi_write(CS_LAMPS, data, sizeof(data));
            delay(500);
            data[i] &= ~(1 << j);
            spi_write(CS_LAMPS, data, sizeof(data));
            delay(500);
        }
    }
}

void test_drawings()
{
    uint8_t data[6] = {0};

    for (uint8_t i = 0; i < 6; i++)
    {
        for (uint8_t j = 0; j < 8; j++)
        {
            data[i] |= 1 << j;
            spi_write(CS_DRAWINGS, data, sizeof(data));
            delay(500);
            data[i] &= ~(1 << j);
            spi_write(CS_DRAWINGS, data, sizeof(data));
            delay(500);
        }
    }
}

void setup()
{
    pinMode(CS_LAMPS, OUTPUT);
    pinMode(CS_DRAWINGS, OUTPUT);
    pinMode(6, OUTPUT);

    SPI.begin();
    uint8_t buf[6] = {0};
    spi_write(CS_LAMPS, buf, 4);
    spi_write(CS_DRAWINGS, buf, 6);

    Serial.begin(115200);
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }
    display.clearDisplay();
    display.display();
    display.setTextSize(3);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(25, 25);
    display.print("Test");
    display.display();

    tone(6, 1000, 300);

    tft.initR(INITR_BLACKTAB);
    tft.setRotation(1);
    tft.fillScreen(ST77XX_BLACK);

    tft.setCursor(40, 20);
    tft.setTextSize(3);
    tft.setTextColor(ST77XX_RED);
    tft.print('T');
    tft.setTextColor(ST77XX_GREEN);
    tft.print('e');
    tft.setTextColor(ST77XX_BLUE);
    tft.print('s');
    tft.setTextColor(ST77XX_CYAN);
    tft.print('t');

    tft.setCursor(20, 80);
    tft.setTextSize(2);
    tft.setTextColor(ST77XX_WHITE);
    tft.print("Lamps");
    test_lamps();

    tone(6, 500, 100);
    tft.fillRect(20, 80, 100, 20, 0);
    tft.setCursor(20, 80);
    tft.print("Drawings");
    test_drawings();

    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(40, 40);
    tft.setTextSize(2);
    tft.print("Test\n  Completed");

    display.clearDisplay();
    display.display();
    tone(6, 2000, 200);
}

void loop() {}