// dllmain.h: 模块类的声明。

class CChromeOpsModule : public ATL::CAtlDllModuleT< CChromeOpsModule >
{
public :
	DECLARE_LIBID(LIBID_ChromeOpsLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_CHROMEOPS, "{51fb357f-0e50-40b7-bcbe-290e42e2af6c}")
};

extern class CChromeOpsModule _AtlModule;
