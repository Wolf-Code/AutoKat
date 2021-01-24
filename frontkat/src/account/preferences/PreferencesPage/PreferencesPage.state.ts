import { useEffect } from 'react'
import { usePreferencesContext } from '../PreferencesContext'
import usePreferencesService from '../usePreferencesService'
import {
    PreferencesPageStateProps,
    PreferencesPageViewProps
} from './PreferencesPage.types'

export default (props: PreferencesPageStateProps): PreferencesPageViewProps => {
    const context = usePreferencesContext()
    const preferencesService = usePreferencesService()

    useEffect(() => {
        const retrieve = async() => {
            const result = await preferencesService.getPreferences()
            context.setPreferences(result)
        }

        retrieve()
    }, [])

    return {
        ...context,
        ...props
    }
}
