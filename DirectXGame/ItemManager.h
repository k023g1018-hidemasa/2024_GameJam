#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include <list>

class Model;
class Reaf;

enum class Phase {
	easy,
	normal,
	hard,
	phaseNum
};

class ItemManager 
{
public:
	ItemManager(ViewProjection* viewProjection) { viewProjection_ = viewProjection; };
	~ItemManager();

	void Initialize();
	void Update();
	void Draw();
	/// <summary>
	/// 葉っぱ
	/// </summary>
	void ReafSpawn();
	std::list<Reaf*> GetReafs() { return reafs_; }

	void CheckIfGround();

private:
	int32_t gameTimer_;
	Phase phase_ = Phase::easy;

	ViewProjection* viewProjection_;
	WorldTransform worldTransfrom_;

	// リーフのテクスチャハンドルとか
	Model* reafModel_ = nullptr;
	std::list<Reaf*> reafs_;
	int32_t kReafNumber = 1;
};
