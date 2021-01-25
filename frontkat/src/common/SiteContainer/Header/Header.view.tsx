import { SettingOutlined } from '@ant-design/icons'
import {
    Layout,
    Menu
} from 'antd'
import cx from 'classnames'
import Translation from 'core/translations/Translation'
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
                                <Link to='/signin'>
                                    <Translation translation='AccountTranslations.SignIn' />
                                </Link>
                            </Menu.Item>
                            <Menu.Item>
                                <Link to='/register'>Register</Link>
                            </Menu.Item>
                        </>
                    )}

                    { isSignedIn && (
                        <>
                            <Menu.Item>
                                <Link to='/account'>
                                    <Translation translation='AccountTranslations.Name' />
                                </Link>
                            </Menu.Item>
                            <Menu.Item>
                                <Link to='/signout'>
                                    <Translation translation='AccountTranslations.SignOut' />
                                </Link>
                            </Menu.Item>
                        </>
                    )}
                </SubMenu>
            </Menu>
        </Header>	
    )
}
