#define NOMINMAX
#include "Player.h"
#include <algorithm>
#include "Ringo.h"
#include "Reaf.h"

Player::Player() {}

Player::~Player() {} // 未定義、参照されてないは関数の作り忘れ

void Player::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);
	modelPlayer_ = model;
	worldTransform_.Initialize();
	// 行列を定数バッファに転送//定数バッファ＝グラボ
	viewProjection_ = viewProjection;
	worldTransform_.translation_ = { 0.0f,3.0f,0.0f }; //modelのサイズは2.0f x 2.0fので
	// 初期回転角の指定//Y軸を90度右に回転、2π
	worldTransform_.rotation_ = {0.0f, 2.0f, 0.0f};
	worldTransform_.scale_ = {2.0f, 2.0f, 2.0f};
}
void Player::Update() {
	// 接地フラグ
	bool landing = false;
	if (onGround_) {
		// 左右移動操作
		if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {
			// 左右加速
			Vector3 acceleration = {};
			if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
				// 左移動中の右入力
				if (velocity_.x < 0.0f) {
					// 速度と逆方向に入力中は急ブレーキ
					velocity_.x *= (1.0f - kAcceleration);
				}
				// 左右状態切り替え
				if (lrDirection_ != LRDirection::kRight) {
					lrDirection_ = LRDirection::kRight;
					// 旋回開始時の角度を記録する
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					// 旋回タイマーに時間を設定する
					turnTimer_ = kTimeTurn;
				}
				acceleration.x += kAcceleration;
			} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
				// 右移動中の左入力
				if (velocity_.x > 0.0f) {
					// 速度と逆方向に入力中は急ブレーキ
					velocity_.x *= (1.0f - kAcceleration);
				}
				// 左右状態切り替え
				if (lrDirection_ != LRDirection::kLeft) {
					lrDirection_ = LRDirection::kLeft;
					// 旋回開始時の角度を記録する
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					// 旋回タイマーに時間を設定する
					turnTimer_ = kTimeTurn;
				}
				acceleration.x -= kAcceleration;
			}
			// 加速原則
			velocity_.x += acceleration.x;

			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
		} else {
			// 火入力時は移動減衰を×
			velocity_.x *= (1.0f - kAttenuation);
			if (fabsf(velocity_.x) < 0.05f) {
				velocity_.x = 0;
			}
		}
		// ジャンプ開始
		if (worldTransform_.translation_.y > 3.0f) {
			// 空ちゅう状態に移行
			onGround_ = false;
		}
		// 移動
		//算術演算子が違った
		worldTransform_.translation_ += velocity_;
		// 空中
	} else {
		// 移動
		worldTransform_.translation_ += velocity_;
		// 落下速度
		velocity_.y += -kGravityAccleration;
		// 落下速度制限
		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);
		// 地面との当たり判定
		//  加工中？
		if (velocity_.y < 0) {
			// ｙ座標が地面いかになったら着地
			if (worldTransform_.translation_.y <= 0.0f) {
				landing = true;
			}
		}
		if (landing) {
			// めり込み排斥
			worldTransform_.translation_.y = 3.0f;
			// 摩擦で横方向速度が減衰知る
			velocity_.x *= (1.0f - kAttenuation); // お前誰やねん
			// 下方向速度をリセット
			velocity_.y = 0.0f;
			// 接地状態に移行
			onGround_ = true;
		}
	}

	// 千回制御
	if (turnTimer_ > 0.0f) {
		// 旋回タイマーをカウントダウン
		turnTimer_ -= 1.0f / 60.0f;

		// 左右の自キャラ角度テーブル
		float destinationRotationYTable[] = {std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f};
		// 状態に応じた角度を取得する
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
		// じきゃrの角度を設定する
		worldTransform_.rotation_.y = destinationRotationY; // ここに角度保管
	}

	Rotation();

	// 行列計算
	worldTransform_.UpdateMatrix();
}

void Player::Draw() {
	modelPlayer_->Draw(worldTransform_, *viewProjection_);
	/*ImGui::Begin("window");
	ImGui::InputFloat3("Velocity", &velocity_.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
	ImGui::End();*/
}

Vector3 Player::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos{};
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::Rotation() {
	if (turnTimer_ > 0.0f) {
		turnTimer_ -= 1.0f / 60.0f;

		float destinationRotationYTable[] = {std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> / -2.0f};

		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
		float timeRatio = 1 - turnTimer_ / kTimeTurn;
		float easing = 1 - powf(1 - timeRatio, 2);
		float newRotationY = std::lerp(turnFirstRotationY_, destinationRotationY, easing);
		worldTransform_.rotation_.y = newRotationY;
	}
}

AABB Player::GetAABB() {
	Vector3 worldPos = GetWorldPosition();
	AABB aabb{};
	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};
	return aabb;
}
void Player::OnCollision(Reaf* reaf) {
	(void)reaf;
	// ジャンプ開始（仮処理）
	//isDead_ = true; //	ここで変更
	worldTransform_.translation_.y += 5.0f;
}

void Player::OnCollision(Ringo* ringo) {

	(void)ringo;
	worldTransform_.translation_.y += 5.0f;

}


