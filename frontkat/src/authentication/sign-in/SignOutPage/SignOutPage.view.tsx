import cx from 'classnames'
import Translation from 'core/translations/Translation'
import React from 'react'
import { SignOutPageViewProps } from './SignOutPage.types'

export default (props: SignOutPageViewProps) => {
    const {
        className,
        styles
    } = props

    const rootClasses = cx(styles.root, className)

    return (
        <div className={ rootClasses }>
            <Translation translation='AuthenticationTranslations.SignedOut' />
        </div>	
    )
}
