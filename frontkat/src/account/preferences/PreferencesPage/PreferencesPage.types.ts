import { ComponentProps } from 'core/utilities/createComponent'
import { UserPreferences } from '../preferences.types'

export interface PreferencesPageStateProps extends ComponentProps {
    className?: string
}

export interface PreferencesPageViewProps extends PreferencesPageStateProps {
    preferences: UserPreferences
}
