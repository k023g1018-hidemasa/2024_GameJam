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
class MapChipField;
class Player;
class Skydome;
class Ground;

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

	Model* blockModel_ = nullptr;
	uint32_t blockTextureHandle_ = 0u;
	// 要素数が分からないから(可変できる配列)、多分ふぉｒで回してブロックの数文っていうやり方？
	// ：の後ろを参照して消す：の前が一個ずつずらしてくれる、とりあえず全部に命令できる
	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;

	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	bool isDebugCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;

	// これの名前で呼び出せばｈにあるやつは使えるからわかりやすく？
	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;
	
	//地面用
	Ground* ground_ = nullptr;
	Model* modelGround_ = nullptr;

	MapChipField* mapChipField_;
	// キャラクターのテクスチャ
	uint32_t texturHandle_ = 0;

	Model* model_ = nullptr;
	Player* player_ = nullptr;
};
