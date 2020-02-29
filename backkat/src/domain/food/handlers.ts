import { createConnection } from 'typeorm'
import { Application } from 'express'
import { useRequestHandler } from '../../utils/request-handler'
import { useDatabase } from '../../data/database'
import { DeviceLogs, DeviceLog } from '../../data/entities/devicelog'
import { Logger } from '../../core/logging/logger'

export const registerRoutes = (app: Application, io: SocketIO.Server) => {
	app.get(
		'/food/:deviceid/query',
		useRequestHandler(async (req, res) => {
			res.send({
				amount: 123
			})
		})
	)
}
