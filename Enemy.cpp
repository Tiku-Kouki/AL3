#include "Enemy.h"
#include "cassert"
#include "ImGuiManager.h"


void Enemy::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);

	model_ = model;

	
	textureHandle_ = textureHandle;
	

	worldTransform_.Initialize();


	worldTransform_.scale_ = {3.0f, 3.0f, 3.0f};

	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};

	worldTransform_.translation_ = {0.0f,5.0f,40.0f};

	

}
void (Enemy::*Enemy::Phase_[])() ={
        &Enemy::Approach, // 接近する
        &Enemy::Leave,      // 離脱する

};

void Enemy::Update() {
	
	Vector3 move = {0.1f, 0.1f, 0.3f};

	
	worldTransform_.UpdateMatrix();

	


	(this->*Phase_[static_cast<size_t>(phase_)])();


	


	ImGui::Begin("en");
	ImGui::Text(
	    " x: %f,y: %f z: %f", worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z);

	ImGui::End();

}

void Enemy::Draw(const ViewProjection& viewProjection) {
	
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Enemy::Approach() {
	Vector3 move = {0.0f, 0.0f, 0.3f};

	worldTransform_.translation_.z -= move.z;
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave_;
	}

}

void Enemy::Leave() { 
	Vector3 move = {0.1f, 0.1f, 0.3f};

	worldTransform_.translation_.x -= move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z -= move.z;

}
