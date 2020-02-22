import { useDatabase } from './database'
import { Animal } from '../animal/entities/animal'
import { Device } from '../device/entities/device'
import { Logger } from '../logging/logger'

export const createDatabase = async () => {
	useDatabase(async db => {
		await db.createCollection<Animal>("animals")
		await db.createCollection<Device>("devices")
	})
}