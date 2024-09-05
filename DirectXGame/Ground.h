#pragma once
#include"WorldTransform.h"

class Model;
class ViewProjection;

class Ground
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model"></param>
	/// <param name="viewProjection"></param>
	void Initialize(Model* model, ViewProjection* viewProjection);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
private:
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_ = nullptr;
	Model* modelPlayer_ = nullptr;
};