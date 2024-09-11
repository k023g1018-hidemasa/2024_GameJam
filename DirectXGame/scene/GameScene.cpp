#include "GameScene.h"
<<<<<<< Updated upstream
#include "TextureManager.h"
#include <cassert>

// #include"ViewProjection.h"
=======
#include "CameraController.h"
#include "Ground.h"
#include "Model.h"
#include "Skydome.h"
#include "TextureManager.h"
#include "ViewProjection.h"
#include "player.h"
#include <cassert>
>>>>>>> Stashed changes

GameScene::GameScene() {}

GameScene::~GameScene() {

	delete blockModel_;
	delete skydome_;

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
		worldTransformBlocks_.clear();
	}
<<<<<<< Updated upstream
	delete debugCamera_;
	// 破壊と創造はセットで
	delete modelSkydome_;

	delete mapChipField_;

	delete model_;
	delete player_;
=======
	reafs_.clear();
	delete cameraController_;
	delete scoreParticlesModel_;
>>>>>>> Stashed changes
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	blockModel_ = Model::Create();
	blockTextureHandle_ = TextureManager::Load("cube/cube.jpg");

	viewProjection_.Initialize();
<<<<<<< Updated upstream
=======
	worldTransform_.Initialize();
>>>>>>> Stashed changes

	debugCamera_ = new DebugCamera(1280, 720);

	// 天球を内部的に作る
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	skydome_ = new Skydome;
	skydome_->Initialize(modelSkydome_, &viewProjection_);
<<<<<<< Updated upstream

	mapChipField_ = new MapChipField;
	mapChipField_->LoadMapChipCsv("Resources/blocks.csv");
	// ｃｓｖを通った後にジェネレイトをする
	GenerateBlocks();

	texturHandle_ = TextureManager::Load("sample.png"); // キャラ画像淹れる
	model_ = Model::Create();
	worldTransform_.Initialize();

	// 座標をマップっチップ 番号で指定
	Vector3 playrePosition = mapChipField_->GetMaoChipPositionByIndex(1, 18);
	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	player_->Initialize(model_, &viewProjection_, playrePosition);
=======
	// 地面
	ground_ = new Ground();
	modelGround_ = Model::CreateFromOBJ("Ground", true);
	ground_->Initialize(modelGround_, &viewProjection_);
	// プレイヤー
	modelPlayer_ = Model::Create();
	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	player_->Initialize(modelPlayer_, &viewProjection_);

	reafModel_ = Model::CreateFromOBJ("AL3_Enemy", true); ///////////////////////葉っぱのモデルを突っ込む
	for (int32_t i = 0; i < kReafNumber; ++i) {
		Reaf* newReaf = new Reaf();
		Vector3 reafPosition = {3.0f, 10.0f + (i * 2.0f), 0.0f};
		newReaf->Initialize(reafModel_, &viewProjection_, reafPosition);

		reafs_.push_back(newReaf);
	}
	// カメラ初期化
	cameraController_ = new CameraController();
	cameraController_->Initialize(&viewProjection_);
	cameraController_->SetTarget(player_);
	cameraController_->SetMovableArea({-20.0f, 20.0f, 10.0f, 60.0f});
	cameraController_->Reset();
	// 音声初期化
	BGM_ = audio_->LoadWave("relax.mp3");
	audio_->PlayWave(BGM_);
>>>>>>> Stashed changes
}

void GameScene::Update() {

	// ブロックの更新
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock) {
				continue;
			}
			worldTransformBlock->matWorld_ = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);
			// 定数バッファに転送
			worldTransformBlock->TransferMatrix();
		}
	}
#ifdef _DEBUG

	if (input_->TriggerKey(DIK_0)) {
		isDebugCameraActive_ ^= true;
	}

	if (isDebugCameraActive_) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		viewProjection_.TransferMatrix();
	} else {
		viewProjection_.UpdateMatrix();
	}

#endif // _DEBUG

	skydome_->Update();

	// 自キャラの更sin
	player_->Update();
<<<<<<< Updated upstream
=======
	// 敵の更新処理
	for (auto* reafs : reafs_) { // 左が自分でなんでも決めれる名前、右が左にコピーする対象したのを変更したら右が（本体）変わる
		reafs->Update();
		// ここを個別にしないと一個一個に動きを付けられない
		// 多分直結型がiを使ってこれはautoの指揮系があってそこから枝分かれ的に指示を渡してる
		// 枝分かれの制限を渡すか渡さないかを制御すればできそう
	}
	cameraController_->Update();
	CheckAllCollision();
	// 葉っぱのゲット判定
	if (player_->IsGeated()) {
		// 自キャラの座標を取得
		const Vector3& scoreParticlesPosition = player_->GetWorldPosition();

		// 自キャラの座標にですパ初期化ｐ13
		if (player_->oneRoop_ == true) {
			scoreParticles_ = new Score;
			scoreParticlesModel_ = Model::CreateFromOBJ("AL3_Enemy", true);                              // ここにスコアの演出用のモデル
			scoreParticles_->Initialize(scoreParticlesModel_, &viewProjection_, scoreParticlesPosition); // プレイヤーの位置があってるのかｐ161
		}
		player_->oneRoop_ = false;

		// 死亡演出切り替え
		// phase_ = Phase::kDeath;
		// この辺をスコアの降雨真とかを入れる感じ？多分アップデートでいいからここではない
		scoreParticles_->Update();//こいつは外に出しちゃいけねえ

	}
>>>>>>> Stashed changes
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	skydome_->Draw();
	// modelSkydome_->Draw(worldTransform_, viewProjection_);

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock) {
				continue;
			}
			blockModel_->Draw(*worldTransformBlock, viewProjection_, blockTextureHandle_);
		}
	}
<<<<<<< Updated upstream
	// 自キャラの描画
	player_->Draw();

=======
	if (player_->IsGeated() == true) {
		scoreParticles_->Draw();
	}
>>>>>>> Stashed changes
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::GenerateBlocks() {

<<<<<<< Updated upstream
	// 要素数,ここ変えれば配置する数が変わる
	// 要素数
	// バーティ縦ホリゾン横
	uint32_t numBlockVirtical = mapChipField_->GetNumBlockVirtical();
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();

	// 要素数を変更
	// 列数を設定(縦方向のブロック数)
	worldTransformBlocks_.resize(numBlockVirtical);
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		// 1列の要素数を設定（横方向のブロック数）
		worldTransformBlocks_[i].resize(numBlockHorizontal);
	}
	// ブロックの生成
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		for (uint32_t j = 0; j < numBlockHorizontal; ++j) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMaoChipPositionByIndex(j, i);
			}
=======
		// AABB同士の考査判定
		if (IsCollision(aabb1, aabb2)) {
			// ぶつかった時どうするか
			// 自キャラの衝突時コールバックを呼び出す
			player_->OnCollision(reafs);
			//	player_->IsDead();
			// 敵との衝突時コールバック呼び出し
			reafs->OnCollision(player_);
>>>>>>> Stashed changes
		}
	}
	// 要素数を変更する、可変長は最初はゼロだからつ要素を作っている（ｎｗＵ）
	worldTransformBlocks_.resize(numBlockHorizontal);
}
