import { useHistory } from 'react-router-dom'
import useAuthenticationService from '../../useAuthenticationService'
import {
    SignInPageStateProps,
    SignInPageViewProps
} from './SignInPage.types'


export default (props: SignInPageStateProps): SignInPageViewProps => {
    const { signIn } = useAuthenticationService()
    const history = useHistory()

    const onSignIn = async(values: any) => {
        const {
            email,
            password
        } = values

        const result = await signIn(email, password)

        if (result.success) {
            history.push('/')
        }
    }

    return {
        onSignIn,
        ...props
    }
}
