import { ObjectId } from "mongodb";

export interface DeviceLog
{
	moment?: Date
	log: string
	level: string
}

export interface DeviceLogs
{
	_id?: ObjectId
	deviceId: string
	logs: DeviceLog[]
}