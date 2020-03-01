modules.success = {}
modules.success.init = () => {
	let count = 5
	const callback = () => {
		document.getElementById('reloader').innerHTML = "Reloading page in " + count + " seconds.."
		count--
		if(count < 0)
		{
			window.location.replace('/')
		}
	}

	setInterval(callback, 1000)
	callback()
}
