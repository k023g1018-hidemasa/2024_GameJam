#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "ViewProjection.h"
#include "player.h"
#include "Model.h"
#include "Skydome.h"
#include "Ground.h"
#include "CameraController.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete debugCamera_;
	delete modelSkydome_;
	delete skydome_;
	delete modelGround_;
	delete ground_;
	delete modelPlayer_;
	delete player_;
	delete cameraController_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	viewProjection_.Initialize();
	worldTransform_.Initialize();
	
	debugCamera_ = new DebugCamera(1280, 720);
	// 天球を内部的に作る
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	skydome_ = new Skydome;
	skydome_->Initialize(modelSkydome_, &viewProjection_);
	//地面
	ground_ = new Ground();
	modelGround_ = Model::CreateFromOBJ("Ground", true);
	ground_->Initialize(modelGround_, &viewProjection_);
	//プレイヤー
	modelPlayer_ = Model::Create();
	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	player_->Initialize(modelPlayer_, &viewProjection_);
	//カメラ初期化
	cameraController_ = new CameraController();
	cameraController_->Initialize(&viewProjection_);
	cameraController_->SetTarget(player_);
	cameraController_->SetMovableArea({ -20.0f, 20.0f, 10.0f,60.0f });
	cameraController_->Reset();
}

void GameScene::Update() {
//#ifdef _DEBUG
//	if (input_->TriggerKey(DIK_0)) {
//		isDebugCameraActive_ ^= true;
//	}
//
//	if (isDebugCameraActive_) {
//		debugCamera_->Update();
//		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
//		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
//
//		viewProjection_.TransferMatrix();
//	} else {
//		viewProjection_.UpdateMatrix();
//	}
//#endif // _DEBUG

	skydome_->Update();
	ground_->Update();
	player_->Update();
	cameraController_->Update();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	skydome_->Draw();
	ground_->Draw();
	player_->Draw();

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
