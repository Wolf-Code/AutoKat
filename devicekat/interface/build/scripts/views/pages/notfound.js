exports.__esModule = true;
var Link_1 = require("../components/Link");
exports.NotFound = {
    render: function () {
        return "<div>\n\t\t\t404: page not found. Click \n\t\t\t" + Link_1.Link.render({
            label: "here",
            route: "/"
        }) + "\n\t\t\tto return to the main page.\n\t\t</div>";
    },
    preRender: function () {
    },
    postRender: function () {
    }
};
