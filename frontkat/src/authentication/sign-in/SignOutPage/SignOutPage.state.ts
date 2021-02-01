import useAuthenticationService from 'authentication/useAuthenticationService'
import { useEffect } from 'react'
import {
    SignOutPageStateProps,
    SignOutPageViewProps
} from './SignOutPage.types'

export default (props: SignOutPageStateProps): SignOutPageViewProps => {
    const { signOut } = useAuthenticationService()

    useEffect(() => {
        const handleSignOut = async() => {
            await signOut()
        }
        
        handleSignOut()
    }, [])
    
    return props
}
