const path = require('path');

module.exports = {
	entry: './build/scripts/index.js',
	output: {
		filename: 'main.js',
		path: path.resolve(__dirname, 'build/output'),
	},
};