#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"

class Player;
class Model;

class Ringo 
{
public:
	Ringo() {}
	~Ringo() {}
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model"></param>
	/// <param name="viewProjection"></param>
	/// <param name="position"></param>
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	//////////////////   ゲッターとセッター  ////////////////////////
	//matWorldの
	Vector3 GetWorldPosition();
	//worldTransform.translationの
	Vector3 GetPosition() { return worldTransform_.translation_; }
	void SetPosition(Vector3 position) { worldTransform_.translation_ = position; }
	//加速の
	Vector3 GetVelocity() { return velocity_; }
	void SetVelocity(Vector3 velocity) { velocity_ = velocity; }
	//発生位置の
	Vector3 GetSpawnPoint() { return spawnPoint_; }
	void SetSpawnPoint(Vector3 spawnPoint) { spawnPoint_ = spawnPoint; }
	//生成フラグ
	bool GetIsAlive() { return isAlive_; }
	void SetIsAlive(bool isAlive) { isAlive_ = isAlive; }
	/// <summary>
	///	当たり判定を移動
	/// </summary>
	void SetPositionOutOfBounds();
	//当たり判定の
	AABB GetAABB();
	void OnCollision(const Player* player);

private:
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	WorldTransform worldTransform_{};

	Vector3 position_{};
	Vector3 velocity_{};

	static inline const float kGravityAcceleration = 0.008f;
	static inline const float kLimitFallSpeed = 0.08f;
	static inline const float kWidth = 2.0f;
	static inline const float kHeight = 2.0f;

	Vector3 spawnPoint_{};
	bool isAlive_ = false;
};
