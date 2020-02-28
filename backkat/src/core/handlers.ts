import { Application } from 'express'
import { Logger } from './logging/logger'

export const registerRoutes = (app: Application, io: SocketIO.Server) => {
	io.on('connection', socket => {
		Logger.debug(`Socket connected`)

		socket.on('disconnect', () => {
			Logger.debug('Socket disconnected')
		})
	})
}
