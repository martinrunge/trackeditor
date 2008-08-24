/*
 * DeviceData.cpp
 *
 *  Created on: 30.07.2008
 *      Author: martin
 */

#include "DeviceData.h"

DeviceData::DeviceData() {
	deviceName.clear();
	deviceInfo.clear();
	deviceSerial.clear();

	logStart = 0;
	logEnd = 0;
	logAreaStart = 0;
	logAreaEnd = 0;

	logStartSet = false;
	logEndSet = false;
	logAreaStartSet = false;
	logAreaEndSet = false;

}

DeviceData::~DeviceData() {
	// TODO Auto-generated destructor stub
}
