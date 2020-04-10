#include "Screen.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Logger.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 Screen::display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void Screen::initialize()
{
	if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
	{
		Logger::errorLine("Failed to allocate SSD1306");
	}

	Screen::display.setTextSize(1);
  	Screen::display.setTextColor(WHITE);
}

void Screen::clear()
{
	Screen::display.clearDisplay();
}

void Screen::writeText(const int x, const int y, const char* format, ...)
{
	const int bufferSize = 100;
	va_list args;
	va_start(args, format);
	char buffer[bufferSize];
	vsprintf(buffer, format, args);
	va_end(args);
	
	Screen::display.setCursor(x, y);
	Screen::display.print(buffer);
}

void Screen::render()
{
	Screen::display.display();
}