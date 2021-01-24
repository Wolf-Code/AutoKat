import { ComponentProps } from 'core/utilities/createComponent'

export interface SignInPageStateProps extends ComponentProps {
	className?: string
}

export interface SignInPageViewProps extends SignInPageStateProps {
	onSignIn: (values: any) => void
}
