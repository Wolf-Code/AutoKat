import { Route } from './Route'
import { Configuration } from '../views/pages/configuration'
import { NotFound } from '../views/pages/notfound'
import { WiFi } from '../views/pages/wifi'

class Router {
	routes: Route[]

	registerRouter() {
		this.registerUrlHandlers()
		this.routes = [
			{
				route: '/',
				view: Configuration
			},
			{
				route: '/wifi',
				view: WiFi
			}
		]
	}

	registerUrlHandlers() {
		window.addEventListener('DOMContentLoaded', ev => {
			this.renderRoute()
		})

		window.addEventListener('hashchange', arg => {
			this.renderRoute()
		})
	}

	findCurrentRoute(): Route {
		const hash = (window.location.hash || '#/').substr(1) 
		const route = this.routes.find(x => x.route === hash)
		if (!route) {
			return {
				route: '',
				view: NotFound
			}
		}

		return route
	}

	renderRoute() {
		const route = this.findCurrentRoute()
		route.view.preRender && route.view.preRender()
		document.getElementById('router').innerHTML = route.view.render()
		route.view.postRender && route.view.postRender()
	}
}

export default new Router()
