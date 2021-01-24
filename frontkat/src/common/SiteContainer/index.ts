import { createComponent } from 'core/utilities/createComponent'
import styles from './SiteContainer.module.scss'
import state from './SiteContainer.state'
import view from './SiteContainer.view'
import { 
    SiteContainerStateProps,
    SiteContainerViewProps
} from './SiteContainer.types'

export default createComponent<SiteContainerStateProps, SiteContainerViewProps>(view, {
    state,
    styles
})
