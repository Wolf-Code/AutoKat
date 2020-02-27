import React from 'react'
import { useDevices } from '../../contexts/devices/DeviceContext'
import { DeviceLogComponent } from './DeviceLog'

export const LogsPage = () => {
	const devices = useDevices()

	console.log(devices)

	return (
		<>
			{devices.map(device => (
				<DeviceLogComponent key={ device._id } id={ device._id } />
			))}
		</>
	)
}