import { View } from '../../router/View'
import { Link } from '../components/Link'

export const NotFound : View = {
	render: () => {
		return `<div>
			404: page not found. Click 
			${Link.render({
				label: "here",
				route: "/"
			})}
			to return to the main page.
		</div>`
	},
	preRender: () => {

	},
	postRender: () => {

	}
}