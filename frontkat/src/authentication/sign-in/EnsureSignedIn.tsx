import useAuthenticationService from 'authentication/useAuthenticationService'
import { useEffect } from 'react'

export default () => {
    const { ensureSignedIn } = useAuthenticationService()

    useEffect(() => {
        const retrieve = async() => await ensureSignedIn()

        retrieve()
    }, [])

    return null
}
