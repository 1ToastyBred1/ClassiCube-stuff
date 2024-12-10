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
#include "src/Commands.h"
#include "src/Protocol.h"
#include "src/Entity.h"
#include "src/Server.h"

// gcc change_motd.c -o ChangeMotd.dll -s -shared -L . -lClassiCube

Net_Handler Classic_Handshake;

static void ChangeMotdCommand_Execute(const cc_string* args, int argsCount) {
	if (Server.IsSinglePlayer) return;
	
	cc_uint8 buffer[130];
	
	String_CopyToRaw(buffer, 64, &Server.Name);
	String_CopyToRaw(buffer + 65, 64, args);
	
	for (int i = Server.Name.length; i < 64; i++) { buffer[i] = ' '; }
	for (int i = 65 + args->length; i < 129; i++) { buffer[i] = ' '; }
	
	cc_uint8 user_type = Entities.CurPlayer->Hacks.IsOp ? 0x64 : 0x00;
	buffer[129] = user_type;
	
	Classic_Handshake(buffer);
}

static struct ChatCommand ChangeMotdCommand = {
	"ChangeMotd", ChangeMotdCommand_Execute,
	COMMAND_FLAG_UNSPLIT_ARGS,
	{
		"&a/ChangeMotd [motd]",
		"&eChanges motd to the desired one."
	}
};

static void ChangeMotdPlugin_Init(void) {
	Commands_Register(&ChangeMotdCommand);
	Classic_Handshake = Protocol.Handlers[OPCODE_HANDSHAKE];
}

EXPORT int Plugin_ApiVersion = 1;
EXPORT struct IGameComponent Plugin_Component = { ChangeMotdPlugin_Init };