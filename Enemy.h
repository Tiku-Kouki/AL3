#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "Affine.h"
#include <list>
#include"EnemyBullet.h"


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

	void Approach_(); // 接近する
	void Leave_();


	~Enemy();

	/// <summary>
	/// 弾発射
	/// </summary>
	void Fire();

	static const int kFireInterval = 60;

	void phaseReset();


private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;

	Phase phase_ = Phase::Approach;

	static void (Enemy::*Phase_[])();

	std::list<EnemyBullet*> bullets_;

	int32_t fireTimer = 0;

};
