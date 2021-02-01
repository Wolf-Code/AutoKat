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

interface UserInformationResult {
    success: boolean,
    token: string
}

export default () => {
    const [, updateAuthenticationAtom] = useAuthenticationAtom()
    const { 
        get,
        post 
    } = useFetch()

    const signIn = async(email: string, password: string, rememberMe: boolean) => {
        const result = await post<SignInResult>('user/login', {
            email,
            password,
            rememberMe
        })

        if (result.success) {
            updateAuthenticationAtom(state => {
                state.token = result.authenticationData.token
            })
        }
    
        return result
    }

    const ensureSignedIn = async() => {
        const result = await get<UserInformationResult>('user')

        if (result.success) {
            updateAuthenticationAtom(state => {
                state.token = result.token
            })
        }
    }

    const signOut = async() => {
        await get('user/logout')

        updateAuthenticationAtom(state => {
            state.token = undefined
        })
    }
    
    return { 
        signIn,
        ensureSignedIn,
        signOut
    }
}