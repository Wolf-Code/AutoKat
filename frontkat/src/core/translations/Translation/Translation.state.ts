import { useTranslationsContext } from '../TranslationsContext'
import {
    TranslationStateProps,
    TranslationViewProps
} from './Translation.types'

export default (props: TranslationStateProps): TranslationViewProps => {
    const { translation } = props
    const translationsContext = useTranslationsContext()

    const value = translationsContext.getTranslation(translation)

    return {
        ...props,
        translatedValue: value
    }
}
