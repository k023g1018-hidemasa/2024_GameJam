#include "SceneManager.h"
#include "GameScene.h"

SceneManager::~SceneManager() {
	// 各種解放
	delete gameScene;
	delete titleScene;
}

void SceneManager::Initialize() {
	// ゲームウィンドウの作成
	win = WinApp::GetInstance();
	win->CreateGameWindow(L"#6021_コーテス_ナカノ_ヒラジマ");

	// DirectX初期化処理
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize(win);

#pragma region 汎用機能初期化
	imguiManager->Initialize(win, dxCommon);

	// 入力の初期化
	input = Input::GetInstance();
	input->Initialize();

	// オーディオの初期化
	audio = Audio::GetInstance();
	audio->Initialize();

	// テクスチャマネージャの初期化
	TextureManager::GetInstance()->Initialize(dxCommon->GetDevice());
	TextureManager::Load("white1x1.png");

	// スプライト静的初期化
	Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::kWindowWidth, WinApp::kWindowHeight);

	// 3Dモデル静的初期化
	Model::StaticInitialize();

	// 軸方向表示初期化
	axisIndicator = AxisIndicator::GetInstance();
	axisIndicator->Initialize();

	primitiveDrawer = PrimitiveDrawer::GetInstance();
	primitiveDrawer->Initialize();
#pragma endregion

	//シーンの初期化
	titleScene = new TitleScene();
	titleScene->Initialize();
}

void SceneManager::Run() {
	while (true) {
		// メッセージ処理
		if (win->ProcessMessage()) {
			break;
		}
		// ImGui受付開始
		imguiManager->Begin();
		// 入力関連の毎フレーム処理
		input->Update();
		// シーン切り替え
		ChangeScene();
		// 毎フレームの処理
		UpdateScene();
		// 軸表示の更新
		axisIndicator->Update();
		// ImGui受付終了
		imguiManager->End();
		// 描画開始
		dxCommon->PreDraw();
		// ゲームシーンの描画
		DrawScene();
		// 軸表示の描画
		axisIndicator->Draw();
		// プリミティブ描画のリセット
		primitiveDrawer->Reset();
		// ImGui描画
		imguiManager->Draw();
		// 描画終了
		dxCommon->PostDraw();
	}
	// 3Dモデル解放
	Model::StaticFinalize();
	audio->Finalize();
	// ImGui解放
	imguiManager->Finalize();
	// ゲームウィンドウの破棄
	win->TerminateGameWindow();
}

void SceneManager::ChangeScene() { 
	switch (scene) { 
	case Scene::titleScene:
		if (titleScene->IsFinished()) {
			scene = Scene::gameScene;
			delete titleScene;
			titleScene = nullptr;
			gameScene = new GameScene();
			gameScene->Initialize();
		}
	break;
	case Scene::gameScene:
		if (gameScene->IsFinished()) {
			scene = Scene::gameOverScene;
			delete gameScene;
			gameScene = nullptr;
			gameOverScene = new GameOverScene();
			gameOverScene->Initialize();
		}
	break;
	case Scene::gameOverScene:
		if (gameOverScene->IsFinished()) {
			scene = Scene::titleScene;
			delete gameOverScene;
			gameOverScene = nullptr;
			titleScene = new TitleScene();
			titleScene->Initialize();
		}
	break;
	}
}

void SceneManager::UpdateScene() {
	switch (scene) {
	case Scene::titleScene:
	titleScene->Update();
	break;
	case Scene::gameScene:
	gameScene->Update();
	break;
	case Scene::gameOverScene:
	gameOverScene->Update();
	break;
	}
}

void SceneManager::DrawScene() {
	switch (scene) {
	case Scene::titleScene:
	titleScene->Draw();
	break;
	case Scene::gameScene:
	gameScene->Draw();
	break;
	case Scene::gameOverScene:
	gameOverScene->Draw();
	break;
	}
}
