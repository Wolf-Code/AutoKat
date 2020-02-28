import { Application } from 'express'
import { useRequestHandler } from '../../utils/request-handler'
import { useDatabase, collections } from '../../data/database'
import { DeviceLogs, DeviceLog } from './entities/devicelog'

export const registerRoutes = (app: Application, io: SocketIO.Server) => {
	app.post(
		'/log/:deviceid',
		useRequestHandler(async (req, res) => {
			await useDatabase(async db => {
				const collection = db.collection<DeviceLogs>(collections.devicelogs)
				let deviceLog = await collection.findOne({ deviceId: req.params.deviceid })

				if (!deviceLog) {
					deviceLog = {
						deviceId: req.params.deviceid,
						logs: []
					}

					await collection.insertOne(deviceLog)
				}

				const log = req.body as DeviceLog
				log.moment = new Date()
				deviceLog.logs.push(log)

				await collection.updateOne({ deviceId: deviceLog.deviceId }, { $set: { logs: deviceLog.logs } })

				io.emit(`devicelog.new/${deviceLog.deviceId}`, log)

				res.send(log)
			})
		})
	)

	app.get(
		'/log/:deviceid',
		useRequestHandler(async (req, res) => {
			await useDatabase(async db => {
				const collection = db.collection<DeviceLogs>(collections.devicelogs)
				let deviceLog = await collection.findOne({ deviceId: req.params.deviceid })

				if (!deviceLog) {
					res.send([])
					return
				}

				res.send(deviceLog.logs.filter(x => x.moment?.getDate() == new Date().getDate()))
			})
		})
	)
}
