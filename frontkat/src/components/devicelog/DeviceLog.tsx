import React, { FunctionComponent, useState, useEffect } from 'react'
import { useFetch } from '../../core/utils/useFetch'
import { DeviceLog } from '../../domain/devicelog/DeviceLog'
import { useSocket } from '../../contexts/socket/SocketContext'

interface DeviceLogComponentProps {
	id: string
}

export const DeviceLogComponent: FunctionComponent<DeviceLogComponentProps> = props => {
	const [logs, setLogs] = useState<DeviceLog[]>([])
	const { response, isLoading } = useFetch<DeviceLog[]>(`log/${props.id}`)
	useSocket(`devicelog.new/${props.id}`, data => {
		const copy = [...logs]
		copy.push(data as DeviceLog)
		setLogs(copy)
	})

	useEffect(() => {
		if (!response) {
			return
		}

		setLogs(response as DeviceLog[])
	}, [response])

	if (isLoading) {
		return <div>Loading..</div>
	}

	return (
		<>
			{logs
				?.sort((a, b) => new Date(b.moment).getTime() - new Date(a.moment).getTime())
				.map((log, index) => (
					<div key={index}>
						{new Date(log.moment).toLocaleString()}: [{log.level}] {log.message}
					</div>
				))}
		</>
	)
}
