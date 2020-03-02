exports.__esModule = true;
var configuration_1 = require("../views/pages/configuration");
var Router = /** @class */ (function () {
    function Router() {
        this.registerRouter();
    }
    Router.prototype.registerRouter = function () {
        this.routes = [
            {
                route: '/',
                view: configuration_1.Configuration
            }
        ];
    };
    Router.prototype.findCurrentRoute = function () {
        return this.routes[0];
    };
    Router.prototype.renderRoute = function () {
        var route = this.findCurrentRoute();
        route.view.preRender();
        document.getElementById("router").innerHTML = route.view.render();
        route.view.postRender();
    };
    return Router;
}());
exports["default"] = new Router();
