#include "GameOverScene.h"
#include "Input.h"
#include "Model.h"
#include "TextureManager.h"
#include "DirectXCommon.h"
#include "Sprite.h"
#include "Audio.h"
#include "Input.h"
#include "Skydome.h"

void GameOverScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	model_ = Model::CreateFromOBJ("gameOverText", true);
	viewProjection_.Initialize();
	worldTransform_.Initialize();
	worldTransform_.scale_.x = 5.0f;
	worldTransform_.scale_.y = 5.0f;
	worldTransform_.scale_.z = 5.0f;

	worldTransform_.rotation_.z = 0.0f;
	worldTransform_.rotation_.x = 0.0f;
	worldTransform_.translation_.y = 2.0f;

	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	skydome = new Skydome;
	skydome->Initialize(modelSkydome_, &viewProjection_);


}

void GameOverScene::Update() {
	worldTransform_.UpdateMatrix();
	Rotate();
	skydome->Update();
	if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
		finished_ = true;
	}
}

void GameOverScene::Draw() {
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

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる

	model_->Draw(worldTransform_, viewProjection_);
	skydome->Draw();

	/// </summary>

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

void GameOverScene::Rotate() {
	if (rotateForward_) {
		worldTransform_.rotation_.z += deltaTime_;
		if (worldTransform_.rotation_.z >= maxRotationZ) {
			rotateForward_ = false;
		}
	} else {
		worldTransform_.rotation_.z -= deltaTime_;
		if (worldTransform_.rotation_.z <= -maxRotationZ) {
			rotateForward_ = true;
		}
	}

	// Xジグで回転
	if (rotateSide_) {
		worldTransform_.rotation_.x += deltaTime_;
		if (worldTransform_.rotation_.x >= maxRotationX) {
			rotateSide_ = false;
		}
	} else {
		worldTransform_.rotation_.x -= deltaTime_;
		if (worldTransform_.rotation_.x <= -maxRotationX) {
			rotateSide_ = true;
		}
	}
}
