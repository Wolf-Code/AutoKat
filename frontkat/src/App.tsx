import React from 'react'
import { DevicesProvider } from './contexts/devices/DeviceContext'
import { Device } from './domain/device/Device'
import { useFetch } from './core/utils/useFetch'
import { LogsPage } from './components/devicelog/LogsPage'

function App() {
	const { response: devices } = useFetch<Device[]>('device', {
		method: 'GET'
	})

	return (
		<DevicesProvider value={devices || []}>
			<LogsPage />
		</DevicesProvider>
	)
}

export default App
