import express from 'express'
import bodyParser from 'body-parser'
import dotenv from 'dotenv'
import cors from 'cors'
import { registerRoutes } from './handlers'

dotenv.config()

const app = express()
app.use(express.json());
app.use(cors())
const port = process.env.SERVER_PORT

registerRoutes(app)

// start the Express server
app.listen(port, () => {
	console.log(`server started at http://localhost:${port}`)
})
