import { createComponent } from 'core/utilities/createComponent'
import styles from './Translation.module.scss'
import state from './Translation.state'
import view from './Translation.view'
import { 
    TranslationStateProps,
    TranslationViewProps
} from './Translation.types'

export default createComponent<TranslationStateProps, TranslationViewProps>(view, {
    state,
    styles
})
