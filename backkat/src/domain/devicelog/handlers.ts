import { createConnection } from 'typeorm'
import { Application } from 'express'
import { useRequestHandler } from '../../utils/request-handler'
import { useDatabase } from '../../data/database'
import { DeviceLogs, DeviceLog } from '../../data/entities/devicelog'
import { Logger } from '../../core/logging/logger'

export const registerRoutes = (app: Application, io: SocketIO.Server) => {
	app.post(
		'/log/:deviceid',
		useRequestHandler(async (req, res) => {
			await useDatabase(async connection => {
				const repository = connection.getRepository(DeviceLogs)
				let deviceLog = await repository.findOne({ _id: req.params.deviceid })

				if (!deviceLog) {
					deviceLog = {
						_id: req.params.deviceid,
						logs: []
					}

					await repository.insert(deviceLog)
				}

				const log = req.body as DeviceLog
				log.moment = new Date()
				deviceLog.logs.push(log)

				await repository.update({ _id: deviceLog._id }, { logs: deviceLog.logs })

				io.emit(`devicelog.new/${deviceLog._id}`, log)

				res.send(log)
			})
		})
	)

	app.get(
		'/log/:deviceid',
		useRequestHandler(async (req, res) => {
			await useDatabase(async connection => {
				const repository = connection.getRepository(DeviceLogs)
				try {
					const deviceLog = await repository.findOne({ _id: req.params.deviceid })

					if (!deviceLog) {
						res.send([])
						return
					}

					const logs = deviceLog.logs.filter(x => x.moment?.getDate() == new Date().getDate())
					logs.sort((a, b) => (b.moment as Date).getTime() - (a.moment as Date).getTime())
					res.send(logs)
				} catch (e) {
					Logger.error(`Failed retrieving device logs for device ${req.params.deviceid}: `, e)
					res.status(500)
					res.send([])
				}
			})
		})
	)
}
