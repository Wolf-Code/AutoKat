import { createConnection } from 'typeorm'
import { Application } from 'express'
import { useRequestHandler } from '../../utils/request-handler'
import { useDatabase } from '../../data/database'
import { DeviceLogs, DeviceLog } from '../../data/entities/devicelog'
import { Logger } from '../../core/logging/logger'
import { Device } from '../../data/entities/device'
import { differenceInCalendarDays } from 'date-fns'

export const registerRoutes = (app: Application, io: SocketIO.Server) => {
	app.get(
		'/food/:deviceid/query',
		useRequestHandler(async (req, res) => {
			await useDatabase(async connection => {
				const repository = connection.getRepository(Device)
				const device = await repository.findOne({ _id: req.params.deviceid })
				if (!device) {
					res.send({
						amount: 0
					})

					return
				}

				const now = new Date()
				const passedTime = now.getHours() * 60 + now.getMinutes()
				const totalTime = 24 * 60
				const totalAmount = Math.round((passedTime / totalTime) * device.amount)

				const todayLogs = device.logs.filter(x => differenceInCalendarDays(now, x.moment as Date) <= 0)
				let finalAmount = totalAmount
				todayLogs.forEach(log => {
					finalAmount -= log.amount
				});

				res.send({
					amount: finalAmount
				})
			})
		})
	)
}
