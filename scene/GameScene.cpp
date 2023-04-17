#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete sprite_; 
	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandle_ = TextureManager::Load("hensei.png");
	sprite_ = Sprite::Create(textureHandle_, {100, 50});
	model_ = Model::Create();
	worldTransform_.Initialize();
	viewProjection_.Initialize();
	
	soundDataHandle_ = audio_->LoadWave("mokugyo.wav");
	audio_->PlayWave(soundDataHandle_);

	voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);

	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);
	//デバックカメラ
	debugCamera_ = new DebugCamera(1280, 729);
	//軸方向表示
	AxisIndicator::GetInstance()->SetVisible(true);

	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

}

void GameScene::Update() { 
	Vector2 position = sprite_->GetPosition();
	position.x -= 5.0f;
	position.y -= 2.0f;

	sprite_->SetPosition(position);//動かす
	if (input_->TriggerKey(DIK_SPACE)) {
	
	audio_->StopWave(voiceHandle_);
	}

	ImGui::Begin("Debug1");
	ImGui::Text("Hellow World %d.%d.%d", 2023, 04, 17);
	ImGui::InputFloat3("InputFloat3", inputFloat3);
	ImGui::SliderFloat3("SliderFloat3", inputFloat3, 0.0f, 1.0f);
	ImGui::ShowDemoWindow();
	ImGui::End();

	debugCamera_->Update();
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
	
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);
	
	PrimitiveDrawer::GetInstance()->DrawLine3d({0, 0, 0}, {10, 0, 0}, {0.0f,1.0f,0.0f,1.0f});
	

	
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	sprite_->Draw();





	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
