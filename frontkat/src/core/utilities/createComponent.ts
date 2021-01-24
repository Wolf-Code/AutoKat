import React from 'react'

export interface ComponentProps
{
	styles?: any
	children?: React.ReactNode
}

interface ComponentParts<TProps, TViewProps> {
	state?: (props: TProps) => TViewProps,
	styles?: any
}

export const createComponent = <TProps, TViewProps extends ComponentProps>(view: React.FunctionComponent<TViewProps>, parts: ComponentParts<TProps, TViewProps>) => {
	const component = (props: TProps) => {
		const { 
			state,
			styles
		} = parts

		let viewProps: any = {
			...props,
			styles
		}
		
		if (state) {
			const stateResult = state(props)
			viewProps = {
				...stateResult,
				styles
			}
		}

		return view(viewProps)
	}

	return component
}