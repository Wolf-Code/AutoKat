import { Application } from 'express'
import { useDatabase, collections } from '../data/database'
import { Animal } from './entities/animal'
import { Logger } from '../logging/logger'
import { useRequestHandler } from '../utils/request-handler'

export const registerRoutes = async (app: Application) => {
	app.get(
		'/animal',
		useRequestHandler(async (req, res) => {
			await useDatabase(async db => {
				const animals = await db
					.collection(collections.animals)
					.find()
					.toArray()

				res.send(animals)
			})
		})
	)

	app.get(
		'/animal/:id',
		useRequestHandler(async (req, res) => {
			await useDatabase(async db => {
				const animal = await db.collection(collections.animals).findOne({
					id: req.params.id
				})

				res.send(animal)
			})
		})
	)

	app.post(
		'/animal',
		useRequestHandler(async (req, res) => {
			const animal = req.body as Animal

			if (!animal) {
				throw 'Provided data was not a valid animal'
			}

			await useDatabase(async db => {
				const collection = db.collection<Animal>(collections.animals)
				if (await collection.findOne({ name: animal.name })) {
					res.status(500)
					res.end(`Provided name '${animal.name}' is already in use`)
					return
				}

				animal._id = undefined
				res.send(await db.collection(collections.animals).insertOne(animal))
			})
		})
	)

	app.put(
		'/animal/:id',
		useRequestHandler(async (req, res) => {
			const updatedAnimal = req.body as Animal

			if (!updatedAnimal) {
				throw 'Invalid animal was provided for update'
			}

			await useDatabase(async db => {
				const collection = db.collection<Animal>(collections.animals)
				const existingAnimal = await collection.findOne({ id: req.params.id })

				if (!existingAnimal) {
					throw `Unable to find an animal with id ${req.params.id}`
				}

				await collection.replaceOne({ id: req.params.id }, updatedAnimal)
			})

			res.send(updatedAnimal)
		})
	)
}
