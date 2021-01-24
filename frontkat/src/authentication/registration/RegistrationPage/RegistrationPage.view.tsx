import React from 'react'
import cx from 'classnames'
import { RegistrationPageViewProps } from './RegistrationPage.types'

export default (props: RegistrationPageViewProps) => {
	const {
		className,
		styles
	} = props

	const rootClasses = cx(styles.root, className)

	return (
		<div className={ rootClasses }>
			
		</div>	
	)
}
