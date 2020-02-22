import { Application } from 'express'
import { registerRoutes as registerDeviceRoutes } from './device/handlers'
import { registerRoutes as registerAnimalRoutes } from './animal/handlers'

export const registerRoutes = ( app: Application ) => {
	registerDeviceRoutes(app)
	registerAnimalRoutes(app)
}