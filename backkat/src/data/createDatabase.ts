import { useDatabase } from './database'
import { Animal } from '../domain/animal/entities/animal'
import { Device } from '../domain/device/entities/device'
import { Logger } from '../core/logging/logger'
import { DeviceLogs } from '../domain/devicelog/entities/devicelog'

export const createDatabase = async () => {
	useDatabase(async db => {
		await db.createCollection<Animal>("animals")
		await db.createCollection<Device>("devices")
		await db.createCollection<DeviceLogs>("devicelogs")
	})
}