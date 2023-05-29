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

	worldTransform_.translation_ = {5.0f,0.0f,40.0f};

	
	
}

void Enemy::Update() {
	
	Vector3 move = {0.0f, 0.0f, 0.2f};

	
	worldTransform_.UpdateMatrix();

	
	phaseReset();
	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}
	

	switch (phase_) {
	case Phase::Approach:
		
		
		worldTransform_.translation_.z -= move.z;
		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Phase::Leave;
		}

		break;
	case Phase::Leave:

		worldTransform_.translation_.x -= move.x;
		worldTransform_.translation_.y += move.y;
		worldTransform_.translation_.z -= move.z;
		

		break;
	}


	ImGui::Begin("en");
	ImGui::Text(
	    " x: %f,y: %f z: %f", worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z);

	ImGui::End();

}

void Enemy::Draw(const ViewProjection& viewProjection) {
	
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	for (EnemyBullet* bullet : bullets_) {

		bullet->Draw(viewProjection);
	}

}

Enemy::~Enemy() {

	for (EnemyBullet* bullet : bullets_) {

		delete bullet;
	}

}

void Enemy::Fire() {

		

	const float kBulletSpeed = 0.4f;
	Vector3 velocity(0, 0, kBulletSpeed);

	velocity = TransformNormal(velocity, worldTransform_.matWorld_);

	EnemyBullet* newBullet = new EnemyBullet();

	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	bullets_.push_back(newBullet);


}

void Enemy::phaseReset() {

	fireTimer--;

	if (fireTimer <= 0) {
		
		Fire();

		fireTimer = kFireInterval;
	}
}
