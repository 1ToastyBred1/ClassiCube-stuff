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
#include "src/TexturePack.h"
#include "src/Commands.h"

// gcc texture.c -o texture.dll -s -shared -L . -lClassiCube

static void Texture_Execute(const cc_string* args, int argsCount) {
	if (!argsCount) return;
	
	TexturePack_Extract(args);
}

static struct ChatCommand TextureCommand = {
	"Texture", Texture_Execute,
	COMMAND_FLAG_UNSPLIT_ARGS,
	{
		"&a/Texture [url]",
		"&aChanges texture using specified url."
	}
};

static void TexturePlugin_Init(void) {
	Commands_Register(&TextureCommand);
}

EXPORT int Plugin_ApiVersion = 1;
EXPORT struct IGameComponent Plugin_Component = { TexturePlugin_Init };