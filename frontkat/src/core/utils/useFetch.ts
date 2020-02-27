import React, { useRef } from 'react'

const createUrl = (endpoint: string) => {
	return `${process.env.REACT_APP_SERVER_URL}/${endpoint}`
}

export const useFetch = <TResponse = any>(endpoint: string, options?: RequestInit) => {
	const [response, setResponse] = React.useState<TResponse>()
	const [error, setError] = React.useState(null)
	const [isLoading, setIsLoading] = React.useState(false)
	const url = createUrl(endpoint)
	const optionsRef = useRef(options)
	optionsRef.current = options

	React.useEffect(() => {
		const fetchData = async () => {
			setIsLoading(true)
			try {
				const res = await fetch(url, optionsRef.current)
				const json = await res.json()

				setResponse(json)
			} catch (error) {
				setError(error)
			} finally {
				setIsLoading(false)
			}
		}

		fetchData()
	}, [url])

	return { response, error, isLoading }
}
