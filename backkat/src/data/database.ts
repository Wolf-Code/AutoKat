import { MongoClient, Db, Collection } from 'mongodb'
import { Logger } from '../core/logging/logger'

export const useDatabase = async (callback: (database: Db, client: MongoClient) => void) => {
	const connectionString = `${process.env.DATABASE_URL}/${process.env.DATABASE_NAME}`
	const client = new MongoClient(connectionString, {
		useUnifiedTopology: true
	})

	await client.connect(async err => {
		if (err) {
			Logger.error(`Failed connecting to ${connectionString}: ${err}`)
			throw err
		}

		const db = client.db()
		try {
			await callback(db, client)
		} catch (error) {
			Logger.error(error)
			throw error
		}
		finally {
			client.close()
		}
	})
}

export const collections = {
	animals: 'animals',
	devices: 'devices',
	devicelogs: 'devicelogs'
}
