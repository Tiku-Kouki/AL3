#pragma once
#include "Affine.h"
#include "Input.h"
#include "Model.h"
#include "PlayerBullet.h"
#include "WorldTransform.h"
#include <list>


class Player {
public:
	void Initalize(Model* model, uint32_t textureHandle);

	void Update();

	void Rotate();

	void Draw(ViewProjection& viewProjection);

	~Player();

	void Attack();

	Vector3 GetWorldPosition();

	void OnColision();
	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;

	std::list <PlayerBullet*> bullets_;

	
};
