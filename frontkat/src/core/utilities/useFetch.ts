import useAuthenticationAtom, { isSignedInSelector } from 'authentication/AuthenticationAtom'
import { useRecoilValue } from 'recoil'

const getUrl = (path: string) => `${ process.env.REACT_APP_API_PATH }/${ path }`

export default () => {
    const [authenticationAtom] = useAuthenticationAtom()
    const signedIn = useRecoilValue(isSignedInSelector)

    const headers = (): HeadersInit => {
        const requestHeaders: HeadersInit = new Headers()
        requestHeaders.set('Content-Type', 'application/json')

        if(signedIn) {
            requestHeaders.set('Authorization', `Bearer ${ authenticationAtom.token }`)
        }

        return requestHeaders
    }

    const get = async<TResponse>(path: string): Promise<TResponse> => {
        const url = getUrl(path)
        const result = await fetch(url, {
            headers: headers()
        })
        const data = await result.json()
    
        return data as TResponse
    }
    
    const post = async<TResponse>(path: string, body: any): Promise<TResponse> => {
        const url = getUrl(path)        

        const result = await fetch(url, {
            body: JSON.stringify(body),
            method: 'POST',
            headers: headers()
        })
        const data = await result.json()
    
        return data as TResponse
    }

    return {
        get,
        post
    }
}