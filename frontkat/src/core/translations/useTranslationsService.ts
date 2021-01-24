import useFetch from 'core/utilities/useFetch'
import { Translations } from './translations.type'

export default () => {
    const { get } = useFetch()

    const getTranslations = async(culture: string) => {
        const result = await get<Translations>(`translations/${ culture }`)

        return result
    }
    
    return { getTranslations }
}