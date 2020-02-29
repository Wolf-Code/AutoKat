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
	static void reloadFromEEPROM();
	static bool hasDataBeenWritten();

private:
	static StorageData data;
	static String readString(unsigned int &index);
	static void writeString(unsigned int &index, String &string);
	static void readLengths(unsigned int &index, unsigned int lengths[]);
	static void writeLength(unsigned int &index, unsigned int length);
};

#endif