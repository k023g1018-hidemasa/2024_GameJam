#pragma once
#include "Audio.h"
#include "AxisIndicator.h"
#include "DirectXCommon.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "WinApp.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "GameOverScene.h"

enum class Scene {
	titleScene,
	gameScene,
	gameOverScene,
	numOfScenes
};

class SceneManager
{
public:
	SceneManager(){}
	~SceneManager();
	void Initialize();
	void Run();
	void ChangeScene();
	void UpdateScene();
	void DrawScene();
private:
	Scene scene = Scene::titleScene;
	//蒲田エンジン
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	// 汎用機能
	Input* input = nullptr;
	Audio* audio = nullptr;
	AxisIndicator* axisIndicator = nullptr;
	PrimitiveDrawer* primitiveDrawer = nullptr;
	// ImGuiの初期化
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();

	//シーン
	GameScene* gameScene = nullptr;
	TitleScene* titleScene = nullptr;
	GameOverScene* gameOverScene = nullptr;
};

