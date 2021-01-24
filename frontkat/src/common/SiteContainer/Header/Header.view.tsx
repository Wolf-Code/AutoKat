import { SettingOutlined } from '@ant-design/icons'
import {
    Layout,
    Menu
} from 'antd'
import cx from 'classnames'
import React from 'react'
import { Link } from 'react-router-dom'
import { HeaderViewProps } from './Header.types'

const { SubMenu } = Menu
const { Header } = Layout


export default (props: HeaderViewProps) => {
    const {
        isSignedIn,
        className,
        styles
    } = props

    const rootClasses = cx(styles.root, className)

    return (
        <Header className={ cx('header', rootClasses) }>
            <Menu 
                theme='dark' 
                mode='horizontal' 
                defaultSelectedKeys={ ['2'] }
                className={ styles.menu }
            >
                <Menu.Item>
                    <Link to='/'>
                        Home
                    </Link>
                </Menu.Item>
                <SubMenu key='SubMenu' icon={ <SettingOutlined /> } title='Account'>
                    { !isSignedIn && (
                        <>
                            <Menu.Item>
                                <Link to='/signin'>Sign in</Link>
                            </Menu.Item>
                            <Menu.Item>
                                <Link to='/register'>Register</Link>
                            </Menu.Item>
                        </>
                    )}

                    { isSignedIn && (
                        <>
                            <Menu.Item>
                                <Link to='/account'>Account</Link>
                            </Menu.Item>
                            <Menu.Item>
                                <Link to='/signout'>Sign out</Link>
                            </Menu.Item>
                        </>
                    )}
                </SubMenu>
            </Menu>
        </Header>	
    )
}
