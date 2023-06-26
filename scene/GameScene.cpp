#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include"AxisIndicator.h"
#include<math.h>

GameScene::GameScene() {}

GameScene::~GameScene() {

	delete model_;
	delete player_;
	delete debugCamera_;
	delete enemy_;
	delete modelSkydome_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandle_ = TextureManager::Load("mario.png");
	textureHandle2_ = TextureManager::Load("tex1.png");

	model_ = Model::Create();

	viewProjection_.Initialize();

	player_ = new Player();

	player_->Initalize(model_, textureHandle_);

	debugCamera_ = new DebugCamera(1280, 720);

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	enemy_ = new Enemy();

	enemy_->Initialize(model_, textureHandle2_);

	enemy_->SetPlayer(player_);

	skydome_ = new Skydome;
	
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	
	skydome_->Initialize(modelSkydome_);
}

void GameScene::Update() {

	player_->Update();

	enemy_->Update();

	skydome_->Update();

	CheckAllCollisions();
#ifdef _DEBUG

	if (input_->PushKey(DIK_SPACE)) {
		isDebugCameraActive_ = true;
	}

#endif // DEBUG
	if (isDebugCameraActive_ == true) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		viewProjection_.TransferMatrix();
	} else {

		viewProjection_.UpdateMatrix();
	}
}

void GameScene::CheckAllCollisions() 
{ Vector3 posA, posB;

const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();

const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets(); 

#pragma region //自キャラと敵弾の当たり判定
posA = player_->GetWorldPosition();

for (EnemyBullet* bullet : enemyBullets) 
{
		posB = bullet->GetWorldPosition();  
		
		float X = (posB.x - posA.x);
		float Y = (posB.y - posA.y);
		float Z = (posB.z - posA.z);

		float center = X * X + Y * Y + Z * Z;
		float R1 = 3.0f;//自分で決める
		float R2 = 1.0f;//自分で決める
		float RR = (R1 + R2);

		if (center <= (RR * RR)) {
		//自キャラの衝突時コールバックを呼び出す
			player_->OnColision();
		//敵弾の衝突時コールバックを呼び出す
			bullet->OnColision();
		}

}
#pragma endregion

#pragma region//自弾と敵キャラの当たり判定
posA = enemy_->GetWorldPosition();

for (PlayerBullet* bullet : playerBullets) {
		posB = bullet->GetWorldPosition();

		float X = (posB.x - posA.x);
		float Y = (posB.y - posA.y);
		float Z = (posB.z - posA.z);

		float center = sqrtf(X * X + Y * Y + Z * Z);
		float R1 = 1.5f; // 自分で決める
		float R2 = 0.5f; // 自分で決める
		float RR = (R1 + R2);

		if (center <= (RR * RR)) {
			// 自キャラの衝突時コールバックを呼び出す
			enemy_->OnColision();
			// 敵弾の衝突時コールバックを呼び出す
			bullet->OnColision();
		}
}


#pragma endregion

#pragma region//自弾と敵弾の当たり判定
for (EnemyBullet* bullet1 : enemyBullets) {

	for (PlayerBullet* bullet2 : playerBullets) {
			posA = bullet1->GetWorldPosition();
			posB = bullet2->GetWorldPosition();

			float X = (posB.x - posA.x);
			float Y = (posB.y - posA.y);
			float Z = (posB.z - posA.z);

			float center = sqrtf(X * X + Y * Y + Z * Z);
			float R1 = 1.0f; // 自分で決める
			float R2 = 1.0f; // 自分で決める
			float RR = (R1 + R2);

			if (center <= (RR * RR)) {
				// 自キャラの衝突時コールバックを呼び出す
				bullet1->OnColision();
				// 敵弾の衝突時コールバックを呼び出す
				bullet2->OnColision();
			}
	}
}
#pragma endregion

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	player_->Draw(viewProjection_);
	enemy_->Draw(viewProjection_);

	skydome_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
