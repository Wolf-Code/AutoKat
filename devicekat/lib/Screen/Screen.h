#ifndef Screen_h
#define Screen_h
#include <Adafruit_SSD1306.h>

class Screen
{
	public:
		static void initialize(void);
		static void writeText(const int x, const int y, const char *format, ...);
		static void clear(void);
		static void render(void);
	private:
		static Adafruit_SSD1306 display;
};

#endif