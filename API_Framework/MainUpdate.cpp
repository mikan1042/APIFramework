#include "MainUpdate.h"
#include "Player.h"
#include "Enemy.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "ObjectManager.h"


MainUpdate::MainUpdate()
{

}

MainUpdate::~MainUpdate()
{
	Release();
}


void MainUpdate::Initialize()
{
	m_hdc = GetDC(g_hWnd);

	SceneManager::GetInstance()->SetScene(SCENEID::LOGO);
}

void MainUpdate::Update()
{
	if(!ObjectManager::GetInstance()->GetPlayer()->GetHp() <= 0)
	SceneManager::GetInstance()->Update();

	InputManager::GetInstance()->CheckKey();
}

void MainUpdate::Render()
{
	SceneManager::GetInstance()->Render(m_hdc);
}

void MainUpdate::Release()
{
	
}
