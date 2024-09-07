#pragma once

//様々なシーンクラス化を提供できすベース
class SceneBase {
public:
	virtual ~SceneBase() = default;
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};