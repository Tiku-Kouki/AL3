#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "Affine.h"
#include <list>

enum class Phase {
	Approach,//接近する
	Leave,//離脱する
};

class Enemy {

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	void Initialize(Model* model, uint32_t textureHandle);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Draw(const ViewProjection& viewProjection);

	

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;

	Phase phase_ = Phase::Approach;

};
