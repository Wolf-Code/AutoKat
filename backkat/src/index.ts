import express from 'express'
import bodyParser from 'body-parser'
import dotenv from 'dotenv'
import cors from 'cors'
import { registerRoutes } from './handlers'
import socketIO from 'socket.io'
import http from 'http'

dotenv.config()

const app = express()
app.use(express.json());
app.use(cors({
	origin: "http://localhost:3000",
	credentials: true
}))
const port = process.env.SERVER_PORT

var httpServer = http.createServer(app)
var io = socketIO(httpServer, {
	path: '/socket.io'
})

registerRoutes(app, io)

// start the Express server
httpServer.listen(port, () => {
	console.log(`server started at http://localhost:${port}`)
})
