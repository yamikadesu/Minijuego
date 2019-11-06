#include "../../../../common/stdafx.h"
#include "sprite.h"
#include "../Managers/graphics_engine.h"
#include <string.h>
#include <assert.h>

cSprite::cSprite(std::string sFileName, const vec2 &vSize, const float angle, const rgba_t &rgba) : m_vPos({ 0,0 })
	, m_vSize(vSize), m_notRender(false), m_angle(angle), m_rgba(rgba), m_uv({ 0.f, 1.f,0.f,1.f })
{
// 	errno_t err = strcpy_s(m_sFileName, _countof(m_sFileName), sFileName.c_str());
// 	assert(err == 0);
	m_sFileName = sFileName;
	m_uImgId = cGraphicsEngine::GetInstance().InsertImg(sFileName);	// Get id from repository to render.
}

cSprite::~cSprite()
{
	cGraphicsEngine::GetInstance().DeleteImg(m_sFileName);	// Delete image.
}

void cSprite::Render()
{
	if (!m_notRender) {
		CORE_RenderCenteredRotatedSprite(m_vPos, m_vSize, m_angle, m_uImgId, m_rgba, m_uv.x, m_uv.y, m_uv.z, m_uv.t);
	}
}

void cSprite::SetNotRender(bool notRender) {
	this->m_notRender = notRender;
}

bool cSprite::GetNotRender() {
	return m_notRender;
}
