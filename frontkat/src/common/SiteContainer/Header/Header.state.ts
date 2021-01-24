import { useAuthenticationContext } from 'authentication/AuthenticationContext'
import {
    HeaderStateProps,
    HeaderViewProps
} from './Header.types'

export default (props: HeaderStateProps): HeaderViewProps => {
    const context = useAuthenticationContext()

    return {
        isSignedIn: context.isSignedIn(),
        ...props
    }
}
