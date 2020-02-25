import { FoodLog } from "./foodlog";

export interface Device {
	_id: string
	name: string
	amount: number
	logs: FoodLog[]
}