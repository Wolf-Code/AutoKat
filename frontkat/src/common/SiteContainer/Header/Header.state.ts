import { isSignedInSelector } from 'authentication/AuthenticationAtom'
import { useRecoilValue } from 'recoil'
import {
    HeaderStateProps,
    HeaderViewProps
} from './Header.types'

export default (props: HeaderStateProps): HeaderViewProps => {
    const signedIn = useRecoilValue(isSignedInSelector)

    return {
        isSignedIn: signedIn,
        ...props
    }
}
