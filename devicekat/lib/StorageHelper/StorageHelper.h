#ifndef StorageHelper_h
#define StorageHelper_h

#include <WString.h>
#include <Preferences.h>
#include "StorageData.h"

class StorageHelper
{
public:
#ifdef ESP32
	static void initialize(Preferences* preferences);
#endif

#ifdef ESP8266
	static void initialize();
#endif

	static void saveStorageData(StorageData &data);
	static void reloadFromStorage();
	static StorageData getStorageData();
	static bool hasDataBeenWritten();

private:
#ifdef ESP32
	static Preferences* preferences;
#endif
	static StorageData data;
	static String readString(unsigned int &index);
	static void writeString(unsigned int &index, String &string);
	static void readLengths(unsigned int &index, unsigned int lengths[]);
	static void writeLength(unsigned int &index, unsigned int length);
};

#endif