#pragma once
#include "entity.h"
#include "../../../../common/core.h"
#include "Button.h"
#include "../Graphics/sprite.h"



class CheckBox : public Button {
protected:
	bool m_checked;
	std::string m_checkedImage;
	std::string m_unCheckedImage;
	float m_auxTime;
	float m_maxTime;
public:
	CheckBox(vec2 size, std::string checkedImage, std::string unCheckedImage, bool checked) {
		m_size = size;
		m_checkedImage = checkedImage;
		m_unCheckedImage = unCheckedImage;
		m_checked = checked;
		m_auxTime = 0.f;
		m_maxTime = 0.3f;
	};
	~CheckBox();
	std::string  GetCheckedImage() const { return m_checkedImage; }
	std::string  GeUnCheckedImage() const { return m_unCheckedImage; }
	bool GetChecked() const { return m_checked; }
	void GetChecked(bool val) { m_checked = val; }
	virtual void Update(float fTimeDiff) override;
	virtual void onClick(void* data) override;
};