#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "Affine.h"


class Player {
public:

	void Initalize(Model* model, uint32_t textureHandle);


	void Update();

	void Rotate();



	void Draw(ViewProjection &viewProjection);

private:

	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;

	};
