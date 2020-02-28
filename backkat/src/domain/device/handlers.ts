import { Application } from 'express'
import { useRequestHandler } from '../../utils/request-handler'
import { useDatabase, collections } from '../../data/database'
import { Device } from './entities/device'
import { FoodLog } from './entities/foodlog'

export const registerRoutes = (app: Application, io: SocketIO.Server) => {
	app.get(
		'/device',
		useRequestHandler(async (req, res) => {
			await useDatabase(async db => {
				const devices = await db
					.collection<Device>(collections.devices)
					.find()
					.toArray()

				res.send(devices)
			})
		})
	)

	app.get(
		'/device/:id',
		useRequestHandler(async (req, res) => {
			await useDatabase(async db => {
				const collection = db.collection<Device>(collections.devices)
				let device = await collection.findOne({ _id: req.params.id })
				if (!device) {
					device = {
						_id: req.params.id,
						amount: 50,
						logs: [],
						name: `New Device (${req.params.id})`
					}

					await collection.insertOne(device)
				}

				device.logs = []
				res.send(device)
			})
		})
	)

	app.get(
		'/device/:id/log-food',
		useRequestHandler(async (req, res) => {
			await useDatabase(async db => {
				const device = await db.collection<Device>(collections.devices).findOne({ _id: req.params.id })
				if (!device) {
					throw `No device found with id ${req.params.id}`
				}

				res.send(device.logs)
			})
		})
	)

	app.post(
		'/device/:id/log-food',
		useRequestHandler(async (req, res) => {
			const log = req.body as FoodLog
			if (!log) {
				throw 'Invalid log provided'
			}

			await useDatabase(async db => {
				const collection = db.collection<Device>(collections.devices)
				const device = await collection.findOne({ _id: req.params.id })

				if (!device) {
					throw `No device found with id ${req.params.id}`
				}

				log.moment = new Date()
				device.logs.push(log)

				await collection.updateOne({ _id: req.params.id }, { $set: { logs: device.logs } })

				res.send(log)
			})
		})
	)
}
