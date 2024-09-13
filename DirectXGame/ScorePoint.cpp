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
	}
	
	for (uint32_t i = 0; i < kNumScores; ++i) {
		worldTransforms_[i].translation_.x = worldTransforms_[i].translation_.x + i;
	}
}

void ScorePoint::Update() {

	


	/*for (auto& worldTransform : worldTransforms_) {
		worldTransform.UpdateMatrix();
	}*/


}

void ScorePoint::Draw(int score) {

	
	//ここができれば0123と作る
	
		for (uint32_t i = 0; i < kNumScores; ++i) {

			if (score % 10 >= 1) { // もしスコアポイントが位置の位が1いじょうなら
				if (score % 10 == 1) {
					// 次はここに足す
					//  1を表示

					scorePointModel_->Draw(worldTransforms_[i], *viewProjection_, &objectColor_);

				} else if (score % 10 == 2) {
					// 2
			    } else if (score % 10 == 3) {
					// 3
			    } else if(score % 10 == 4) {
					// 4
			    } else if (score % 10 == 5) {
					// 5
			    } else if (score % 10 == 6) {
					// 6
			    } else if (score % 10 == 7) {
					// 7
			    } else if (score % 10 == 8) {
					// 8
			    } else if (score % 10 == 9) {
					// 9
				}
		    } else if (score % 10 == 0) {
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
