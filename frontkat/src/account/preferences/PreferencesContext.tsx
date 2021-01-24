import { useTranslationsContext } from 'core/translations/TranslationsContext'
import useTranslationsService from 'core/translations/useTranslationsService'
import React, {
    useEffect, useState
} from 'react'
import { UserPreferences } from './preferences.types'

interface StateType {
    preferences: UserPreferences
}

interface ContextType extends StateType {
    setPreferences: (preferences: UserPreferences) => void
}

const initialValue: ContextType = {
    preferences: { language: 'en-US' },
    setPreferences: () => {}
}

const PreferencesContext = React.createContext<ContextType>(initialValue)

export const usePreferencesContext = () => React.useContext(PreferencesContext)

export default (props: React.PropsWithChildren<any>) => {
    const { children } = props
    const [state, setState] = useState<StateType>({ preferences: initialValue.preferences })
    const translationsContext = useTranslationsContext()
    const translationsService = useTranslationsService()

    useEffect(() => {
        const retrieve = async() => {
            const translations = await translationsService.getTranslations(state.preferences.language)
            translationsContext.setTranslations(translations)
        }

        retrieve()
    }, [state.preferences.language])

    const setPreferences = (preferences: UserPreferences) => {
        setState({
            ...state,
            preferences
        })
    }

    return (
        <PreferencesContext.Provider value={ {
            preferences: state.preferences,
            setPreferences
        } }>
            { children }
        </PreferencesContext.Provider>
    )
}