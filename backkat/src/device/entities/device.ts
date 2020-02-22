import { Log } from "./log";

export interface Device {
	_id: string
	name: string
	amountPerDay: number
	logs: Log[]
}