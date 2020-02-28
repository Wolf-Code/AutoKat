#ifndef StorageHelper_h
#define StorageHelper_h

#include <WString.h>
#include "StorageData.h"

class StorageHelper
{
public:
	static void initialize();

	static void saveStorageData(StorageData &data);

	static StorageData getStorageData();

private:
	static StorageData data;
	static String readString(int index, int &endedAtIndex);
	static int writeString(int index, String string);
	static unsigned int combineTwoBytesIntoInt(uint8_t high, uint8_t low);
	static void decomposeIntToTwoBytes(unsigned int value, uint8_t &high, uint8_t &low);
};

#endif