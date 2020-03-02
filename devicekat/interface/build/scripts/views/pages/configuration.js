exports.__esModule = true;
var Link_1 = require("../components/Link");
exports.Configuration = {
    render: function () {
        return "<div>\n\t\t\tdit is de hoofdpagina\n\t\t\t" + Link_1.Link.render({
            label: "test linkje",
            route: "/wifi"
        }) + "\n\t\t</div>";
    },
    preRender: function () {
    },
    postRender: function () {
    }
};
