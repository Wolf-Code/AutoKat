#include <EEPROM.h>
#include "StorageHelper.h"

StorageData StorageHelper::data;

void StorageHelper::initialize()
{
	EEPROM.begin(1024);

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
		return;
	}

	unsigned int index = 0;
	data.serverUrl = readString(index);
	data.wifiSSID = readString(index);
	data.wifiPassword = readString(index);
}

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

void StorageHelper::writeString(unsigned int &index, String string)
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

void StorageHelper::saveStorageData(StorageData &data)
{
	unsigned int index = 0;
	writeString(index, data.serverUrl);
	writeString(index, data.wifiSSID);
	writeString(index, data.wifiPassword);
	EEPROM.commit();

	StorageHelper::data = data;
}

StorageData StorageHelper::getStorageData()
{
	return data;
}

bool StorageHelper::hasDataBeenWritten()
{
	unsigned int index = 0;
	unsigned int lengths[2];
	readLengths(index, lengths);

	return lengths[0] == lengths[1];
}