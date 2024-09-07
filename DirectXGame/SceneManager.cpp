#include "SceneManager.h"
#include "GameScene.h"

void SceneManager::Initialize(){
	sceneArr_[static_cast<int>(Scene::gameScene)] = std::make_unique<GameScene>();
}

void SceneManager::Update(){
	switch (scene) {
	case Scene::titleScene:
		break;
	case Scene::gameScene:
		sceneArr_[static_cast<int>(Scene::gameScene)]->Update();
		break;
	case Scene::gameOverScene:
		break;
	case Scene::gameClearScene:
		break;
	}
}

void SceneManager::Draw(){
	switch (scene) {
	case Scene::titleScene:
		break;
	case Scene::gameScene:
		sceneArr_[static_cast<int>(Scene::gameScene)]->Draw();
		break;
	case Scene::gameOverScene:
		break;
	case Scene::gameClearScene:
		break;
	}
}
