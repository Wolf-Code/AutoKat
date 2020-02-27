import { DeviceLog } from "../devicelog/DeviceLog";

export interface Device
{
	name: string
	_id: string
	logs: DeviceLog[]
	amount: number
}