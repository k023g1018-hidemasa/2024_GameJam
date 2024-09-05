#pragma once

#include "Audio.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Sprite.h"
#include <vector>
#include "WorldTransform.h"

class Model;
class ViewProjection;
class Player;
class Skydome;
class Ground;
class CameraController;

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	void GenerateBlocks();
private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	//ゲームシーン
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	bool isDebugCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;
	// これの名前で呼び出せばｈにあるやつは使えるからわかりやすく？
	Model* modelSkydome_ = nullptr;
	Skydome* skydome_ = nullptr;
	//地面用
	Model* modelGround_ = nullptr;
	Ground* ground_ = nullptr;
	// キャラクターのテクスチャ
	Model* modelPlayer_ = nullptr;
	Player* player_ = nullptr;
	//カメラコントローラ
	CameraController* cameraController_ = nullptr;
};
