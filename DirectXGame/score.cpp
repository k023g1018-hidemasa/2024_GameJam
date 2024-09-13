#include "score.h"
#include <algorithm>
#include <iostream>

void Score::Initialize(Model* scoreParticlesModel, ViewProjection* viewProjection, const Vector3& position) {
	scoreParticlesModel_ = scoreParticlesModel;
	// 行列を定数バッファに転送//定数バッファ＝グラボ
	viewProjection_ = viewProjection;
	objectColor_.Initialize();
	color_ = {1, 1, 1, 1};

	for (auto& worldTransform : worldTransforms_) {
		worldTransform.Initialize(); // whay
		worldTransform.translation_ = position;
	}



}

void Score::Update() {
	if (isGeated_) {
		return;
	}

	for (uint32_t i = 0; i < kNumParticles; ++i) {
		// 基本となる速度ベクトル
		Vector3 velocity = {kSpeed, 0, 0};
		// 回転角の計算
		float angle = kAngleUnit * i;
		// Z軸回り回転行列
		Matrix4x4 matrixRotation = MakeRotateZMatrix(angle);
		// 基本ベクトルを回転させて速度ベクトルを得る
		velocity = Transform(velocity, matrixRotation);
		// 移動処理
		worldTransforms_[i].translation_ += velocity;
	}
	// カウンターを１フレーム分の秒数進める
	counter_ += 1.0f / 60.0f;
	// 存続時間の上限に達したら
	if (counter_ >= kDuration) {
		counter_ = kDuration;
		// 終了扱いにする
		isGeated_ = true;
	}
	color_.w = std::clamp(color_.w, 0.0f, 1.0f); // 都度変更
	color_.w += 0.01f;
	// 色変更オブジェに色の数値おwせってり
	objectColor_.SetColor(color_);
	// 色変更オブジェクトをVramに転送
	objectColor_.TransferMatrix();

	// ワールド返還の更新12ｐ
	for (auto& worldTransform : worldTransforms_) {
		worldTransform.UpdateMatrix();
	}


}

void Score::Draw() {
	if (isGeated_) {
		return;
	}
	for (auto& worldTransform : worldTransforms_) {
		scoreParticlesModel_->Draw(worldTransform, *viewProjection_, &objectColor_);
	}


}