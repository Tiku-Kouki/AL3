#include "Player.h"
#include "ImGuiManager.h"
#include "cassert"

void Player::Initalize(Model* model, uint32_t textureHandle, Vector3 playerPosition) {

	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.scale_ = {2.0f, 2.0f, 2.0f};

	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};

	worldTransform_.translation_ = playerPosition;

	worldTransform_.Initialize();

	input_ = Input::GetInstance();

	worldTransform3DReticle_.Initialize();

	//レティクル用テクスチャ取得
	uint32_t textureReticle = TextureManager::Load("2DReticle.png");

	//スプライト生成
	sprite2DReticle_ = Sprite::Create(
	    textureReticle, {0.0f, 0.0f},
	    {1.0f, 1.0f, 1.0f, 1}, {0.5f, 0.5f});

}
void Player::Rotate() {

	const float kRotSpeed = 0.02f;

	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	} else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}
}

void Player::Update(ViewProjection& viewProjection) {

	Vector3 move = {0, 0, 0};

	const float kCharacterSpeed = 0.2f;

	// デスフラグの立った弾を削除
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;

			return true;
		}
		return false;
	});


	Rotate();

	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	const float kMoveLimitX = 20;
	const float kMoveLimitY = 18;

	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	worldTransform_.UpdateMatrix();

	
	
	//自機のワールド座標から3Dレティクルのワールド座標を計算
	
	// 自機から3Dレティクルへの距離
	//const float kDistancePlayerTo3DReticle = 50.0f;
	// 自機から3Dレティクルへのオフセット(Z+向き)
	Vector3 offset = {0, 0, 1.0f};

	

	// 自機のワールド行列の回転を反映
	offset = MultiplyT(offset, worldTransform_.matWorld_);

	ImGui::Begin("offset");

	ImGui::Text("offset : x: %f,y: %f z: %f", offset.x, offset.y, offset.z);

	ImGui::End();

	// ベクトルの長さを整える
	//offset = Multiply(kDistancePlayerTo3DReticle,Normalize(offset));

	

	//// 3Dレティクルの座標を設定
	//worldTransform3DReticle_.translation_ = Add(GetWorldPosition(), offset);
	//
	//worldTransform3DReticle_.UpdateMatrix();

	GetmMouse(viewProjection);

	Attack();

	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}

	////3Dレティクルのワールド座標から2Dレティクルのスクリーン座標を計算

	//Vector3 positionReticle = {
	//    worldTransform3DReticle_.matWorld_.m[3][0], worldTransform3DReticle_.matWorld_.m[3][1],
	//    worldTransform3DReticle_.matWorld_.m[3][2]};

	////ビューポート行列
	//Matrix4x4 matViewport = MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);

	//Matrix4x4 matViewProjectionViewport =
	//    Multiply(Multiply(viewProjection.matView ,viewProjection.matProjection),matViewport);


	//positionReticle = Transform(positionReticle, matViewProjectionViewport);


	////sprite2DReticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));


	




	ImGui::Begin("player");
	ImGui::Text(
	    " x: %f,y: %f z: %f", worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z);
	//ImGui::DragFloat3("Translation", &worldTransform_.translation_.x, 0.01f);
	//ImGui::DragFloat3("Rotation", &worldTransform_.rotation_.x, 0.01f);
	ImGui::Text(
	    "LocalPos :  %f,%f,%f", worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z);
	ImGui::Text(
	    "LocalRotate :  %f,%f,%f", worldTransform_.rotation_.x, worldTransform_.rotation_.y,
	    worldTransform_.rotation_.z);

	ImGui::Text(
	    "worldPos :  %f,%f,%f", GetWorldPosition().x, GetWorldPosition().y, GetWorldPosition().z);

	ImGui::End();

	ImGui::Begin("Reticle");

	ImGui::Text(
	    "worldPos : %f,%f,%f", 
		worldTransform3DReticle_.matWorld_.m[3][0],
	    worldTransform3DReticle_.matWorld_.m[3][1],
		worldTransform3DReticle_.matWorld_.m[3][2]
	);
	ImGui::Text(
	    "LocalPos : %f,%f,%f", 
		worldTransform3DReticle_.translation_.x,
	    worldTransform3DReticle_.translation_.y,
		worldTransform3DReticle_.translation_.z
	);

	ImGui::End();
}

void Player::Draw(ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	for (PlayerBullet* bullet : bullets_) {
	
	bullet->Draw(viewProjection);
	}
	
	model_->Draw(worldTransform3DReticle_, viewProjection);
}

Player::~Player() {

	for (PlayerBullet* bullet : bullets_) {

	delete bullet;
	}
	 
	delete sprite2DReticle_;
}

void Player::Attack() {

	if (input_->PushKey(DIK_SPACE)) {

		/*if (bullet_) {
			delete bullet_;
		
			bullet_ = nullptr;
		}*/
		
		const float kBulletSpeed = 1.0f;
	Vector3 velocity(0, 0, kBulletSpeed);

	



	Vector3 playerWorld = GetWorldPosition();

	velocity = Subtract(
		{	worldTransform3DReticle_.matWorld_.m[3][0], 
			worldTransform3DReticle_.matWorld_.m[3][1], 
			worldTransform3DReticle_.matWorld_.m[3][2]
		 },
		playerWorld);

	velocity = Multiply(kBulletSpeed, Normalize(velocity));

	velocity = TransformNormal(velocity, worldTransform_.matWorld_);

		PlayerBullet* newBullet = new PlayerBullet();

		newBullet->Initialize(model_, playerWorld, velocity);

		bullets_.push_back(newBullet);
	}


}

Vector3 Player::GetWorldPosition() {

Vector3 worldPos = {};

worldPos.x = worldTransform_.matWorld_.m[3][0];
worldPos.y = worldTransform_.matWorld_.m[3][1];
worldPos.z = worldTransform_.matWorld_.m[3][2];

return worldPos;

}

void Player::OnColision() {
}

void Player::SetParent(const WorldTransform* parent) 
{ worldTransform_.parent_ = parent;

}

void Player::DrawUI() {


	sprite2DReticle_->Draw();

}

void Player::GetmMouse(ViewProjection& viewProjection) {


	POINT mousePosition;
	// マウス座標(スクリーン座標)を取得する
	GetCursorPos(&mousePosition);
	// クライアントエリア座標に変換する
	HWND hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);
	sprite2DReticle_->SetPosition(Vector2((float)mousePosition.x, (float)mousePosition.y));


	// ビューポート行列
	Matrix4x4 matViewport = MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);

	//ビュープロジェクションビューポート合成行列
	Matrix4x4 matVPV = Multiply(Multiply(viewProjection.matView, viewProjection.matProjection), matViewport);

	//合成行列の逆行列を計算する
	Matrix4x4 matInverseVPV = Inverse(matVPV);

	ImGui::Begin("vlayer");
	
	ImGui::Text(
	    "vpv:(%f,%f,%f,%f)\n,(%f,%f,%f,%f)\n,(%f,%f,%f,%f)\n,(%f,%f,%f,%f)\n ",
		matVPV.m[0][0], matVPV.m[0][1], matVPV.m[0][2], matVPV.m[0][3],
		matVPV.m[1][0], matVPV.m[1][1], matVPV.m[1][2], matVPV.m[1][3], 
		matVPV.m[2][0], matVPV.m[2][1], matVPV.m[2][2], matVPV.m[2][3], 
		matVPV.m[3][0], matVPV.m[3][1], matVPV.m[3][2], matVPV.m[3][3]);

	ImGui::Text(
	    "Inverse:(%f,%f,%f,%f)\n,(%f,%f,%f,%f)\n,(%f,%f,%f,%f)\n,(%f,%f,%f,%f)\n ",
	    matInverseVPV.m[0][0], matInverseVPV.m[0][1], matInverseVPV.m[0][2], matInverseVPV.m[0][3],
	    matInverseVPV.m[1][0], matInverseVPV.m[1][1], matInverseVPV.m[1][2], matInverseVPV.m[1][3],
	    matInverseVPV.m[2][0], matInverseVPV.m[2][1], matInverseVPV.m[2][2], matInverseVPV.m[2][3],
	    matInverseVPV.m[3][0], matInverseVPV.m[3][1], matInverseVPV.m[3][2], matInverseVPV.m[3][3]
	);
	ImGui::End();


	//スクリーン座標系
	Vector3 posNear = Vector3((float)mousePosition.x, (float)mousePosition.y, 0);
	Vector3 posFar = Vector3((float)mousePosition.x, (float)mousePosition.y, 1);

	// スクリーン座標系からワールド座標へ
	posNear = Transform(posNear, matInverseVPV);
	posFar = Transform(posFar, matInverseVPV);

	//マウスレイの方向
	Vector3 mouseDirection = Subtract(posFar, posNear);
	mouseDirection = Normalize(mouseDirection);

	//カメラから照準オブジェクトの距離
	const float kDistanceTestObject = 50.0f;

	worldTransform3DReticle_.translation_ =
	    Add(posNear,Multiply(kDistanceTestObject, mouseDirection));

	worldTransform3DReticle_.UpdateMatrix();

	ImGui::Begin("Player");
	ImGui::Text("2DReticle:(%f,%f)", sprite2DReticle_->GetPosition().x, sprite2DReticle_->GetPosition().y);
	
	ImGui::Text("Near:(%+.2f,%+.2f,%+.2f)", posNear.x, posNear.y, posNear.z);
	ImGui::Text("Far:(%+.2f,%+.2f,%+.2f)", posFar.x, posFar.y, posFar.z);

	ImGui::Text(
	    "3DReticle:(%+.2f,%+.2f,%+.2f)", worldTransform3DReticle_.translation_.x,
	    worldTransform3DReticle_.translation_.y, worldTransform3DReticle_.translation_.z);

	ImGui::End();



}
