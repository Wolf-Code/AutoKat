import React, { FunctionComponent } from 'react'
import { useFetch } from '../../core/utils/useFetch'
import { DeviceLog } from '../../domain/devicelog/DeviceLog'

interface DeviceLogComponentProps {
	id: string
}

export const DeviceLogComponent: FunctionComponent<DeviceLogComponentProps> = props => {
	const { response, isLoading } = useFetch<DeviceLog[]>(`log/${props.id}`)

	if (isLoading) {
		return <div>Loading..</div>
	}

	return (
		<>
			{response?.sort((a,b) => new Date(b.moment).getTime() - new Date(a.moment).getTime()).map((log, index) => (
				<div key={ index }>
					{new Date(log.moment).toLocaleString()}: [{log.level}] {log.message}
				</div>
			))}
		</>
	)
}
