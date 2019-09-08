#pragma once
#include "entity.h"
#include "../../../../common/core.h"
#include <functional>


class Button : public cEntity {
protected:
	vec2 m_size;
	std::function<void(Button *, void *)> m_callback;
public:
	Button() : m_size({ 0,0 }) {};
	Button(vec2 size) : m_size(size) {};

	vec2 GetSize() const { return m_size; }
	void SetSize(vec2 val) { m_size = val; }
	std::function<void(Button *, void *)> GetCallback() const { return m_callback; }
	void SetCallback(std::function<void(Button *, void *)> val) { m_callback = val; }
	virtual void onClick(void* data, vec2 pos);
	virtual void onClick(void* data){ m_callback(this, data); };
};