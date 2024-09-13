#include "Ringo.h"
#include <cassert>
#include <algorithm>
#include "Model.h"
#include "Player.h"

void Ringo::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) { 
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	viewProjection_ = viewProjection;
	worldTransform_.translation_ = position;
	worldTransform_.rotation_ = {};
}

void Ringo::Update() { 

	worldTransform_.UpdateMatrix();

	if (worldTransform_.translation_.y > 0.0f) {
	
		velocity_.y += -kGravityAcceleration;
		if (velocity_.y <= -kLimitFallSpeed) {
			velocity_.y = -kLimitFallSpeed;
		}
		worldTransform_.translation_.y += velocity_.y;
	}

}

void Ringo::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

Vector3 Ringo::GetWorldPosition() { 
	Vector3 worldPos{};
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void Ringo::SetPositionOutOfBounds() {
	spawnPoint_ = {0.0f, -100.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, -100.0f, 0.0f};
}

AABB Ringo::GetAABB() {
	Vector3 worldPos = GetWorldPosition();
	AABB aabb;
	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};
	return aabb;
}

void Ringo::OnCollision(const Player* player) {
	(void)player;
	isAlive_ = false;
	SetPositionOutOfBounds();
}
