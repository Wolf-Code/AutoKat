#include "ConfigurationServer.h"
#include <WifiAccess.h>
#include <Logger.h>
#include <StorageHelper.h>
#include <StorageData.h>
#include <DeviceHelper.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <AsyncJson.h>

AsyncWebServer ConfigurationServer::server(80);
DNSServer ConfigurationServer::dnsServer;
const int dnsPort = 53;
const char htmlSpa[] PROGMEM = "<style>body .container{width:100%;max-width:600px;margin:auto;background-color:lightgrey}</style><div id=router class=container></div><script>!function(t){var e={};function n(r){if(e[r])return e[r].exports;var o=e[r]={i:r,l:!1,exports:{}};return t[r].call(o.exports,o,o.exports,n),o.l=!0,o.exports}n.m=t,n.c=e,n.d=function(t,e,r){n.o(t,e)||Object.defineProperty(t,e,{enumerable:!0,get:r})},n.r=function(t){\"undefined\"!=typeof Symbol&&Symbol.toStringTag&&Object.defineProperty(t,Symbol.toStringTag,{value:\"Module\"}),Object.defineProperty(t,\"__esModule\",{value:!0})},n.t=function(t,e){if(1&e&&(t=n(t)),8&e)return t;if(4&e&&\"object\"==typeof t&&t&&t.__esModule)return t;var r=Object.create(null);if(n.r(r),Object.defineProperty(r,\"default\",{enumerable:!0,value:t}),2&e&&\"string\"!=typeof t)for(var o in t)n.d(r,o,function(e){return t[e]}.bind(null,o));return r},n.n=function(t){var e=t&&t.__esModule?function(){return t.default}:function(){return t};return n.d(e,\"a\",e),e},n.o=function(t,e){return Object.prototype.hasOwnProperty.call(t,e)},n.p=\"\",n(n.s=1)}([function(t,e){e.__esModule=!0,e.Link={render:function(t){return'<a href=\"#'+t.route+'\">'+t.label+\"</a>\"}}},function(t,e,n){e.__esModule=!0,n(2).default.registerRouter()},function(t,e,n){e.__esModule=!0;var r=n(3),o=n(4),i=n(5),u=function(){function t(){}return t.prototype.registerRouter=function(){this.registerUrlHandlers(),this.routes=[{route:\"/\",view:r.Configuration},{route:\"/wifi\",view:i.WiFi}]},t.prototype.registerUrlHandlers=function(){var t=this;window.addEventListener(\"DOMContentLoaded\",(function(e){t.renderRoute()})),window.addEventListener(\"hashchange\",(function(e){t.renderRoute()}))},t.prototype.findCurrentRoute=function(){var t=(window.location.hash||\"#/\").substr(1),e=this.routes.find((function(e){return e.route===t}));return e||{route:\"\",view:o.NotFound}},t.prototype.renderRoute=function(){var t=this.findCurrentRoute();t.view.preRender&&t.view.preRender(),document.getElementById(\"router\").innerHTML=t.view.render(),t.view.postRender&&t.view.postRender()},t}();e.default=new u},function(t,e,n){e.__esModule=!0;var r=n(0);e.Configuration={render:function(){return\"<div>\\n\\t\\t\\tdit is de hoofdpagina\\n\\t\\t\\t\"+r.Link.render({label:\"test linkje\",route:\"/wifi\"})+\"\\n\\t\\t</div>\"},preRender:function(){},postRender:function(){}}},function(t,e,n){e.__esModule=!0;var r=n(0);e.NotFound={render:function(){return\"<div>\\n\\t\\t\\t404: page not found. Click \\n\\t\\t\\t\"+r.Link.render({label:\"here\",route:\"/\"})+\"\\n\\t\\t\\tto return to the main page.\\n\\t\\t</div>\"},preRender:function(){},postRender:function(){}}},function(t,e){var n=this&&this.__awaiter||function(t,e,n,r){return new(n||(n=Promise))((function(o,i){function u(t){try{c(r.next(t))}catch(t){i(t)}}function a(t){try{c(r.throw(t))}catch(t){i(t)}}function c(t){var e;t.done?o(t.value):(e=t.value,e instanceof n?e:new n((function(t){t(e)}))).then(u,a)}c((r=r.apply(t,e||[])).next())}))},r=this&&this.__generator||function(t,e){var n,r,o,i,u={label:0,sent:function(){if(1&o[0])throw o[1];return o[1]},trys:[],ops:[]};return i={next:a(0),throw:a(1),return:a(2)},\"function\"==typeof Symbol&&(i[Symbol.iterator]=function(){return this}),i;function a(i){return function(a){return function(i){if(n)throw new TypeError(\"Generator is already executing.\");for(;u;)try{if(n=1,r&&(o=2&i[0]?r.return:i[0]?r.throw||((o=r.return)&&o.call(r),0):r.next)&&!(o=o.call(r,i[1])).done)return o;switch(r=0,o&&(i=[2&i[0],o.value]),i[0]){case 0:case 1:o=i;break;case 4:return u.label++,{value:i[1],done:!1};case 5:u.label++,r=i[1],i=[0];continue;case 7:i=u.ops.pop(),u.trys.pop();continue;default:if(!(o=(o=u.trys).length>0&&o[o.length-1])&&(6===i[0]||2===i[0])){u=0;continue}if(3===i[0]&&(!o||i[1]>o[0]&&i[1]<o[3])){u.label=i[1];break}if(6===i[0]&&u.label<o[1]){u.label=o[1],o=i;break}if(o&&u.label<o[2]){u.label=o[2],u.ops.push(i);break}o[2]&&u.ops.pop(),u.trys.pop();continue}i=e.call(t,u)}catch(t){i=[6,t],r=0}finally{n=o=0}if(5&i[0])throw i[1];return{value:i[0]?i[1]:void 0,done:!0}}([i,a])}}},o=this;e.__esModule=!0,e.WiFi={render:function(){return'<div id=\"wifi-list\">\\n\\t\\t\\t\\tLoading..\\n\\t\\t\\t</div>'},postRender:function(){return n(o,void 0,void 0,(function(){var t,e,o=this;return r(this,(function(i){switch(i.label){case 0:return[4,fetch(\"/wifi\",{method:\"GET\"})];case 1:return[4,i.sent().json()];case 2:return t=i.sent(),e=\"\",t.sort((function(t,e){return e.strength-t.strength})),t.forEach((function(t){e+=\"<div id='wifi-\"+t.name+\"'>\\n\\t\\t\\t\\t\\t<p>\"+t.name+\" - \"+t.strength+\"</p>\\n\\t\\t\\t\\t\\t<input type='text' placeholder='password'></input>\\n\\t\\t\\t\\t\\t<button>Connect</button>\\n\\t\\t\\t\\t</div>\"})),document.getElementById(\"wifi-list\").innerHTML=e,t.forEach((function(t){var e=document.getElementById(\"wifi-\"+t.name),i=e.getElementsByTagName(\"input\")[0];e.getElementsByTagName(\"button\")[0].onclick=function(){return n(o,void 0,void 0,(function(){var e,n;return r(this,(function(r){switch(r.label){case 0:return e={ssid:t.name,password:i.value},[4,fetch(\"/wifi\",{method:\"POST\",body:JSON.stringify(e)})];case 1:return n=r.sent(),console.log(e,n.status),[2]}}))}))}})),[2]}}))}))}}}]);</script>";

void ConfigurationServer::start()
{
	server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
		request->send_P(200, "text/html", htmlSpa);
	});

	// server.on("/save", HTTP_POST, [](AsyncWebServerRequest *request) {
	// 	Logger::debugLine("handling /save");

	// 	StorageData storageData = StorageHelper::getStorageData();

	// 	if (request->hasParam("server", true))
	// 	{
	// 		storageData.serverUrl = request->getParam("server", true)->value();
	// 	}

	// 	if (request->hasParam("ssid", true))
	// 	{
	// 		storageData.wifiSSID = request->getParam("ssid", true)->value();
	// 	}

	// 	if (request->hasParam("password", true))
	// 	{
	// 		storageData.wifiPassword = request->getParam("password", true)->value();
	// 	}

	// 	StorageHelper::saveStorageData(storageData);
	// 	request->send(200, "text/html", htmlSuccess);
	// 	DeviceHelper::restart();
	// });

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
		dnsServer.start(dnsPort, "*", WiFi.softAPIP());
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