#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "../../../../common/core.h"
#include "render_object.h"
#include <string>

//Información de datos de un sprite (para generar un sprite)
struct SpriteData {
	std::string loc;
	vec2 size;
	float angle = 0.0f;
	rgba_t rgba = { 255, 255, 255, 255 };
};

class cSprite : public cRenderObject
{
private:
	//Posición del sprite 
	vec2 m_vPos;
	//Tamaño del sprite
	vec2 m_vSize;
	//Id del sprite (OpenGL)
	GLuint m_uImgId;
	//Ubicación del archivo
	std::string m_sFileName;
	//Variable que indica si se renderiza o no (se usa principalmente en el parpadeo de invulnerabilidad del player)
	bool m_notRender;
	//Ángulo de rotación del sprite
	float m_angle;
	//Color de renderizado del sprite
	rgba_t m_rgba;
	//UVs para la animación (x = u0 = coordenada x inferior izquierda ; y = v0 = coordenada x inferior derecha; z = u1 = coordenada x superior izquierda; t = v1 = coordenada x superior derecha)
	vec4 m_uv;
public:
	cSprite(std::string sFileName, const vec2 &vSize, const float angle = 0.0f, const rgba_t &rgba = {255, 255, 255, 255});
	~cSprite();
	inline void SetPos(const vec2 &vPos) { m_vPos = vPos; };
	inline const vec2 &GetPos() const { return m_vPos; };
	inline void SetSize(const vec2 &vSize) { m_vSize = vSize; };
	inline const vec2 &GetSize() const { return m_vSize; };
	inline void SetAngle(const float angle) { m_angle = angle; };
	inline const float &GetAngle() const { return m_angle; };
	inline void SetRGBA(const rgba_t &rgba) { m_rgba = rgba; };
	inline const rgba_t &GetRGBA() const { return m_rgba; };
	inline void SetUV(const vec4 &uv) { m_uv = uv; };
	inline const vec4 &GetUV() const { return m_uv; };
	inline std::string GetFileName() const { return m_sFileName; };
	inline void SetId(const GLuint &uv) { m_uImgId = uv; };
	inline const GLuint &GetId() const { return m_uImgId; };

	virtual void Render() override;
	void SetNotRender(bool notRender);
	bool GetNotRender();
};

#endif // !_SPRITE_H_
