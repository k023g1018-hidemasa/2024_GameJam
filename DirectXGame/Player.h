#pragma once
#include "Input.h"
#include "Model.h"
#include "Vector3.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <cassert>
#include <imgui.h>
#include <numbers>

class Reaf;


enum class LRDirection {
	kRight,
	kLeft,
};
// 角
enum Corner {
	kRightBottom, // 右下
	kLeftBottom,  // 左下
	kRightTop,    // 右上
	kLeftTop,     // 左上

	kNumCorner // enumの要素数ここを見ると何個あるかわかる
};


class Player {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();
	void Initialize(Model* model, ViewProjection* viewProjection);
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
	/// <summary>
	/// velocityを取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetVelocity() { return velocity_; }
	/// <summary>
	/// worldTransformを取得
	/// </summary>
	/// <returns></returns>
	const WorldTransform& GetWorldTransform() { return worldTransform_; }

	Vector3 GetWorldPosition();
	AABB GetAABB();
	void OnCollision(const Reaf* reaf);
	bool IsGeated() const { return isGeat_; }
	bool oneRoop_ = false;//一回だけ当たり判定を通ったら通過できるように

private:
	WorldTransform worldTransform_;
	/// <summary>
	/// モデル//一旦預かるだけ
	/// </summary>
	Model* modelPlayer_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	/// <summary>
	/// テクスチャハンドル
	/// </summary>
	uint32_t textureHandle_ = 0u;

	

	static inline const float kAcceleration = 0.2f;
	static inline const float kAttenuation = 0.5f;
	static inline const float kLimitRunSpeed = 1.0f;
	// 重力加速度（下方向）
	static inline const float kGravityAccleration = 0.8f;
	// 最大落下速度（下方向）
	static inline const float kLimitFallSpeed = 1.2f;
	// ジャンプ初速（上方向）
	static inline const float kJumpAccleration = 1.2f;

	Vector3 velocity_ = {};
	LRDirection lrDirection_ = LRDirection::kRight;
	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;
	// 旋回タイマー
	float turnTimer_ = 0.0f;
	// 旋回時間<秒>
	static inline const float kTimeTurn = 0.3f;
	// 接地状態フラグ
	bool onGround_ = true;

	static inline const float kWidth = 1.8f;
	static inline const float kHeight = 1.8f;

	Vector3 CornerPostion(const Vector3& center, Corner corner);
	static inline const float kBlank = 0.2f; // めり込まない数値？
	//スコアの更新、エフェクトの発生
	bool isGeat_ = false;




};
