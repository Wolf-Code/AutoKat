const fs = require('fs')
const glob = require('glob')
const babel = require("@babel/core")
const concat = require('concat')

const inputDir = './src/'
const concatFile = './src/scripts-concat.js'

glob(`../data/**/*.js`, (error, matches) => {
	matches.forEach(fs.unlinkSync);
})

glob(`${inputDir}**/*.js`, async (error, matches) => {
	await concat(matches, concatFile).then(() => {
		const contents = fs.readFileSync(concatFile)
		const contentString = contents.toString()

		const transformed = babel.transform(contentString, {
			compact: true,
			minified: true,
			comments: false
		})
		fs.writeFileSync(`../data/scripts.js`, transformed.code)
		fs.unlinkSync(concatFile)
	})
})