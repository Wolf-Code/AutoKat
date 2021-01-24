import useFetch from 'core/utilities/useFetch'
import { UserPreferences } from './preferences.types'


export default () => {
    const { get } = useFetch()

    const getPreferences = async() => {
        const result = await get<UserPreferences>('user/preferences')

        return result
    }
    
    return { getPreferences }
}