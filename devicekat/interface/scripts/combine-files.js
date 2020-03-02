const fs = require('fs')

const pathHtml = './build/index.html'
const pathJs = './build/output/main.js'
const pathCss = './build/styles.css'

const html = fs.readFileSync(pathHtml).toString()
const scripts = fs.readFileSync(pathJs).toString()
const styles = fs.readFileSync(pathCss).toString().trim()

const combined = `<style>${styles}</style>${html}<script>${scripts}</script>`
fs.writeFileSync(`./build/output.html`, combined)

let combinedSafe = combined
combinedSafe = combinedSafe.replace(/\\/g, '\\\\')
combinedSafe = combinedSafe.replace(/\"/g,'\\"')
fs.writeFileSync(`./build/output-safe.html`, combinedSafe)

fs.unlinkSync(pathHtml)
fs.unlinkSync(pathJs)
fs.unlinkSync(pathCss)