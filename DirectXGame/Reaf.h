#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "numbers"
#include <cmath>
#include <limits>
#include <iostream>

class Player;
class MapChipField;

class Reaf {
public:
	Reaf();
	~Reaf();

	void Initialize(Model* enemyModel, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	void Draw();

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; };
	//matWorld_.mの情報
	Vector3 GetWorldPosition();
	void SetPositionOutOfBounds();
	//worldTransform_の情報
	Vector3 GetPosition() { return worldTransform_.translation_; }
	
	AABB GetAABB();
	void OnCollision(const Player* player);

	//void OnCollision(const Player* player);
	//葉っぱの疑似振り子
	float easeInOutCubic(float x) { return x < 0.5f ? 4.0f* x * x * x : 1 - std::pow(-2.0f * x + 2.0f, 3.0f) / 2.0f; };
	bool switchPendulum = false;

	Vector3 GetSpawnPoint() { return spawnPoint; }
	void SetSpawnPoint(Vector3 koko) { spawnPoint = koko; }

	// 生成フラグ
	bool isAlive_ = false;
private:
	Model* enemyModel_ = nullptr;
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_ = nullptr;
	
	uint32_t textureHandle_ = 0u;
	// マップチップでフィールドを作った
	MapChipField* mapChipField_ = nullptr;
	static inline const float kWalkSpeed = 0.01f;
	Vector3 verocity_ = {};
	// 最初の角度（上向き）
	static inline const float kWalkMotionAngleStart = 30;
	// 最後の角度（下向き）
	static inline const float kWalkMotionAngleEnd = -30;
	// アニメーションの周期となる時間
	static inline const float kWalkMotionTime = 1.0f;
	// 経過時間
	float wolkTimer_ = 0.0f;
	// とぇきの半径
	static inline const float kWidth = 1.8f;
	static inline const float kHeight = 1.8f;
	//リーフの振り子の動き
	//  ラープの移動するスピード？
	static inline const float kInterpolationRate = 0.2f;
	//スポーンした場所から揺れたい終点の距離
	Vector3 targetOffset_ = {15, -5, 0};
	//ラープの終点
	Vector3 targetCoordinates{};
	//スポーンした場所（そこを中心に揺れる）
	Vector3 spawnPoint{};
	//スポーンのタイマー
	int spawnTimer = 0;
};

