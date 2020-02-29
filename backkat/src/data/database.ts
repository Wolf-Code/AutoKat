import { createConnection, Connection, EntityManager, ConnectionOptions, Repository } from 'typeorm'
import { MongoClient, Db, Collection } from 'mongodb'
import { Logger } from '../core/logging/logger'

export const useDatabase = async (callback: (connection: Connection) => void) => {
	try {
		const connection = await createConnection()

		try {
			await callback(connection)
			connection.close()
		} catch (error) {
			Logger.error(error)
			throw error
		}
	} catch (error) {
		Logger.error('Failed using database: ', error)
		throw error
	}
}
