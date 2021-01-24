import React, { useState } from 'react'

interface StateType {
    token: undefined | string
}

interface ContextType extends StateType {
    setToken: (token: string) => void,
    isSignedIn: () => boolean
}

const initialValue: ContextType = {
    isSignedIn: () => false,
    setToken: () => {},
    token: undefined
}

const AuthenticationContext = React.createContext<ContextType>(initialValue)

export const useAuthenticationContext = () => React.useContext(AuthenticationContext)

export default (props: React.PropsWithChildren<any>) => {
    const { children } = props
    const [state, setState] = useState<StateType>({ token: undefined })

    const setToken = (token: string) => {
        setState({
            ...state,
            token
        })
    }

    const isSignedIn = (): boolean => state.token !== undefined

    return (
        <AuthenticationContext.Provider value={ {
            token: state.token,
            setToken,
            isSignedIn            
        } }>
            { children }
        </AuthenticationContext.Provider>
    )
}