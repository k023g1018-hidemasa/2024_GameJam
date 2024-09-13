#define NOMINMAX
#include "CameraController.h"
#include "WorldTransform.h"
#include "Player.h"
#include "ViewProjection.h"
#include <numbers>
#include <algorithm>

void CameraController::Initialize(ViewProjection* viewProjection) {
	viewProjection_ = viewProjection;
}

void CameraController::Update(){
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	Vector3 targetSpeed = target_->GetVelocity();
	Vector3 temp = Multiply(kVelocityBias, targetSpeed);
	Vector3 temp1 = Add(temp, targetOffset_);
	targetDestination_ = Add(targetWorldTransform.translation_, temp1);

	viewProjection_->translation_.x = std::lerp(viewProjection_->translation_.x, targetDestination_.x, kInterpolationRate);
	viewProjection_->translation_.y = std::lerp(viewProjection_->translation_.y, targetDestination_.y, kInterpolationRate);

	viewProjection_->translation_.x = std::max(viewProjection_->translation_.x, movableArea_.left);
	viewProjection_->translation_.x = std::min(viewProjection_->translation_.x, movableArea_.right);
	viewProjection_->translation_.y = std::max(viewProjection_->translation_.y, movableArea_.bottom);
	viewProjection_->translation_.y = std::min(viewProjection_->translation_.y, movableArea_.top);
	viewProjection_->UpdateMatrix();
}

void CameraController::Reset(){
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	viewProjection_->translation_ = Add(targetWorldTransform.translation_, targetOffset_);
}


