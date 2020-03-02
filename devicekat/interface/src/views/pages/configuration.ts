import { View } from '../../router/View'
import { Link } from '../components/Link'

export const Configuration : View = {
	render: () => {
		return `<div>
			dit is de hoofdpagina
			${Link.render({
				label: "test linkje",
				route: "/wifi"
			})}
		</div>`
	},
	preRender: () => {

	},
	postRender: () => {

	}
}