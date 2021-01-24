import { createComponent } from 'core/utilities/createComponent'
import styles from './Header.module.scss'
import state from './Header.state'
import view from './Header.view'
import { 
    HeaderStateProps,
    HeaderViewProps
} from './Header.types'

export default createComponent<HeaderStateProps, HeaderViewProps>(view, {
    state,
    styles
})
