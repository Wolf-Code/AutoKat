import { View } from '../../router/View'
import { Link } from '../components/Link'
import { WiFiNetwork } from '../../wifi/WiFiNetwork'

export const WiFi: View = {
	render: () => {
		return `<div id="wifi-list">
				Loading..
			</div>`
	},
	postRender: async () => {
		const data = await fetch('/wifi', {
			method: 'GET'
		})
		const json = (await data.json()) as WiFiNetwork[]

		let html = ''

		json.sort((a, b) => b.strength - a.strength)
		json.forEach(network => {
			html += `<div id='wifi-${network.name}'>
					<p>${network.name} - ${network.strength}</p>
					<input type='text' placeholder='password'></input>
					<button>Connect</button>
				</div>`
		})

		document.getElementById('wifi-list').innerHTML = html

		json.forEach(network => {
			const element = document.getElementById(`wifi-${network.name}`)
			const input = element.getElementsByTagName('input')[0]
			const button = element.getElementsByTagName('button')[0]

			button.onclick = async () => {
				const payload = {
					ssid: network.name,
					password: input.value
				}

				const data = await fetch('/wifi', {
					method: 'POST',
					body: JSON.stringify(payload)
				})
				console.log(payload, data.status)
			}
		})
	}
}
