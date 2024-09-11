#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"

class Model;
class Audio;
class DirectXCommon;
class Skydome;

class TitleScene {
public:
	TitleScene();
	~TitleScene();
	/// <summary>
	/// 
	/// </summary>
	void Initialize();
	/// <summary>
	/// 
	/// </summary>
	void Update();
	/// <summary>
	/// 
	/// </summary>
	void Draw();
	/// <summary>
	/// 
	/// </summary>
	void Rotate();
	// デスフラグのgetter
	bool IsGeated() const { return finished_; }

private:
	DirectXCommon* dxCommon_ = nullptr;

	const float pi = 3.14159265359f;
	const float maxRotationZ = 15.0f * (pi / 180.0f); //45度　radian式
	const float maxRotationX = 10.0f * (pi / 180.0f);

	// 終了フラグ
	bool finished_ = false;
	Model* model_ = nullptr;
	ViewProjection viewProjection_;
	WorldTransform worldTransform_;

	bool rotateForward_ = true;
	bool rotateSide_ = true;
	float deltaTime_ = 0.002f;

	Model* modelSkydome_ = nullptr;
	Skydome* skydome = nullptr;
};