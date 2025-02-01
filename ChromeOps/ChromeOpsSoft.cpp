// ChromeOpsSoft.cpp: CChromeOpsSoft 的实现
#include "pch.h"
#include <string>
#include "ChromeOpsSoft.h"

// CChromeOpsSoft
STDMETHODIMP CChromeOpsSoft::getVersion(BSTR* retVal)
{
    CComBSTR version(L"1.0.0.2");
    *retVal = version.Detach();
    ::SysFreeString(version);
    return S_OK;
}

STDMETHODIMP CChromeOpsSoft::chromeBind(BSTR host, int port, int* retVal)
{
    *retVal = this->chrome->chromeBind(this->stringUtils.BSTRToString(host), port);// 0=失败，1=成功
    return S_OK;
}

STDMETHODIMP CChromeOpsSoft::pushArgs(BSTR arg)
{
    this->chrome->pushArgs(this->stringUtils.BSTRToString(arg));
    return S_OK;
}

STDMETHODIMP CChromeOpsSoft::launch(BSTR chromeFullPath, int tryBind, int* retVal)
{
    this->chrome->launch(this->stringUtils.BSTRToString(chromeFullPath), tryBind);
    *retVal = 1;
    return S_OK;
}

STDMETHODIMP CChromeOpsSoft::findTargetList(BSTR* targetList)
{
    std::string ret = this->chrome->findTargetList();
    *targetList = this->stringUtils.stringToBSTR(ret);
    return S_OK;
}

STDMETHODIMP CChromeOpsSoft::switchTab(BSTR tabId, int* retVal)
{
    *retVal = this->chrome->switchTab(this->stringUtils.BSTRToString(tabId));
    return S_OK;
}

STDMETHODIMP CChromeOpsSoft::getOuterHTML(BSTR selector, BSTR* retVal)
{
    string ret = this->chrome->getOuterHTML(this->stringUtils.BSTRToString(selector));
    *retVal = this->stringUtils.stringToBSTR(ret);
    return S_OK;
}

STDMETHODIMP CChromeOpsSoft::navigate(BSTR url, BSTR referrer)
{
    this->chrome->navigate(this->stringUtils.BSTRToString(url), this->stringUtils.BSTRToString(referrer));
    return S_OK;
}

STDMETHODIMP CChromeOpsSoft::isLoadingFinished(int* retVal)
{
    *retVal = this->chrome->isLoadingFinished();
    return S_OK;
}

STDMETHODIMP CChromeOpsSoft::runScript(BSTR expression, BSTR* retVal)
{
    string ret = this->chrome->runScript(this->stringUtils.BSTRToString(expression));
    *retVal = this->stringUtils.stringToBSTR(ret);
    return S_OK;
}

STDMETHODIMP CChromeOpsSoft::captureFullScreenshot(BSTR format, int quality, BSTR imgFullPath)
{
    this->chrome->captureFullScreenshot(this->stringUtils.BSTRToString(format), quality, this->stringUtils.BSTRToString(imgFullPath));
    return S_OK;
}

STDMETHODIMP CChromeOpsSoft::captureScreenshot(BSTR format, int quality, int x, int y, int width, int height, float scale, BSTR imgFullPath)
{
    this->chrome->captureScreenshot(this->stringUtils.BSTRToString(format), quality, x, y, width, height, scale, this->stringUtils.BSTRToString(imgFullPath));
    return S_OK;
}

STDMETHODIMP CChromeOpsSoft::inputText(BSTR selector, BSTR txt)
{
    this->chrome->inputText(this->stringUtils.BSTRToString(selector), this->stringUtils.BSTRToString(txt));
    return S_OK;
}

STDMETHODIMP CChromeOpsSoft::getCookies(BSTR urls, BSTR* retVal)
{
    string jsonArray = this->stringUtils.BSTRToString(urls);
    nlohmann::json obj = nlohmann::json::parse(jsonArray);
    string ret = this->chrome->getCookies(obj);
    *retVal = this->stringUtils.stringToBSTR(ret);
    return S_OK;
}

STDMETHODIMP CChromeOpsSoft::setCookie(BSTR name, BSTR value, BSTR url, BSTR domain, BSTR path, int secure, int httpOnly, BSTR sameSite, int expires)
{
    string sName = this->stringUtils.BSTRToString(name);
    string sValue = this->stringUtils.BSTRToString(value);
    string sUrl = this->stringUtils.BSTRToString(url);
    string sDomain = this->stringUtils.BSTRToString(domain);
    string sPath = this->stringUtils.BSTRToString(path);
    string sSameSite = this->stringUtils.BSTRToString(sameSite);
    this->chrome->setCookie(sName, sValue, sUrl, sDomain, sPath, secure, httpOnly, sSameSite, expires);
    return S_OK;
}

STDMETHODIMP CChromeOpsSoft::setCookies(BSTR jsonCookies)
{
    this->chrome->setCookies(this->stringUtils.BSTRToString(jsonCookies));
    return S_OK;
}

STDMETHODIMP CChromeOpsSoft::clearBrowserCache()
{
    this->chrome->clearBrowserCache();
    return S_OK;
}

STDMETHODIMP CChromeOpsSoft::clearBrowserCookies()
{
    this->chrome->clearBrowserCookies();
    return S_OK;
}

STDMETHODIMP CChromeOpsSoft::setCacheDisabled(int cacheDisabled)
{
    this->chrome->setCacheDisabled(cacheDisabled);
    return S_OK;
}

STDMETHODIMP CChromeOpsSoft::parseJson(BSTR jsonBStr, BSTR* retVal)
{
    string uuidStr = this->jsonUtils.parseJson(this->stringUtils.BSTRToString(jsonBStr), &this->jsonCache);
    *retVal = this->stringUtils.stringToBSTR(uuidStr);
    return S_OK;
}

STDMETHODIMP CChromeOpsSoft::getJsonArraySize(BSTR uuidStr, int* retVal)
{
    string uuidKey = this->stringUtils.BSTRToString(uuidStr);
    if (this->jsonCache.count(uuidKey) > 0) {
        nlohmann::json cache = this->jsonCache[uuidKey];
        *retVal = cache.size();
    }
    else {
        *retVal = 0;
    }
    return S_OK;
}

STDMETHODIMP CChromeOpsSoft::getJsonValue(BSTR uuidStr, int idx, BSTR keyPath, BSTR* retVal)
{
    string uuidKey = this->stringUtils.BSTRToString(uuidStr);
    if (this->jsonCache.count(uuidKey) > 0) {
        nlohmann::json cache = this->jsonCache[uuidKey];
        if (cache.size() > 0) {
            nlohmann::json value;
            if (idx > -1) { //大于-1表示为数组
                value = this->jsonUtils.getValueFromJson(cache[idx], this->stringUtils.BSTRToString(keyPath));
            }
            else {
                value = this->jsonUtils.getValueFromJson(cache, this->stringUtils.BSTRToString(keyPath));
            }
            string ret = value.get<string>();
            *retVal = this->stringUtils.stringToBSTR(ret);
        }
    }
    else {
        *retVal = SysAllocString(L"");
    }
    return S_OK;
}


STDMETHODIMP CChromeOpsSoft::createTarget(BSTR url, BSTR* retVal)
{
    string ret = this->chrome->createTarget(this->stringUtils.BSTRToString(url));
    *retVal = this->stringUtils.stringToBSTR(ret);
    return S_OK;
}


STDMETHODIMP CChromeOpsSoft::closeTarget(BSTR targetId)
{
    this->chrome->closeTarget(this->stringUtils.BSTRToString(targetId));
    return S_OK;
}


STDMETHODIMP CChromeOpsSoft::getLastTargetId(BSTR* retVal)
{
    string ret = this->chrome->getLastTargetId();
    *retVal = this->stringUtils.stringToBSTR(ret);
    return S_OK;
}
