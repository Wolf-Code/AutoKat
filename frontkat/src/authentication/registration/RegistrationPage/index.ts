import { createComponent } from 'core/utilities/createComponent'
import styles from './RegistrationPage.module.scss'
import state from './RegistrationPage.state'
import {
	RegistrationPageStateProps,
	RegistrationPageViewProps
} from './RegistrationPage.types'
import view from './RegistrationPage.view'

export default createComponent<RegistrationPageStateProps, RegistrationPageViewProps>(view, {
	state,
	styles
})
