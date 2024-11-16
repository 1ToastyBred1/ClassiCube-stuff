#ifdef _WIN32
    #define CC_API __declspec(dllimport)
    #define CC_VAR __declspec(dllimport)
    #define EXPORT __declspec(dllexport)
#else
    #define CC_API
    #define CC_VAR
    #define EXPORT __attribute__((visibility("default")))
#endif

#include "src/Chat.h"
#include "src/Game.h"
#include "src/String.h"
#include "src/Server.h"
#include "src/Commands.h"

// gcc change_client_name.c -o ChangeAppname.dll -s -shared -L . -lClassiCube

static void ChangeAppnameCommand_Execute(const cc_string* args, int argsCount) {
	cc_uint8 buffer[67];
	buffer[0] = 0x10;
	String_CopyToRaw(buffer + 1, 64, args);
	for (int i = args->length + 1; i < 65; i++) { buffer[i] = ' '; }
	buffer[65] = 0; buffer[66] = 0;
	
	Server.SendData(buffer, 67);
}

static struct ChatCommand ChangeAppnameCommand = {
	"ChangeAppname", ChangeAppnameCommand_Execute,
	COMMAND_FLAG_UNSPLIT_ARGS,
	{
		"&a/ChangeAppname [new app name]",
		"&aChanges your client name to the desired one.",
	}
};

static void ChangeAppnamePlugin_Init(void) {
	Commands_Register(&ChangeAppnameCommand);
}

EXPORT int Plugin_ApiVersion = 1;
EXPORT struct IGameComponent Plugin_Component = { ChangeAppnamePlugin_Init };
