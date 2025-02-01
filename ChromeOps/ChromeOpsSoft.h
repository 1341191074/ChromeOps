// ChromeOpsSoft.h: CChromeOpsSoft 的声明
#pragma once
#include "resource.h"       // 主符号
#include "ChromeOps_i.h"
#include "utils/StringUtils.hpp"
#include "base/Chrome.hpp"
#include "utils/GlobalData.hpp"
#include "nlohmann/json.hpp"
#include "utils/JsonUtils.hpp"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif

using namespace ATL;

// CChromeOpsSoft
// 在类外定义并初始化静态成员变量result
std::map<int, nlohmann::json> GlobalData::result = std::map<int, nlohmann::json>();
class ATL_NO_VTABLE CChromeOpsSoft :
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CChromeOpsSoft, &CLSID_ChromeOpsSoft>,
    public IDispatchImpl<IChromeOpsSoft, &IID_IChromeOpsSoft, &LIBID_ChromeOpsLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
private:
    StringUtils stringUtils;
    JsonUtils jsonUtils;
    Chrome* chrome;

    std::map<string, nlohmann::json> jsonCache;
public:
    CChromeOpsSoft()
    {
        chrome = new Chrome();
    }

    ~CChromeOpsSoft()
    {
    }

    DECLARE_REGISTRY_RESOURCEID(106)

    BEGIN_COM_MAP(CChromeOpsSoft)
        COM_INTERFACE_ENTRY(IChromeOpsSoft)
        COM_INTERFACE_ENTRY(IDispatch)
    END_COM_MAP()

    DECLARE_PROTECT_FINAL_CONSTRUCT()

    HRESULT FinalConstruct()
    {
        return S_OK;
    }

    void FinalRelease() {
        delete this->chrome;
        this->jsonCache.clear();
    }

public:
    // 测试方法
    STDMETHOD(getVersion)(BSTR* ret);
    STDMETHOD(chromeBind)(BSTR host, int port, int* retVal);
    STDMETHOD(pushArgs)(BSTR arg);
    STDMETHOD(launch)(BSTR chromeFullPath, int tryBind, int* retVal);
    STDMETHOD(findTargetList)(BSTR* targetList);
    STDMETHOD(switchTab)(BSTR tabId, int* ret);
    STDMETHOD(getOuterHTML)(BSTR selector, BSTR* retVal);
    STDMETHOD(navigate)(BSTR url, BSTR referrer);
    STDMETHOD(isLoadingFinished)(int* retVal);
    STDMETHOD(runScript)(BSTR expression, BSTR* retVal);
    STDMETHOD(captureScreenshot)(BSTR format, int quality, int x, int y, int width, int height, float scale, BSTR imgFullPath);
    STDMETHOD(inputText)(BSTR selector, BSTR txt);
    STDMETHOD(getCookies)(BSTR urls, BSTR* retVal);
    STDMETHOD(setCookie)(BSTR name, BSTR value, BSTR url, BSTR domain, BSTR path, int secure, int httpOnly, BSTR sameSite, int expires);
    STDMETHOD(setCookies)(BSTR jsonCookies);
    STDMETHOD(clearBrowserCache)();
    STDMETHOD(clearBrowserCookies)();
    STDMETHOD(setCacheDisabled)(int cacheDisabled);
    STDMETHOD(captureFullScreenshot)(BSTR format, int quality, BSTR imgFullPath);
    STDMETHOD(parseJson)(BSTR jsonBStr, BSTR* retVal);
    STDMETHOD(getJsonValue)(BSTR uuidStr, int idx, BSTR keyPath, BSTR* retVal);
    STDMETHOD(getJsonArraySize)(BSTR uuidStr, int* retVal);
    STDMETHOD(createTarget)(BSTR url, BSTR* retVal);
    STDMETHOD(closeTarget)(BSTR targetId);
    STDMETHOD(getLastTargetId)(BSTR* retVal);
};

OBJECT_ENTRY_AUTO(__uuidof(ChromeOpsSoft), CChromeOpsSoft)
