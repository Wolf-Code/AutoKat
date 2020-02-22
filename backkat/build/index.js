"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const express_1 = __importDefault(require("express"));
const handlers_1 = require("./handlers");
const app = express_1.default();
const port = 8080; // default port to listen
handlers_1.registerRoutes(app);
// start the Express server
app.listen(port, () => {
    console.log(`server started at http://localhost:${port}`);
});
