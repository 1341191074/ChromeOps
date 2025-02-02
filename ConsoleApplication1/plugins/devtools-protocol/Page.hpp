#pragma once
#include "nlohmann/json.hpp"
#include "BaseDomain.hpp"
#include "Types.hpp"
#include "Network.hpp"

class Page : public BaseDomain
{
public:
	// 本次请求的frameId
	PageTypes::FrameId frameId;
	// 本次亲求的loaderId
	NetworkTypes::LoaderId loaderId;
	// 本次请求的错误信息，如果有的话
	string errorText = "";
public:
	Page(AsyncDriver* mdriver) : BaseDomain(mdriver), frameId(""), loaderId("") {
		this->driver = mdriver;
		this->sendCommandNoWait("Page.enable", {});
	}

	/// <summary>
	/// 获得主框架ID
	/// </summary>
	/// <returns>FrameId</returns>
	PageTypes::FrameId getFrameTree() {
		map<string, std::variant<int, string, bool, float, nlohmann::json>> params;
		nlohmann::json retJson = this->sendCommandAndWait("Page.getFrameTree", params);
		string ret = retJson["frameTree"]["frame"]["id"];
		PageTypes::FrameId frameId(ret);
		return frameId;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="url">,URL to navigate the page to.</param>
	/// <param name="referrer">,Referrer URL</param>
	/// <param name="frameId">,Frame id to navigate, if not specified navigates the top frame.</param>
	void navigate(string url, string referrer) {
		map<string, std::variant<int, string, bool, float, nlohmann::json>> params;
		params["url"] = url;
		params["referrer"] = referrer;
		nlohmann::json res = this->sendCommandAndWait("Page.navigate", params);
		if (res.contains("frameId")) {
			frameId.frameId = res["frameId"];
		}
		if (res.contains("loaderId")) {
			loaderId.loaderId = res["loaderId"];
		}
		if (res.contains("errorText")) {
			errorText = res["errorText"];
		}
	}

	string captureFullScreenshot(string format, int quality) {
		return this->_captureScreenshot(format, quality, nullptr, true, true);
	}
	string captureScreenshot(string format, int quality, PageTypes::Clip* clip) {
		return this->_captureScreenshot(format, quality, clip);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="format">,Allowed Values: jpeg, png, webp</param>
	/// <param name="quality">,Compression quality from range [0..100] (jpeg only).</param>
	/// <param name="x">,X offset in device independent pixels (dip).</param>
	/// <param name="y">,Y offset in device independent pixels (dip).</param>
	/// <param name="width">,Rectangle width in device independent pixels (dip).</param>
	/// <param name="height">,Rectangle height in device independent pixels (dip).</param>
	/// <param name="scale">,Page scale factor.</param>
	/// <returns>Base64-encoded image data. (Encoded as a base64 string when passed over JSON)</returns>
	string _captureScreenshot(string format, int quality, PageTypes::Clip* clip, bool captureBeyondViewport = false, bool fromSurface = true) {
 		map<string, std::variant<int, string, bool, float, nlohmann::json>> params;
		params["format"] = format;
		params["quality"] = quality;
		params["captureBeyondViewport"] = captureBeyondViewport; // Defaults to false
		params["fromSurface"] = fromSurface; //Defaults to true
		if (clip != nullptr && clip->width > 0 && clip->height > 0) {
			nlohmann::json j = nlohmann::json{ {"x", clip->x}, {"y", clip->y}, {"width", clip->width}, {"height", clip->height}, {"scale", clip->scale} };
			params["clip"] = j;
		}
		nlohmann::json retJson = this->sendCommandAndWait("Page.captureScreenshot", params, 20000);
		if (retJson.contains("data")) {
			return retJson["data"];
		}
		return "";
	}
	void handleJavaScriptDialog(bool accept, string promptText) {
		map<string, std::variant<int, string, bool, float, nlohmann::json>> params;
		params["accept"] = accept;
		params["promptText"] = promptText;
		this->sendCommandNoWait("Page.handleJavaScriptDialog", params);
	}

	void bringToFront() {
		this->sendCommandNoWait("Page.bringToFront", {});
	}

};

