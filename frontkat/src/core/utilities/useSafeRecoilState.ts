import { produce } from 'immer'
import { useMemo } from 'react'
import {
    RecoilState, useRecoilState
} from 'recoil'

export default <TState>(atom: RecoilState<TState>): [TState, (stateSetter: (state: TState) => void) => void] => {
    const [state, setter] = useRecoilState(atom)

    const safeSetter = useMemo(() => (stateSetter: (state: TState) => void) => setter(curState => produce(curState, stateSetter)), [state, setter])

    return [
        state, 
        safeSetter
    ]
}