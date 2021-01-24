import { ComponentProps } from 'core/utilities/createComponent'

export interface HeaderStateProps extends ComponentProps {
    className?: string
}

export interface HeaderViewProps extends HeaderStateProps {
    isSignedIn: boolean
}
