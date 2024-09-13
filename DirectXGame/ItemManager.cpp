#include "ItemManager.h"
#include "Reaf.h"
#include "Ringo.h"
#include <random>
#include <iostream>

ItemManager::~ItemManager() {
	for (auto* reafs : reafs_) { // 左が自分でなんでも決めれる名前、右が左にコピーする対象したのを変更したら右が（本体）変わる
		delete reafs;
	}
	reafs_.clear();
	delete reafModel_;
	for (auto* ringos : ringos_) {
			delete ringos;
	}

	ringos_.clear();
	delete ringoModel_;
}

void ItemManager::Initialize(ViewProjection* viewProjection) {
	reafModel_ = Model::CreateFromOBJ("happa", true); ///////////////////////葉っぱのモデルを突っ込む
	ringoModel_ = Model::CreateFromOBJ("ringo", true);
	viewProjection_ = viewProjection;
}

void ItemManager::Update() {
	//ゲームタイマーを回す
	gameTimer_++;
	if (gameTimer_ % 500 == 0) {
		kReafNumber += 1;
		ReafSpawn();
	}
	if (gameTimer_ % 60 == 0) {
		kRingoNumber += 1;
		RingoSpawn();
	}
	//葉っぱの更新処理
	for (auto* reafs : reafs_) { // 左が自分でなんでも決めれる名前、右が左にコピーする対象したのを変更したら右が（本体）変わる
		//生成がいるなら更新
		if (!reafs->GetIsAlive()) { 
			reafs->SetPositionOutOfBounds(); //消えた葉っぱの当たり判定をプレイ内所に残らないように
		}
		reafs->Update(); 
		// ここを個別にしないと一個一個に動きを付けられない
		// 多分直結型がiを使ってこれはautoの指揮系があってそこから枝分かれ的に指示を渡してる
		// 枝分かれの制限を渡すか渡さないかを制御すればできそう
	}
	//リンゴの更新処理
	for (auto* ringos : ringos_) {
		if (!ringos->GetIsAlive()) {
			ringos->SetPositionOutOfBounds();
		}
		ringos->Update();
	}

	// 地面との当たり判定
	CheckIfGround();
}

void ItemManager::Draw() {
	// 葉っぱ描画
	for (auto* reafs : reafs_) { // 左が自分でなんでも決めれる名前、右が左にコピーする対象したのを変更したら右が（本体）変わる
		//生成がいるなら描画
		if (reafs->GetIsAlive()) { 
			reafs->Draw(); 
		}
	}
	//リンゴ描画
	for (auto* ringos : ringos_) {
		if (ringos->GetIsAlive()) {
			ringos->Draw();
		}
	}
}

void ItemManager::ReafSpawn() {
	//新しい葉っぱを発生
	Reaf* newReaf = new Reaf();
	newReaf->SetIsAlive(true);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(-20, 20); //プレイエリアは -20.0f - 20.0f
	int randomNumber = dist(gen);
	//葉っぱの位置をセットする
	newReaf->SetSpawnPoint({float(randomNumber), newReaf->GetSpawnPoint().y + 10.0f, newReaf->GetSpawnPoint().z});
	//借りの変数に保留
	Vector3 reafPosition = newReaf->GetSpawnPoint();
	newReaf->Initialize(reafModel_, viewProjection_, reafPosition);
	reafs_.push_back(newReaf);
}

void ItemManager::RingoSpawn() {
	Ringo* newRingo = new Ringo();
	//発生フラグをtrueに
	newRingo->SetIsAlive(true);
	//乱数でｘの位置を決め
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(-20, 20); //プレイエリアは -20.0f - 20.0f
	int randomNumber = dist(gen);
	//発生位置を設置する
	newRingo->SetSpawnPoint({float(randomNumber), 10.0f, 0.0f}); //今んとこｙとｚは適当
	//借り変数に保留
	Vector3 ringoPosition = newRingo->GetSpawnPoint();
	//初期化を行う
	newRingo->Initialize(ringoModel_, viewProjection_, ringoPosition);
	//listの裏に追加する
	ringos_.push_back(newRingo);
}

void ItemManager::CheckIfGround() { 
	for (auto* reafs : reafs_) {
		if (reafs->GetPosition().y <= 0.0f) {
		}
	}

	for (auto* ringos : ringos_) {
		if (ringos->GetPosition().y <= 0.0f) {
			//ringos->SetIsAlive(false);
			//ringos->SetPositionOutOfBounds();
		}
	}
}
