#ifndef PI
#define PI 3.14159265358979323846
#endif
#include "Ground.h"
#include"Model.h"
#include"ViewProjection.h"
#include <cassert>

void Ground::Initialize(Model* model, ViewProjection* viewProjection){
	float pi = float(PI);
	assert(model);
	modelPlayer_ = model;
	worldTransform_.Initialize();
	viewProjection_ = viewProjection;
	worldTransform_.rotation_.x = -float(pi / 2.0f);
	worldTransform_.scale_ = { 20.0f,20.0f,20.0f };
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
}

void Ground::Update(){
	worldTransform_.UpdateMatrix();
}

void Ground::Draw(){
	modelPlayer_->Draw(worldTransform_, *viewProjection_);
}
