import React, { FunctionComponent, useContext } from "react"
import { Device } from "../../domain/device/Device"

const DevicesContext = React.createContext<Device[]>([])

interface DevicesProviderProps
{
	value: Device[]
}

export const DevicesProvider: FunctionComponent<DevicesProviderProps> = props => {
	return (<DevicesContext.Provider value={ props.value }>
		{ props.children }
	</DevicesContext.Provider>)
}

export const useDevices = () => {
	return useContext(DevicesContext)
}
