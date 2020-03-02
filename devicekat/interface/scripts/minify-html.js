const minify = require('html-minifier').minify;
const fs = require('fs')

const content = fs.readFileSync('./index.html').toString()

const result = minify(content, {
	removeAttributeQuotes: true,
	collapseBooleanAttributes: true,
	collapseInlineTagWhitespace: true,
	collapseWhitespace: true,
	quoteCharacter: "'",
	removeEmptyAttributes: true,
	removeComments: true,
	removeOptionalTags: true,
	removeRedundantAttributes: true,
	removeScriptTypeAttributes: true,
	removeStyleLinkTypeAttributes: true,
	removeTagWhitespace: true,
	useShortDoctype: true
});

fs.writeFileSync('./build/index.html', result)