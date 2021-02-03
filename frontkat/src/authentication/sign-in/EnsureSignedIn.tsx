import useAuthenticationService from 'authentication/useAuthenticationService'
import { useEffect } from 'react'

export default () => {
    const { refreshToken } = useAuthenticationService()

    useEffect(() => {
        const retrieve = async() => await refreshToken()

        retrieve()
    }, [])

    return null
}
