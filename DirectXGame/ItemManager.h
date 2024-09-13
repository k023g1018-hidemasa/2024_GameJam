#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include <list>
#include "Ringo.h"
#include "Reaf.h"

class Model;

enum class Phase {
	easy,
	normal,
	hard,
	phaseNum
};

class ItemManager 
{
public:
	ItemManager() {}
	~ItemManager();

	void Initialize(ViewProjection* viewProjection);
	void Update();
	void Draw();
	/// <summary>
	/// 葉っぱ
	/// </summary>
	void ReafSpawn();
	/// <summary>
	/// リンゴ
	/// </summary>
	void RingoSpawn();
	
	std::list<Reaf*> GetReafs() { return reafs_; }
	std::list<Ringo*> GetRingo() { return ringos_; }

	void CheckIfGround();
	uint32_t GetGameOverCount() { return gameOverCount_; }

private:
	int32_t gameTimer_ = 0;
	//Phase phase_ = Phase::easy;

	ViewProjection* viewProjection_;
	WorldTransform worldTransfrom_;

	// リーフのテクスチャハンドルとか
	Model* reafModel_ = nullptr;
	std::list<Reaf*> reafs_;
	int32_t kReafNumber = 1;

	Model* ringoModel_ = nullptr;
	std::list<Ringo*> ringos_;
	int32_t kRingoNumber = 1;

	int32_t gameOverCount_ = 1;
	bool isDropped = false;
};
