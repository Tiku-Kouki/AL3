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

void (Enemy::*Enemy::Phase_[])() = {
    &Enemy::Approach_, // 接近する
    &Enemy::Leave_,    // 離脱する

};

void Enemy::Update() {
	
	Vector3 move = {0.0f, 0.0f, 0.2f};

	
	worldTransform_.UpdateMatrix();

	
	phaseReset();
	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}
	

	(this->*Phase_[static_cast<size_t>(phase_)])();


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

void Enemy::Approach_() {
	Vector3 move = {0.0f, 0.0f, 0.3f};

	worldTransform_.translation_.z -= move.z;
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}

}

void Enemy::Leave_() {
	Vector3 move = {0.1f, 0.1f, 0.3f};

	worldTransform_.translation_.x -= move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z -= move.z;


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
