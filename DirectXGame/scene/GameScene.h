#pragma once
#include "Input.h"
#include "Sprite.h"
#include "Audio.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include <vector>
#include"Reaf.h"
#include "WorldTransform.h"
#include"score.h"

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
	void CheckAllCollision();
	void Draw();
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
	//リーフのテクスチャハンドルとか
	Model* reafModel_ = nullptr;
	std::list<Reaf*> reafs_;
	static inline const int32_t kReafNumber = 1;
	//カメラコントローラ
	CameraController* cameraController_ = nullptr;
	//音声用
	uint32_t BGM_ = 0;

	//ゲットの判定
	Score* scoreParticles_ = nullptr;
	Model* scoreParticlesModel_ = nullptr;

};
