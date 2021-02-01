import { usePreferencesContext } from 'account/preferences/PreferencesContext'
import usePreferencesService from 'account/preferences/usePreferencesService'
import { isSignedInSelector } from 'authentication/AuthenticationAtom'
import { useEffect } from 'react'
import { useHistory } from 'react-router-dom'
import { useRecoilValue } from 'recoil'
import useAuthenticationService from '../../useAuthenticationService'
import {
    SignInPageStateProps,
    SignInPageViewProps
} from './SignInPage.types'


export default (props: SignInPageStateProps): SignInPageViewProps => {
    const { signIn } = useAuthenticationService()
    const signedIn = useRecoilValue(isSignedInSelector)
    const history = useHistory()

    const context = usePreferencesContext()
    const preferencesService = usePreferencesService()

    const retrievePreferences = async() => {
        const result = await preferencesService.getPreferences()
        context.setPreferences(result)
    }

    const onSignIn = async(values: any) => {
        const {
            email,
            password,
            rememberMe
        } = values

        await signIn(email, password, rememberMe)
    }

    useEffect(() => {
        if (!signedIn) {
            return
        }

        const handler = async() => {
            history.replace('/')
            await retrievePreferences()
        }
        
        handler()
    }, [signedIn])

    return {
        onSignIn,
        ...props
    }
}
