#pragma once
#include <memory>
#include"SceneBase.h"

enum class Scene {
	titleScene,
	gameScene,
	gameOverScene,
	gameClearScene,
	numOfScenes
};

//SceneManagerがSceneBaseを管理できる
class SceneManager
{
public:
	SceneManager(){}
	~SceneManager(){}
	void Initialize();
	void Update();
	void Draw();
private:
	std::unique_ptr<SceneBase> sceneArr_[4];

	Scene scene = Scene::gameScene;
};

