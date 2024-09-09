#include "Reaf.h"
#include "assert.h"
#include <cmath>
#include <fstream>
#include <vector>

Reaf::Reaf() {}

Reaf::~Reaf() {}

Vector3 Lerp(const Vector3& a, const Vector3& b, float t) { // イージングシートのリターンをｔに入れたらできる
	Vector3 resurt{};
	// return{ t * a.x + (1.0f - t) * b.x ,t * a.y + (1.0f - t) * b.y };//かっこで囲ったら行けるらしい
	
	resurt.x = t * b.x + (1.0f - t) * a.x;
	resurt.y = t * b.y + (1.0f - t) * a.y;
	resurt.z = t * b.z + (1.0f - t) * a.z; 
	return resurt;
}



void Reaf::Initialize(Model* enemyModel, ViewProjection* viewProjection, const Vector3& position) {
	assert(enemyModel);
	enemyModel_ = enemyModel;
	worldTransform_.Initialize();
	viewProjection_ = viewProjection;
	worldTransform_.translation_ = position; // ここで場所を代入している
	worldTransform_.rotation_.y = std::numbers::pi_v<float> * 3.0f / 2.0f;

	// 速度の設定
	verocity_ = {-kWalkSpeed, -kWalkSpeed, 0};
	wolkTimer_ = 0.0f;

	/// 葉っぱの振り子
	spawnPoint = worldTransform_.translation_;
	
}

void Reaf::Update() {

	
	// 追従対象とオフセットからカメラの座標を計算//演算子のエラーもし動かなかったらここが原因かも（VECTOR3）
	
	//////////////
	// 
	// //羽っぽい動き
	// 座標保管 targetCoordinates//開始位置から終点まで
	if (spawnPoint.x + targetOffset_.x <= worldTransform_.translation_.x+3) {//45より場所が大きいとき//スポーンした位置から15-3離れた位置から交代
		switchPendulum = false;
	} else if (spawnPoint.x - targetOffset_.x >= worldTransform_.translation_.x-3) {//25より小さいとき
		switchPendulum = true;
	}
	if (switchPendulum == true) {
		//ここはｘだけ計算
		if (spawnPoint.x<=worldTransform_.translation_.x) {
		worldTransform_.translation_ = Lerp(worldTransform_.translation_, Vector3{spawnPoint.x+targetOffset_.x , spawnPoint.y-targetOffset_.y, spawnPoint.z}, easeInOutCubic(kInterpolationRate));
		} else {
		worldTransform_.translation_ = Lerp(worldTransform_.translation_, Vector3{spawnPoint.x+targetOffset_.x,spawnPoint.y+targetOffset_.y,spawnPoint.z} , easeInOutCubic(kInterpolationRate));
		}
	
	} else if (switchPendulum == false) {
		if (spawnPoint.x >= worldTransform_.translation_.x) {
		worldTransform_.translation_ = Lerp(worldTransform_.translation_, Vector3{spawnPoint.x - targetOffset_.x, spawnPoint.y-targetOffset_.y, spawnPoint.z}, easeInOutCubic(kInterpolationRate));	
		} else {
			worldTransform_.translation_ = Lerp(worldTransform_.translation_, Vector3{spawnPoint.x - targetOffset_.x, spawnPoint.y + targetOffset_.y, spawnPoint.z}, easeInOutCubic(kInterpolationRate));
		}
	}
	


	//worldTransform_.translation_ += verocity_;
	wolkTimer_ += 1.0f / 60.0f;
	// 回転アニメーション
	//
	// 22pはこの式であってるのか
	float param = std::sin((2 * 3.14f) * wolkTimer_ / kWalkMotionTime);
	float radian = kWalkMotionAngleStart + kWalkMotionAngleEnd * (param + 1.0f) / 2.0f;
	worldTransform_.rotation_.x = radian * 3.14f / 360.0f; // よくわからん
	if (spawnTimer >= 60) {
	}
	//otiru
	worldTransform_.translation_.y += verocity_.y;
	//スポーンポイントを下げる
	spawnPoint.y += verocity_.y;


	// 多分アップデートマトリクスがワールド行列の更新？
	worldTransform_.UpdateMatrix(); // これを通ったらアフィンとかを通るからアップデートにはこれが必要
}

void Reaf::Draw() { enemyModel_->Draw(worldTransform_, *viewProjection_, textureHandle_); }
Vector3 Reaf::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

AABB Reaf::GetAABB() {

	Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;
}

void Reaf::OnCollision(const Player* player) { (void)player; }

