import { createComponent } from 'core/utilities/createComponent'
import styles from './PreferencesPage.module.scss'
import state from './PreferencesPage.state'
import view from './PreferencesPage.view'
import { 
    PreferencesPageStateProps,
    PreferencesPageViewProps
} from './PreferencesPage.types'

export default createComponent<PreferencesPageStateProps, PreferencesPageViewProps>(view, {
    state,
    styles
})
