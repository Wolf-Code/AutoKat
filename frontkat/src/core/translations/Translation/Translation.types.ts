import { ComponentProps } from 'core/utilities/createComponent'

export interface TranslationStateProps extends ComponentProps {
    className?: string,
    translation: string
}

export interface TranslationViewProps extends TranslationStateProps {
    translatedValue: string | undefined
}
