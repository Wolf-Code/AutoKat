import useFetch from 'core/utilities/useFetch'
import useAuthenticationAtom from './AuthenticationAtom'

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
    const [, setAuthenticationAtom] = useAuthenticationAtom()
    const { post } = useFetch()

    const signIn = async(email: string, password: string) => {
        const result = await post<SignInResult>('user/login', {
            email,
            password
        })

        if (result.success) {
            setAuthenticationAtom(state => {
                state.token = result.authenticationData.token
            })
        }
    
        return result
    }
    
    return { signIn }
}