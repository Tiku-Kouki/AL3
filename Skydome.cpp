#include "Skydome.h"
#include "cassert"

void Skydome::Initialize(Model* model) { 

	assert(model);
	model_ = model;
	


	worldTransform_.scale_ = {150.0f, 150.0f, 150.0f};

	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};

	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};

	worldTransform_.Initialize();
	
}

void Skydome::Update() { worldTransform_.UpdateMatrix(); }

void Skydome::Draw(ViewProjection& viewProjection) 
{
	model_->Draw(worldTransform_, viewProjection);
}

Skydome::~Skydome() { 
	

}
