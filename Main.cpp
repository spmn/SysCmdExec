#ifdef _WINDOWS
	#define popen _popen
	#define pclose  _pclose
#endif

#include <stdio.h>
#include <string>

#include "sdk/amx/amx.h"
#include "sdk/plugincommon.h"

typedef void(*logprintf_t)(char* format, ...);

logprintf_t logprintf;
extern void *pAMXFunctions;

// native SysCmdExec(cmd[]);
cell AMX_NATIVE_CALL SysCmdExec(AMX* amx, cell* params)
{
	char *pszCommand; 
	amx_StrParam(amx, params[1], pszCommand);

	FILE *pPipe;
	char szBuffer[512];
	int iRetVal;
	std::string bigBuffer = "";

	logprintf("SysCmdExec: Executing command: \"%s\"", pszCommand);
	if ((pPipe = popen(pszCommand, "r")) != NULL)
	{
		while (fgets(szBuffer, sizeof(szBuffer), pPipe))
			bigBuffer.append(szBuffer);
		
		iRetVal = pclose(pPipe);

		logprintf("SysCmdExec: Command output:\n%s", bigBuffer.c_str());
		logprintf("SysCmdExec: Command return value: %d", iRetVal);
	}
	else
	{
		logprintf("SysCmdExec: Couldn't open pipe.");
	}
	return 1;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	logprintf("  SysCmdExec v1.0 - Author: Spmn - Loaded.");
	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	logprintf("  SysCmdExec v1.0 - Author: Spmn - Unloaded.");
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

AMX_NATIVE_INFO PluginNatives[] =
{
	{ "SysCmdExec", SysCmdExec },
	{ 0, 0 }
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	return amx_Register(amx, PluginNatives, -1);
}
