import { createComponent } from 'core/utilities/createComponent'
import styles from './SignInPage.module.scss'
import state from './SignInPage.state'
import {
    SignInPageStateProps,
    SignInPageViewProps
} from './SignInPage.types'
import view from './SignInPage.view'

export default createComponent<SignInPageStateProps, SignInPageViewProps>(view, {
    state,
    styles
})
