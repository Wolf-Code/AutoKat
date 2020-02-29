import { Application } from 'express'
import { registerRoutes as registerDeviceRoutes } from './domain/device/handlers'
import { registerRoutes as registerDeviceLogRoutes } from './domain/devicelog/handlers'
import { registerRoutes as registerCoreRoutes } from './core/handlers'

export const registerRoutes = (app: Application, io: SocketIO.Server) => {
	registerDeviceRoutes(app, io)
	registerDeviceLogRoutes(app, io)
	registerCoreRoutes(app, io)
}
