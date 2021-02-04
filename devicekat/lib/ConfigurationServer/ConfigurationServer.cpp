#include "ConfigurationServer.h"
#include <WifiAccess.h>
#include <Logger.h>
#include <StorageHelper.h>
#include <StorageData.h>
#include <DeviceHelper.h>
#include <ArduinoJson.h>
#include <AsyncJson.h>

AsyncWebServer ConfigurationServer::server(80);
DNSServer ConfigurationServer::dnsServer;
const int dnsPort = 53;
const char htmlSpa[] PROGMEM = "<style>body #router{padding:20px;border-radius:5px;max-width:700px;margin:0 auto;display:flex;flex-direction:column;background-color:#f0f0f0}h1{font-size:1rem}.wifi-network{background-color:#7ae7c7;border-radius:5px;padding:5px;margin-bottom:2px}.wifi-network:hover{background-color:#75bba7}</style><div id=router></div><script>!function(t,e){\"object\"==typeof exports&&\"undefined\"!=typeof module?e():\"function\"==typeof define&&define.amd?define(e):e()}(0,function(){var t=function(t){return'<a href=\"#'+t.route+'\">'+t.label+\"</a>\"},e={render:function(){return\"<div>\\n\\t\\t\\t<h1>Configuration</h1>\\n\\t\\t\\t\"+t({label:\"Wifi\",route:\"/wifi\"})+\"\\n\\t\\t</div>\"},preRender:function(){},postRender:function(){}},n={render:function(){return\"<div>\\n\\t\\t\\t404: page not found. Click \\n\\t\\t\\t\"+t({label:\"here\",route:\"/\"})+\"\\n\\t\\t\\tto return to the main page.\\n\\t\\t</div>\"},preRender:function(){},postRender:function(){}},r={render:function(){return'<div id=\"wifi-list\">\\n\\t\\t\\t\\tLoading..\\n\\t\\t\\t</div>'},postRender:function(){try{return Promise.resolve(fetch(\"/wifi\",{method:\"GET\"})).then(function(t){return Promise.resolve(t.json()).then(function(t){var e=\"\";t.sort(function(t,e){return e.strength-t.strength}),t.forEach(function(t){e+=\"<div class='wifi-network' id='wifi-\"+t.name+\"'>\\n\\t\\t\\t\\t\\t<div class='label'>\"+t.name+\" - \"+t.strength+\"</div>\\n\\t\\t\\t\\t\\t<div class='wifi-collapse' style='display: none'>\\n\\t\\t\\t\\t\\t\\t<button type='button'>Connect</button>\\n\\t\\t\\t\\t\\t\\t<input type='text' placeholder='password'></input>\\n\\t\\t\\t\\t\\t</div>\\n\\t\\t\\t\\t</div>\"}),document.getElementById(\"wifi-list\").innerHTML=e,t.forEach(function(t){var e=document.getElementById(\"wifi-\"+t.name),n=e.getElementsByTagName(\"input\")[0],r=e.getElementsByTagName(\"button\")[0],i=e.getElementsByClassName(\"wifi-collapse\")[0];e.onclick=function(){try{for(var e=document.getElementsByClassName(\"wifi-collapse\"),o=0;o<e.length;++o)e.item(o).setAttribute(\"style\",\"display: none\");return i.setAttribute(\"style\",\"display: block\"),r.onclick=function(){try{return Promise.resolve(fetch(\"/wifi\",{method:\"POST\",body:JSON.stringify({ssid:t.name,password:n.value})})).then(function(){})}catch(t){return Promise.reject(t)}},Promise.resolve()}catch(t){return Promise.reject(t)}}})})})}catch(t){return Promise.reject(t)}}},i=function(){};i.prototype.registerRouter=function(){this.registerUrlHandlers(),this.routes=[{route:\"/\",view:e},{route:\"/wifi\",view:r}]},i.prototype.registerUrlHandlers=function(){var t=this;window.addEventListener(\"DOMContentLoaded\",function(e){t.renderRoute()}),window.addEventListener(\"hashchange\",function(e){t.renderRoute()})},i.prototype.findCurrentRoute=function(){var t=(window.location.hash||\"#/\").substr(1);return this.routes.find(function(e){return e.route===t})||{route:\"\",view:n}},i.prototype.renderRoute=function(){var t=this.findCurrentRoute();t.view.preRender&&t.view.preRender(),document.getElementById(\"router\").innerHTML=t.view.render(),t.view.postRender&&t.view.postRender()},(new i).registerRouter()});</script>";

void ConfigurationServer::start()
{
	server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
		request->send_P(200, "text/html", htmlSpa);
	});

	server.on("/wifi", HTTP_GET, [](AsyncWebServerRequest *request) {
		AsyncJsonResponse *response = new AsyncJsonResponse(true);

		JsonVariant &root = response->getRoot();
		const unsigned int n = WifiAccess::getNetworksCount();
		for (unsigned int i = 0; i < n; ++i)
		{
			const WifiNetwork network = WifiAccess::getWifiNetwork(i);
			JsonObject obj = root.createNestedObject();
			obj["name"] = network.name;
			obj["strength"] = network.strength;
		}
		response->setLength();
		request->send(response);
	});

	// server.on("/wifi", HTTP_POST, [](AsyncWebServerRequest *request) {

	// });

	server.onRequestBody([](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
		if (request->url() == "/wifi")
		{
			DynamicJsonDocument json(1024);
			deserializeJson(json, (const char *)data);
			const String ssid = json["ssid"];
			const String password = json["password"];

			StorageData storageData = StorageHelper::getStorageData();
			storageData.wifiSSID = ssid;
			storageData.wifiPassword = password;

			StorageHelper::saveStorageData(storageData);
			request->send(200);
			server.end();
			DeviceHelper::restart();
		}
	});

	// server.serveStatic("/scripts.js", SPIFFS, "/scripts.js");
	// server.serveStatic("/styles.css", SPIFFS, "/styles.css");

	server.onNotFound([](AsyncWebServerRequest *request) {
		request->send(404, "text/plain", "Die is er niet vriend");
	});

	server.begin();
	if (WifiAccess::isSoftAP())
	{
		dnsServer.start(dnsPort, "*", WifiAccess::getSoftApIp());
	}
	Logger::debugLine("Starting configuration server");
}

void ConfigurationServer::debugAsyncWebServerRequest(AsyncWebServerRequest *request)
{
	const int params = request->params();
	Serial.printf("%d params sent in\n", params);
	for (int i = 0; i < params; i++)
	{
		AsyncWebParameter *p = request->getParam(i);
		if (p->isFile())
		{
			Serial.printf("_FILE[%s]: %s, size: %u\n", p->name().c_str(), p->value().c_str(), p->size());
		}
		else if (p->isPost())
		{
			Serial.printf("_POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
		}
		else
		{
			Serial.printf("_GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
		}
	}
}

void ConfigurationServer::loop()
{
	if (WifiAccess::isSoftAP())
	{
		dnsServer.processNextRequest();
	}
}