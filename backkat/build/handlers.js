"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.registerRoutes = (app) => {
    app.get('/', (req, res) => {
        res.send('Hello world!');
    });
};
