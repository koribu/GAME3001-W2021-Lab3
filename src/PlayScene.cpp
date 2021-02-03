#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);


	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}


	
}

void PlayScene::update()
{
	updateDisplayList();

}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";

	m_buildGrid();

}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("GAME3001 - Lab 2", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar|ImGuiWindowFlags_NoMove);

	static bool isGridEnabled = false;
	if(ImGui::Checkbox("Grid Enabled", &isGridEnabled))
	{
		//toggle the grid on
		m_setGridEnabled((isGridEnabled));
	}

	ImGui::Separator();
	
	if(ImGui::Button("Start"))
	{
		
	}
	ImGui::SameLine();
	if (ImGui::Button("Reset"))
	{

	}

	


	ImGui::Separator();

	

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}

void PlayScene::m_buildGrid()
{
	auto tileSize = Config::TILE_SIZE;
	
	for(int row=0;row<Config::ROW_NUM;++row)
	{
		for(int col=0;col<Config::COL_NUM;++col)
		{
			Tile* tile = new Tile();
			tile->getTransform()->position = glm::vec2(col * tileSize, row*tileSize);
			addChild(tile);
			tile->setEnabled(false);
			m_pGrid.push_back(tile);
		}
	}
}

void PlayScene::m_setGridEnabled(bool state) const
{
	for(auto tile: m_pGrid)
	{
		tile->setEnabled(state);
	}
	if(state == false)
	{
		SDL_RenderClear(Renderer::Instance()->getRenderer());
	}
}
