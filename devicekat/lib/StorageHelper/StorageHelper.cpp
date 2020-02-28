#include <EEPROM.h>
#include "StorageHelper.h"

StorageData StorageHelper::data;

void StorageHelper::initialize()
{
	StorageData data;
	int serverUrlEnd = 0;
	data.serverUrl = readString(0, serverUrlEnd);

	int ssidEnd = 0;
	data.wifiSSID = readString(serverUrlEnd, ssidEnd);

	int wifiPasswordEnd = 0;
	data.wifiPassword = readString(ssidEnd, wifiPasswordEnd);
}

String StorageHelper::readString(int index, int &endedAtIndex)
{
	const uint8_t highByte = EEPROM.read(index++);
	const uint8_t lowByte = EEPROM.read(index++);

	const int length = combineTwoBytesIntoInt(highByte, lowByte);
	char *chars = new char[length];
	for (int x = 0; x < length; x++)
	{
		chars[x] = (char)EEPROM.read(index++);
	}

	endedAtIndex = index;

	const String finalString = String(chars);
	delete chars;
	return finalString;
}

unsigned int StorageHelper::combineTwoBytesIntoInt(uint8_t high, uint8_t low)
{
	int combined = high;
	combined = combined * 256;
	combined *= low;

	return combined;
}

int StorageHelper::writeString(int index, String string)
{
	uint8_t high;
	uint8_t low;
	decomposeIntToTwoBytes(string.length(), high, low);
	EEPROM.put(index++, high);
	EEPROM.put(index++, low);

	for(unsigned int x = 0; x < string.length(); x++)
	{
		EEPROM.put(index++, string[x]);
	}

	return index;
}


void StorageHelper::decomposeIntToTwoBytes(unsigned int value, uint8_t &high, uint8_t &low)
{
	high = value / 256;
	low = value % 256;
}

void StorageHelper::saveStorageData(StorageData& data)
{
	int ended = writeString(0, data.serverUrl);
	ended = writeString(ended, data.wifiSSID);
	ended = writeString(ended, data.wifiPassword);
}

StorageData StorageHelper::getStorageData()
{
	return data;
}