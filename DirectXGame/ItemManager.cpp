#include "ItemManager.h"
#include "Reaf.h"
#include <random>
#include <iostream>

ItemManager::~ItemManager() {
	for (auto* reafs : reafs_) { // 左が自分でなんでも決めれる名前、右が左にコピーする対象したのを変更したら右が（本体）変わる
		delete reafs;
	}
	reafs_.clear();
	delete reafModel_;
}

void ItemManager::Initialize() {
	reafModel_ = Model::CreateFromOBJ("AL3_Enemy", true); ///////////////////////葉っぱのモデルを突っ込む
}

void ItemManager::Update() {
	//ゲームタイマーを回す
	gameTimer_++;

	if (gameTimer_ % 300 == 0) {
		kReafNumber += 1;
		ReafSpawn();
	}
	// 敵の更新処理
	for (auto* reafs : reafs_) { // 左が自分でなんでも決めれる名前、右が左にコピーする対象したのを変更したら右が（本体）変わる
		//生成がいるなら更新
		if (!reafs->isAlive_) { 
			reafs->SetPositionOutOfBounds();
		}
		reafs->Update(); 
		// ここを個別にしないと一個一個に動きを付けられない
		// 多分直結型がiを使ってこれはautoの指揮系があってそこから枝分かれ的に指示を渡してる
		// 枝分かれの制限を渡すか渡さないかを制御すればできそう

		//地面との当たり判定
		CheckIfGround();
	}
}

void ItemManager::Draw() {
	// 敵描画
	for (auto* reafs : reafs_) { // 左が自分でなんでも決めれる名前、右が左にコピーする対象したのを変更したら右が（本体）変わる
		//生成がいるなら描画
		if (reafs->isAlive_) { 
			reafs->Draw(); 
		}
	}
}

void ItemManager::ReafSpawn() {
	//新しい葉っぱを発生
	Reaf* newReaf = new Reaf();
	newReaf->isAlive_ = true;
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> dist(-20, 20);
	int randomNumber = dist(gen);
	//葉っぱの位置をセットする
	newReaf->SetSpawnPoint({float(randomNumber), newReaf->GetSpawnPoint().y + 10.0f, newReaf->GetSpawnPoint().z});
	//借りの変数に保留
	Vector3 reafPosition = newReaf->GetSpawnPoint();
	//
	newReaf->Initialize(reafModel_, viewProjection_, reafPosition);
	reafs_.push_back(newReaf);
}

void ItemManager::CheckIfGround() { 
	for (auto* reafs : reafs_) {
		if (reafs->GetPosition().y <= 0.0f) {
			reafs->isAlive_ = false;
			reafs->SetPositionOutOfBounds();
		}
	}
}
