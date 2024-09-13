#pragma once
#include "Vector3f.h"
class ViewProjection;
class Player;

struct Rect {
	float left = 0.0f;
	float right = 1.0f;
	float bottom = 0.0f;
	float top = 1.0f;
};

/// <summary>
/// カメラコントローラ
/// </summary>
class CameraController
{
public:
	CameraController() = default;
	~CameraController() = default;
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="viewProjection"></param>
	void Initialize(ViewProjection* viewProjection);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	const ViewProjection& GetViewProjection() { return *viewProjection_; }
	/// <summary>
	/// カメラの位置をセット
	/// </summary>
	/// <param name="target"></param>
	void SetTarget(Player* target) { target_ = target; }
	/// <summary>
	/// カメラの制限をかける
	/// </summary>
	/// <param name="area"></param>
	void SetMovableArea(Rect area) { movableArea_ = area; }
	/// <summary>
	/// カメラをスルスルにプレイヤーを追いかけるようにする
	/// </summary>
	/// <param name="viewProjection">カメラの位置</param>
	/// <param name="targetDestination">カメラの目標位置</param>
	/// <param name="kInterpolationRate">だんだんプレイヤーからに離れる数字</param>
	//void Lerp(Vector3 &viewProjection, Vector3 &targetDestination);
	/// <summary>
	/// カメラの位置をプレイヤーの位置に戻す
	/// </summary>
	void Reset();
	//Vector3 GetPosition() { return viewProjection_->translation_; } 

private:
	ViewProjection* viewProjection_;
	Vector3 targetOffset_ = { 0.0f, 0.0f, -30.0f };
	Player* target_ = nullptr;
	Rect movableArea_{ 0, 100, 0, 100 };
	Vector3 targetDestination_ = {};

	float kInterpolationRate = 0.1f;
	static inline const float kVelocityBias = 0.8f;
};

