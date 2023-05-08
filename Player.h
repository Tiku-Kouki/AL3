#pragma once
#include "Affine.h"
#include "Input.h"
#include "Model.h"
#include "PlayerBullet.h"
#include "WorldTransform.h"

class Player {
public:
	void Initalize(Model* model, uint32_t textureHandle);

	void Update();

	void Rotate();

	void Draw(ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;

	PlayerBullet* bullet_ = nullptr;

	void Attack();
};
