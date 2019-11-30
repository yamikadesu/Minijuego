#ifndef _GRAPHICS_ENGINE_H_
#define _GRAPHICS_ENGINE_H_

#include <map>
#include "../Entities/Messages/render_msg.h"
#include "../Graphics/background.h"
#include "../../../../common/core.h"

using namespace std;

class cRenderObject;

class cGraphicsEngine
{
public:
	struct tImgInfo {
		//Id de la Imagen
		GLuint	ImgId;
		//Referencia del contador para eliminar la imagen si no es usada
		unsigned int	iRefCount;
		tImgInfo() : ImgId(0), iRefCount(0)
		{}
	};
	static cGraphicsEngine& GetInstance();	// Singleton.
	cGraphicsEngine(cGraphicsEngine const&) = delete;
	void operator = (cGraphicsEngine const&) = delete;

	void Init();
	void Slot(cBackground* background = nullptr, int actualLevel = -1, bool draw = false,
		bool playerDraw = false, cDrawBossMsg* drawBoss = nullptr,
		cDrawInitTextsMsg* initText = nullptr, cDrawBossTextsMsg* bossText = nullptr,
		cDrawFinalTextsMsg* finalText = nullptr);
	void Terminate();

	//Inserta una imagen en el repositorio de imagenes
	GLuint InsertImg(string sFileName);
	//Elimina una imagen
	void DeleteImg(string sFileName);
	//Lo mismo pero para objetos renderizables
	void InsertRenderObj(cRenderObject &renderObj);
	void DeleteRenderObj(cRenderObject &renderObj);
	void DeleteRenderObj(string sprite);
	void DeleteAllRenderObj();
	//Obtiene la información de la imagen, devuelve 0 en caso de error
	cGraphicsEngine::tImgInfo *GetImgInfo(string sFileName);
private:
	//Conjunto de imágenes
	std::map<std::string, tImgInfo> m_Images;
	//Conjunto de objetos renderizables
	std::vector<cRenderObject *>	m_RenderObjs;

private:
	cGraphicsEngine() {};

	void RenderObjs();
};

#endif // !_GRAPHICS_ENGINE_H_

