#include "../../../../common/stdafx.h"
#include "graphics_engine.h"
#include "../../../../common/sys.h"
#include "../../../../common/core.h"
#include "../../../../common/font.h"
#include "world.h"
#include "../Graphics/render_object.h"
#include <assert.h>
#include "Level.h"
#include "../Entities/Player.h"
#include "InterfaceController.h"

cGraphicsEngine& cGraphicsEngine::GetInstance()
{
	static cGraphicsEngine engine;
	return engine;
}

void cGraphicsEngine::Init()
{
	FONT_Init();

	// Set up rendering
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Sets up clipping
	glClearColor(0.0f, 0.1f, 0.3f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_Images.clear();
	m_RenderObjs.clear();
}

void cGraphicsEngine::Slot(cBackground * background, int actualLevel, bool draw, bool playerDraw,
	cDrawBossMsg* drawBoss, cDrawInitTextsMsg * initText,
	cDrawBossTextsMsg * bossText, cDrawFinalTextsMsg * finalText)
{
	// Render
	glClear(GL_COLOR_BUFFER_BIT);
	//En caso de que se indique un background específico (victoria/derrota) se renderiza este background
	if (background != nullptr) {
		background->Render();
	}

	//Si el nivel actual es válido (PLAYING)
	if (actualLevel != -1) {
		//Se renderizan los fondos de dicho nivel
		for (unsigned int i = 0; i < Level::GetLevels().at(actualLevel)->FindComponent<cLevelComp>()->GetBackgrounds().size(); i++) {
			Level::GetLevels().at(actualLevel)->FindComponent<cLevelComp>()->GetBackgrounds().at(i)->Render();
		}
	}

	//Renderiza los objetos
	RenderObjs();

	//En caso de que se permita dibujar las entidades e Interfaz(vida de jugador, enemigo y dialogos)
	if (draw) {
		//Renderiza el jugador
		if (Player::GetPlayer() != nullptr && playerDraw) {
			Player::GetPlayer()->FindComponent<cRenderComp>()->GetSprite()->Render();
		}
		//Renderiza el boss
		if (drawBoss != nullptr) {
			Level::GetLevels().at(actualLevel)->ReceiveMessage(*drawBoss);
		}
		//Renderiza los textos
		if (initText != nullptr) {
			Level::GetLevels().at(actualLevel)->ReceiveMessage(*initText);
		}
		else if (bossText != nullptr) {
			Level::GetLevels().at(actualLevel)->ReceiveMessage(*bossText);
		}
		else if (finalText != nullptr) {
			Level::GetLevels().at(actualLevel)->ReceiveMessage(*finalText);
		}
		//Renderiza la vida del player
		cInterfaceController::GetInstance().UpdatePlayerHealth();
	}
	//Sino no renderiza la vida del player
	else {
		cInterfaceController::GetInstance().UpdatePlayerHealth(false);
	}
	//Se actualiza la interfaz
	cInterfaceController::GetInstance().Slot();

	SYS_Show();
}

void cGraphicsEngine::Terminate()
{
	for (auto itImg = m_Images.begin(); itImg != m_Images.end(); ++itImg) {
		CORE_UnloadPNG(itImg->second.ImgId);
	}
	m_Images.clear();
	m_RenderObjs.clear();
	FONT_End();
}

GLuint cGraphicsEngine::InsertImg(const char *sFileName)
{
	// Control if prev. inserted.
	tImgInfo *pImgInfo = GetImgInfo(sFileName);
	if (pImgInfo != nullptr) {
		pImgInfo->iRefCount++;
		return pImgInfo->ImgId;
	}

	GLuint imgId = CORE_LoadPNG(sFileName, false);
	assert(imgId != 0);
	tImgInfo newImgInfo;
	newImgInfo.ImgId = imgId;
	newImgInfo.iRefCount = 1;
	m_Images[sFileName] = newImgInfo;
	return newImgInfo.ImgId;
}

void cGraphicsEngine::DeleteImg(const char *sFileName)
{
	tImgInfo *pImgInfo = GetImgInfo(sFileName);
	if (pImgInfo == nullptr) {
		return;
	}
	pImgInfo->iRefCount--;
	// Control no se usa img.
	if (pImgInfo->iRefCount == 0) {
		CORE_UnloadPNG(pImgInfo->ImgId);	// Eliminación de memoria.
		m_Images.erase(sFileName);
	}
}

cGraphicsEngine::tImgInfo *cGraphicsEngine::GetImgInfo(const char *sFileName)
{
	// Control if prev. inserted.
	auto result = m_Images.find(sFileName);
	if (result != m_Images.end()) {
		return &result->second;
	}
	return nullptr;
}

void cGraphicsEngine::InsertRenderObj(cRenderObject &renderObj)
{
	// Control if prev. inserted.
	for (const cRenderObject *pRenderObj : m_RenderObjs) {
		if (pRenderObj == &renderObj) {
			return;
		}
	}
	m_RenderObjs.push_back(&renderObj);
}

void cGraphicsEngine::DeleteRenderObj(cRenderObject &renderObj)
{
	for (auto it = m_RenderObjs.begin(); it != m_RenderObjs.end(); ++it) {
		if (*it == &renderObj) {
			m_RenderObjs.erase(it);
			break;
		}
	}
}

void cGraphicsEngine::DeleteAllRenderObj()
{
	int size = m_RenderObjs.size();
	for (int i = 0; i < size; i++) {
		DEL(m_RenderObjs[i]);
	}
	m_RenderObjs.clear();
}

void cGraphicsEngine::RenderObjs() const
{
	for (cRenderObject *pRenderObj : m_RenderObjs) {
		assert(pRenderObj != nullptr);
		pRenderObj->Render();
	}
}