import React, { FunctionComponent, useContext, useEffect } from 'react'
import socketIOClient from 'socket.io-client'

const SocketContext = React.createContext<SocketIOClient.Socket>(
	socketIOClient({
		autoConnect: false
	})
)

interface SocketProviderProps {
	value: SocketIOClient.Socket
}

export const SocketProvider: FunctionComponent<SocketProviderProps> = props => {
	return <SocketContext.Provider value={props.value}>{props.children}</SocketContext.Provider>
}

export const useSocket = (event: string, callback: (data: any) => void) => {
	const socket = useContext(SocketContext)

	useEffect(() => {
		socket.on(event, callback)

		return () => {
			socket.off('event', callback)
		}
	}, [socket, event, callback])
}
