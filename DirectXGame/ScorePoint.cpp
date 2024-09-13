#include "ScorePoint.h"
#include "Reaf.h"
#include "player.h"
#include <algorithm>
#include <iostream>

void ScorePoint::Initialize(Model* scorePointModel, ViewProjection* viewProjection, const Vector3& position) {
	scorePointModel_ = scorePointModel;
	// 行列を定数バッファに転送//定数バッファ＝グラボ
	viewProjection_ = viewProjection;
	objectColor_.Initialize();
	color_ = {1, 1, 1, 1};
	

	for (auto& worldTransform : worldTransforms_) {
		worldTransform.Initialize(); // whay
		worldTransform.translation_ = position;
		worldTransform.translation_={10, 10, 10};
		}
		 uint32_t offset;
	for (uint32_t i = 0; i < kNumScores; ++i) {
		     offset = i;
		worldTransforms_[i].translation_.x = worldTransforms_[i].translation_.x+i;
	}
	//getPoint = new Reaf;
}

void ScorePoint::Update() {

	getPoint->GetPoint();


	for (auto& worldTransform : worldTransforms_) {
		worldTransform.UpdateMatrix();
	}


}

void ScorePoint::Draw() {

	
	//ここができれば0123と作る
	
		for (uint32_t i = 0; i < kNumScores; ++i) {

			if (getPoint->GetPoint() % 10 >= 1) { // もしスコアポイントが位置の位が1いじょうなら
			    if (getPoint->GetPoint() % 10 == 1) {
					// 次はここに足す
					//  1を表示

					scorePointModel_->Draw(worldTransforms_[i], *viewProjection_, &objectColor_);

				} else if (getPoint->GetPoint() % 10 == 2) {
					// 2
			    } else if (getPoint->GetPoint()  % 10 == 3) {
					// 3
			    } else if (getPoint->GetPoint() % 10 == 4) {
					// 4
			    } else if (getPoint->GetPoint() % 10 == 5) {
					// 5
			    } else if (getPoint->GetPoint() % 10 == 6) {
					// 6
			    } else if (getPoint->GetPoint() % 10 == 7) {
					// 7
			    } else if (getPoint->GetPoint() % 10 == 8) {
					// 8
			    } else if (getPoint->GetPoint() % 10 == 9) {
					// 9
				}
		    } else if (getPoint->GetPoint() % 10 == 0) {
				// ゼロを表示

				scorePointModel_->Draw(worldTransforms_[i], *viewProjection_, &objectColor_); // コレでゼロかな
			}
		}
	}


void ScorePoint::ZeroInitialize(Model* modelZero, ViewProjection* viewProjection, const Vector3& position) {
	modelZero = zeloModel_;
	// 行列を定数バッファに転送//定数バッファ＝グラボ
	viewProjection_ = viewProjection;

	for (auto& worldTransform : worldTransforms_) {
		worldTransform.Initialize(); // whay
		worldTransform.translation_ = position;
	}
}
