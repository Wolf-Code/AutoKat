import cx from 'classnames'
import React from 'react'
import { TranslationViewProps } from './Translation.types'

export default (props: TranslationViewProps) => {
    const {
        translatedValue,
        className,
        styles
    } = props

    const rootClasses = cx(styles.root, className)

    return (
        <span className={ rootClasses }>
            { translatedValue }
        </span>
    )
}
