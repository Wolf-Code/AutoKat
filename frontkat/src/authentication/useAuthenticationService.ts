import useFetch from 'core/utilities/useFetch'
import { useAuthenticationContext } from './AuthenticationContext'

interface AuthenticationData {
    id: string,
    token: string,
    tokenExpirationTime: number
}

interface SignInResult {
    success: boolean,
    information: string,
    authenticationData: AuthenticationData
}

export default () => {
    const authenticationContext = useAuthenticationContext()
    const { post } = useFetch()

    const signIn = async(email: string, password: string) => {
        const result = await post<SignInResult>('user/login', {
            email,
            password
        })

        if (result.success) {
            authenticationContext.setToken(result.authenticationData.token)
        }
    
        return result
    }
    
    return { signIn }
}