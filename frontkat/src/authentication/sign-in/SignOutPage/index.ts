import { createComponent } from 'core/utilities/createComponent'
import styles from './SignOutPage.module.scss'
import state from './SignOutPage.state'
import view from './SignOutPage.view'
import { 
    SignOutPageStateProps,
    SignOutPageViewProps
} from './SignOutPage.types'

export default createComponent<SignOutPageStateProps, SignOutPageViewProps>(view, {
    state,
    styles
})
