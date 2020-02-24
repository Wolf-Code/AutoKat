import { Log } from "./log";

export interface Device {
	_id: string
	name: string
	amount: number
	logs: Log[]
}