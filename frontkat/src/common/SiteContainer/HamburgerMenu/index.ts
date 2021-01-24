import { createComponent } from 'core/utilities/createComponent'
import styles from './HamburgerMenu.module.scss'
import state from './HamburgerMenu.state'
import view from './HamburgerMenu.view'
import { 
    HamburgerMenuStateProps,
    HamburgerMenuViewProps
} from './HamburgerMenu.types'

export default createComponent<HamburgerMenuStateProps, HamburgerMenuViewProps>(view, {
    state,
    styles
})
