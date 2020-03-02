const fs = require('fs')

const filePath = './build/output/main.js'
const contents = fs.readFileSync(filePath)
const contentString = contents.toString()

const transformed = babel.transform(contentString, {
	compact: true,
	minified: true,
	comments: false
})

fs.writeFileSync(filePath, transformed.code)