import { Application } from 'express'
import { useRequestHandler } from '../../utils/request-handler'
import { useDatabase } from '../../data/database'
import { Device } from '../../data/entities/device'
import { FoodLog } from '../../data/entities/foodlog'

export const registerRoutes = (app: Application, io: SocketIO.Server) => {
	app.get(
		'/device',
		useRequestHandler(async (req, res) => {
			await useDatabase(async connection => {
				const repository = connection.getRepository(Device)
				const devices = await repository.find()

				res.send(devices)
			})
		})
	)

	app.get(
		'/device/:id',
		useRequestHandler(async (req, res) => {
			await useDatabase(async connection => {
				const repository = connection.getRepository(Device)
				let device = await repository.findOne({ _id: req.params.id })
				if (!device) {
					device = {
						_id: req.params.id,
						amount: 50,
						logs: [],
						name: `New Device (${req.params.id})`
					}

					const result = await repository.insert(device)
				}

				device.logs = []
				res.send(device)
			})
		})
	)
}
