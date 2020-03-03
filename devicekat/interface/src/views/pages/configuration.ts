import { View } from '../../router/View'
import { Link } from '../components/Link'

export const Configuration : View = {
	render: () => {
		return `<div>
			<h1>Configuration</h1>
			${Link.render({
				label: "Wifi",
				route: "/wifi"
			})}
		</div>`
	},
	preRender: () => {

	},
	postRender: () => {

	}
}