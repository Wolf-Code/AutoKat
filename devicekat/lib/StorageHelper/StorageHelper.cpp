#ifdef ESP8266
	#include <EEPROM.h>
#endif

#ifdef ESP32
	#include <Preferences.h>
#endif
#include <Constants.h>
#include "StorageHelper.h"

StorageData StorageHelper::data;
Preferences StorageHelper::preferences;
#ifdef ESP32
	const char* PREFERENCES_WIFI = "PREFERENCES_WIFI";
#endif

void StorageHelper::initialize(Preferences preferences)
{
	StorageHelper::preferences = preferences;
	#ifdef ESP8266
		EEPROM.begin(1024);
	#endif

	if (!hasDataBeenWritten())
	{
		return;
	}

	reloadFromEEPROM();
}

void StorageHelper::reloadFromEEPROM()
{
	if (!hasDataBeenWritten())
	{
		Serial.println("No configuration stored");
		return;
	}

	#ifdef ESP8266
		unsigned int index = 0;
		data.serverUrl = readString(index);
		data.wifiSSID = readString(index);
		data.wifiPassword = readString(index);
	#endif

	#ifdef ESP32
		StorageHelper::preferences.begin(PREFERENCES_WIFI, true);
		data.serverUrl = StorageHelper::preferences.getString("Url");
		data.wifiSSID = StorageHelper::preferences.getString("SSID");
		data.wifiPassword = StorageHelper::preferences.getString("Password");
		StorageHelper::preferences.end();
	#endif

	Serial.println(data.serverUrl);
	Serial.println(data.wifiSSID);
	Serial.println(data.wifiPassword);
}

#ifdef ESP8266
String StorageHelper::readString(unsigned int &index)
{
	unsigned int lengths[2];
	readLengths(index, lengths);
	const unsigned int length = lengths[0];

	char chars[length + 1];
	for (unsigned int x = 0; x < length; x++)
	{
		chars[x] = EEPROM.read(index++);
	}
	chars[length] = '\0';

	const String finalString = String(chars);
	return finalString;
}

void StorageHelper::readLengths(unsigned int &index, unsigned int lengths[])
{
	for (int i = 0; i < 2; i++)
	{
		unsigned char *accessor = (unsigned char *)&lengths[i];
		const unsigned int bytes = sizeof(unsigned int);
		for (unsigned int x = 0; x < bytes; x++)
		{
			accessor[x] = EEPROM.read(index++);
		}
	}
}

void StorageHelper::writeString(unsigned int &index, String &string)
{
	const char *chars = string.c_str();
	const unsigned int length = string.length();
	writeLength(index, length);

	for (unsigned int x = 0; x < length; x++)
	{
		EEPROM.put(index++, (char)chars[x]);
	}
}

void StorageHelper::writeLength(unsigned int &index, unsigned int length)
{
	EEPROM.put(index, length);
	index += sizeof(unsigned int);
	EEPROM.put(index, length);
	index += sizeof(unsigned int);
}
#endif

void StorageHelper::saveStorageData(StorageData &data)
{
	#ifdef ESP8266
		unsigned int index = 0;
		writeString(index, data.serverUrl);
		writeString(index, data.wifiSSID);
		writeString(index, data.wifiPassword);
		EEPROM.commit();
	#endif

	#ifdef ESP32
		StorageHelper::preferences.begin(PREFERENCES_WIFI, false);
		StorageHelper::preferences.putString("Url", data.serverUrl);
		StorageHelper::preferences.putString("SSID", data.wifiSSID);
		StorageHelper::preferences.putString("Password", data.wifiPassword);
		StorageHelper::preferences.putBool("Written", true);
		StorageHelper::preferences.end();
	#endif

	StorageHelper::data = data;
}

StorageData StorageHelper::getStorageData()
{
	return data;
}

bool StorageHelper::hasDataBeenWritten()
{
	#ifdef ESP8266
		unsigned int index = 0;
		unsigned int lengths[2];
		readLengths(index, lengths);

		return lengths[0] == lengths[1];
	#endif

	#ifdef ESP32
		StorageHelper::preferences.begin(PREFERENCES_WIFI, true);
		const bool isWritten = StorageHelper::preferences.getBool("Written", false);
		StorageHelper::preferences.end();

		return isWritten;
	#endif
}