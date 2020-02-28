import socketIOClient from 'socket.io-client'
import React, { useState, useEffect } from 'react'
import { DevicesProvider } from './contexts/devices/DeviceContext'
import { Device } from './domain/device/Device'
import { useFetch } from './core/utils/useFetch'
import { LogsPage } from './components/devicelog/LogsPage'
import { SocketProvider } from './contexts/socket/SocketContext'

function App() {
	const [socket, setSocket] = useState<SocketIOClient.Socket>(socketIOClient({ autoConnect: false }))
	const { response: devices } = useFetch<Device[]>('device', {
		method: 'GET'
	})

	useEffect(() => {
		const localSocket = socketIOClient(process.env.REACT_APP_SERVER_URL as string)
		setSocket(localSocket)
	}, [])

	return (
		<DevicesProvider value={devices || []}>
			<SocketProvider value={socket}>
				<LogsPage />
			</SocketProvider>
		</DevicesProvider>
	)
}

export default App
