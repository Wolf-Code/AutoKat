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
		// Testing purposes:
		
		// const json = [{
		// 	name: "BimBamBommel",
		// 	strength: -12
		// },
		// {
		// 	name: "BimBamBommel 2",
		// 	strength: -18
		// }] as WiFiNetwork[]
		const json = (await data.json()) as WiFiNetwork[]

		let html = ''

		json.sort((a, b) => b.strength - a.strength)
		json.forEach(network => {
			html += `<div class='wifi-network' id='wifi-${network.name}'>
					<div class='label'>${network.name} - ${network.strength}</div>
					<div class='wifi-collapse' style='display: none'>
						<button type='button'>Connect</button>
						<input type='text' placeholder='password'></input>
					</div>
				</div>`
		})

		document.getElementById('wifi-list').innerHTML = html

		json.forEach(network => {
			const element = document.getElementById(`wifi-${network.name}`)
			const input = element.getElementsByTagName('input')[0]
			const button = element.getElementsByTagName('button')[0]
			const collapse = element.getElementsByClassName('wifi-collapse')[0]

			element.onclick = async () => {
				const collapses = document.getElementsByClassName('wifi-collapse')
				for(let i = 0; i < collapses.length; ++i)
				{
					collapses.item(i).setAttribute('style', 'display: none')
				}

				collapse.setAttribute("style", 'display: block')

				button.onclick = async () => {
					const payload = {
						ssid: network.name,
						password: input.value
					}
	
					const data = await fetch('/wifi', {
						method: 'POST',
						body: JSON.stringify(payload)
					})
				}
			}
		})
	}
}
