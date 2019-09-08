#include "CheckBox.h"
#include "../Managers/world.h"
#include "../Managers/graphics_engine.h"
#include "../../../../common/leaks.h"

CheckBox::~CheckBox()
{
}

void CheckBox::Update(float fTimeDiff)
{
	m_auxTime += fTimeDiff;
}

void CheckBox::onClick(void* data)
{
	cRenderComp* rendComp = FindComponent<cRenderComp>();
	if (rendComp) {
		if (m_checked && m_auxTime >= m_maxTime) {
			GLuint id = cGraphicsEngine::GetInstance().GetImgInfo(m_unCheckedImage)->ImgId;
			rendComp->GetSprite()->SetId(id);
			m_checked = false;
			m_auxTime = 0.f;
		}
		else if(m_auxTime >= m_maxTime){
			GLuint id = cGraphicsEngine::GetInstance().GetImgInfo(m_checkedImage)->ImgId;
			rendComp->GetSprite()->SetId(id);
			m_checked = true;
			m_auxTime = 0.f;
		}
	}
	m_callback(this, data);
}
