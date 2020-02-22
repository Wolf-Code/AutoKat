import { Request, Response } from 'express'

export const useRequestHandler = (callback: (req: Request, res: Response) => void): ((req: Request, res: Response) => void) => {
	return async (request, response) => {
		try {
			await callback(request, response)
		} catch (error) {
			response.status(500)
			response.end(error)
		}
	}
}
