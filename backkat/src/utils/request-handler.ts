import { Request, Response } from 'express'
import { Logger } from '../core/logging/logger'

export const useRequestHandler = (callback: (req: Request, res: Response) => void): ((req: Request, res: Response) => void) => {
	return async (request, response) => {
		try {
			Logger.debug(`Handling request to ${request.originalUrl}`)
			await callback(request, response)
		} catch (error) {
			response.status(500)
			console.error(error)
			response.end(error)
		}
	}
}
