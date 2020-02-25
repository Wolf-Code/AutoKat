import { Application } from 'express'
import { registerRoutes as registerDeviceRoutes } from './domain/device/handlers'
import { registerRoutes as registerAnimalRoutes } from './domain/animal/handlers'
import { registerRoutes as registerDeviceLogRoutes } from './domain/devicelog/handlers'

export const registerRoutes = ( app: Application ) => {
	registerDeviceRoutes(app)
	registerAnimalRoutes(app)
	registerDeviceLogRoutes(app)
}