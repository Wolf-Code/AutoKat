import React, { FunctionComponent, useContext, useEffect, useRef } from 'react'
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
	const callbackRef = useRef(callback)
	const socketRef = useRef(socket)

	useEffect(() => {
		const localCallback = callback
		const localSocket = socketRef.current
		localSocket.on(event, localCallback)

		return () => {
			localSocket.off(event, callbackRef.current)
			callbackRef.current = localCallback
		}
	}, [event, callback])
}
