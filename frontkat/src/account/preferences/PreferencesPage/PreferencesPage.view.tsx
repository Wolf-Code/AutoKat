import cx from 'classnames'
import React from 'react'
import { PreferencesPageViewProps } from './PreferencesPage.types'

export default (props: PreferencesPageViewProps) => {
    const {
        preferences: { language },
        className,
        styles
    } = props

    const rootClasses = cx(styles.root, className)

    return (
        <div className={ rootClasses }>
            { language }
        </div>
    )
}
