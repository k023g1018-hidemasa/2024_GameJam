#pragma once
#include "Model.h"
#include "Vector3.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include"Reaf.h"

class ScorePoint {
public:
	void Initialize(Model* scorePointModel, ViewProjection* viewProjection, const Vector3& position);
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
	void ZeroInitialize(Model* modelZero, ViewProjection* viewProjection, const Vector3& position);

	
private:
	Model* scorePointModel_;
	uint32_t textureHandle_ = 0u;
	ViewProjection* viewProjection_ = nullptr;
	
	// スコアの個数
	static inline const uint32_t kNumScores = 4;

	std::array<WorldTransform, kNumScores> worldTransforms_; //	ワールドトランスフォームをknum分作る

	float counter_ = 0.0f;
	// 色変化オブジェクト
	ObjectColor objectColor_;
	// 色の数値
	Vector4 color_;
//	int scorePoint_= 0;

	Model* zeloModel_;
	uint32_t countTextureHandle;
	//ゲットしたときのポイントを足し算するため
	Reaf* getPoint;
	








};