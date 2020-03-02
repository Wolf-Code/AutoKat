exports.__esModule = true;
var configuration_1 = require("../views/pages/configuration");
var notfound_1 = require("../views/pages/notfound");
var wifi_1 = require("../views/pages/wifi");
var Router = /** @class */ (function () {
    function Router() {
    }
    Router.prototype.registerRouter = function () {
        this.registerUrlHandlers();
        this.routes = [
            {
                route: '/',
                view: configuration_1.Configuration
            },
            {
                route: '/wifi',
                view: wifi_1.WiFi
            }
        ];
    };
    Router.prototype.registerUrlHandlers = function () {
        var _this = this;
        window.addEventListener('DOMContentLoaded', function (ev) {
            _this.renderRoute();
        });
        window.addEventListener('hashchange', function (arg) {
            _this.renderRoute();
        });
    };
    Router.prototype.findCurrentRoute = function () {
        var hash = (window.location.hash || '#/').substr(1);
        var route = this.routes.find(function (x) { return x.route === hash; });
        if (!route) {
            return {
                route: '',
                view: notfound_1.NotFound
            };
        }
        return route;
    };
    Router.prototype.renderRoute = function () {
        var route = this.findCurrentRoute();
        route.view.preRender && route.view.preRender();
        document.getElementById('router').innerHTML = route.view.render();
        route.view.postRender && route.view.postRender();
    };
    return Router;
}());
exports["default"] = new Router();
