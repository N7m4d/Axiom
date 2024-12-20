#include "Game.h"
#include "google\protobuf\message_lite.h"

using namespace Axiom;

Game *poGame = nullptr;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow)
{
	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	int ValueReturn;

	poGame = new Game("Axiom", 1920, 1080);
	ValueReturn = poGame->wWinMain(hInstance, prevInstance, cmdLine, cmdShow);

	delete poGame;

	// clean shut down
	google::protobuf::ShutdownProtobufLibrary();

	return ValueReturn;
}
