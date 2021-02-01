import {
    Button,
    Checkbox,
    Form,
    Input
} from 'antd'
import cx from 'classnames'
import Translation from 'core/translations/Translation'
import React from 'react'
import { SignInPageViewProps } from './SignInPage.types'

export default (props: SignInPageViewProps) => {
    const {
        onSignIn,
        className,
        styles
    } = props

    const rootClasses = cx(styles.root, className)

    return (
        <div className={ rootClasses }>
            <Form
                onFinish={ onSignIn }
            >
                <Form.Item
                    label={ <Translation translation='AuthenticationTranslations.Email'/> }
                    name='email'
                    rules={ [{
                        required: true,
                        message: 'Please input your email address!' 
                    }] }
                >
                    <Input />
                </Form.Item>
                <Form.Item
                    label={ <Translation translation='AuthenticationTranslations.Password'/> }
                    name='password'
                    rules={ [{
                        required: true,
                        message: 'Please input your password!' 
                    }] }
                >
                    <Input.Password />
                </Form.Item>

                <Form.Item 
                    name='rememberMe' 
                    valuePropName='checked'
                >
                    <Checkbox>
                        <Translation translation='AuthenticationTranslations.RememberMe'/>
                    </Checkbox>
                </Form.Item>

                <Form.Item>
                    <Button type='primary' htmlType='submit'>
                        Submit
                    </Button>
                </Form.Item>
            </Form>
        </div>	
    )
}
