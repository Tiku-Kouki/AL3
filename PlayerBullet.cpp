#include "PlayerBullet.h"
#include "cassert"



void PlayerBullet::Initialize(Model* model, const Vector3& position) { 
	
	assert(model);

	model_ = model;

	textureHandle_ = TextureManager::Load("mario.png");

	worldTransform_.translation_ = position;

	worldTransform_.Initialize(); 
	


}

void PlayerBullet::Update() {

worldTransform_.UpdateMatrix();


}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {

model_->Draw(worldTransform_, viewProjection, textureHandle_);

}
