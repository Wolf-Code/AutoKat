const fs = require('fs')

const pathHtml = './build/index.html'
const pathJs = './build/output/main.js'
const pathCss = './build/styles.css'

const html = fs.readFileSync(pathHtml).toString()
const scripts = fs.readFileSync(pathJs).toString()
const styles = fs.readFileSync(pathCss).toString().trim()

const combined = `${html}<script>${scripts}</script><style>${styles}</style>`
fs.writeFileSync(`./build/output.html`, combined)

fs.unlinkSync(pathHtml)
fs.unlinkSync(pathJs)
fs.unlinkSync(pathCss)