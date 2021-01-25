import useSafeRecoilState from 'core/utilities/useSafeRecoilState'
import {
    atom, selector
} from 'recoil'

const key = 'authentication'

interface StateType {
    token: undefined | string
}

const AuthenticationAtom = atom<StateType>({
    key,
    default: { token: undefined }
})

export const isSignedInSelector = selector({
    key: `${ key }-signed-in`,
    get: ({ get }) => {
        const state = get(AuthenticationAtom)
        
        return state.token !== undefined
    }
})

export default () => useSafeRecoilState(AuthenticationAtom)
// export default (): [StateType, (stateSetter: (state: StateType) => void) => void] => {
//     const [state, setter] = useRecoilState(AuthenticationAtom)

//     const safeSetter = useMemo(() => (stateSetter: (state: StateType) => void) => setter(curState => produce(curState, stateSetter)), [state, setter])

//     return [
//         state, 
//         safeSetter
//     ]
// }