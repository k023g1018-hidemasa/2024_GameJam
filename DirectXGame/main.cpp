#include "SceneManager.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) { 
	SceneManager* gameLoop = new SceneManager();
	gameLoop->Initialize();

	gameLoop->Run();

	delete gameLoop;
}