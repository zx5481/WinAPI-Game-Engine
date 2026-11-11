#include "pch.h"

#include "Scene_Start.h"

#include "Core.h"

#include "CollisionMgr.h"

#include "Object.h"
#include "Player.h"
#include "UI.h"
#include "ButtonUI.h"
#include "PanelUI.h"



Scene_Start::Scene_Start()
{

}

Scene_Start::~Scene_Start()
{

}

void Scene_Start::Update()
{
	Scene::Update();
}

void Scene_Start::Enter()
{
	Vec2 resolution = Core::GetInst()->GetResolution();

	Camera::GetInst()->SetLookAt(resolution / 2.f);

	Camera::GetInst()->FadeOut(1.f);
	Camera::GetInst()->FadeIn(1.f);

	Object* pPlayer = new Player;
	pPlayer->SetPosition(Vec2(640.f, 384.f));
	pPlayer->SetScale(Vec2(100.f, 100.f));
	AddObject(pPlayer, GROUP_TYPE::PLAYER);

	UI* pPanel = new PanelUI;
	pPanel->SetPosition(Vec2(640.f, 60.f));
	pPanel->SetScale(Vec2(50.f, 90.f));

	UI* pButton = new ButtonUI;
	pButton->SetPosition(Vec2(10.f, 10.f));
	pButton->SetScale(Vec2(30.f, 30.f));

	pPanel->AddChild(pButton);

	AddObject(pPanel, GROUP_TYPE::UI);
}

void Scene_Start::Exit()
{
	DeleteAll();

	CollisionMgr::GetInst()->Reset();
}