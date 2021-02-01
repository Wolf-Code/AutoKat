import { useMemo } from 'react'
import {
    RecoilState,
    useRecoilState
} from 'recoil'

export default <TState>(atom: RecoilState<TState>): [TState, (stateSetter: (state: TState) => void) => void] => {
    const [atomState, atomSetter] = useRecoilState(atom)

    const safeSetter = useMemo(() => (stateSetter: (state: TState) => void) => {
        atomSetter(newState => {
            let copy = { ...newState }

            stateSetter(copy)

            return copy
        })
    }, [atomState, atomSetter])

    return [
        atomState, 
        safeSetter
    ]
}