import { Layout } from 'antd'
import cx from 'classnames'
import React from 'react'
import HamburgerMenu from './HamburgerMenu'
import Header from './Header'
import { SiteContainerViewProps } from './SiteContainer.types'

const { Content } = Layout

export default (props: SiteContainerViewProps) => {
    const {
        children,
        className,
        styles
    } = props

    const rootClasses = cx(styles.root, className)

    return (
        <Layout className={ rootClasses }>
            <Header />
            <Layout>
                <HamburgerMenu />
                <Layout style={ { padding: '0 24px 24px' } }>
                    <Content
                        className='site-layout-background'
                        style={ {
                            padding: 24,
                            margin: 0,
                            minHeight: 280
                        } }
                    >
                        { children }
                    </Content>
                </Layout>
            </Layout>
        </Layout>
    )
}
