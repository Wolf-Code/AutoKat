import React, { useState } from 'react'
import { Translations } from './translations.type'

interface StateType {
    translations: Translations
}

interface ContextType extends StateType {
    getTranslation: (key: string) => string | undefined,
    setTranslations: (translations: Translations) => void
}

const initialValue: ContextType = {
    translations: {},
    getTranslation: () => undefined,
    setTranslations: () => {}
}

const TranslationsContext = React.createContext<ContextType>(initialValue)

export const useTranslationsContext = () => React.useContext(TranslationsContext)

export default (props: React.PropsWithChildren<any>) => {
    const { children } = props
    const [state, setState] = useState<StateType>({ translations: {} })

    const getTranslation = (key: string) => state.translations[key]
    const setTranslations = (translations: Translations) => {
        setState({
            ...state,
            translations
        })
    }

    return (
        <TranslationsContext.Provider value={ {
            translations: state.translations,
            getTranslation,
            setTranslations        
        } }>
            { children }
        </TranslationsContext.Provider>
    )
}