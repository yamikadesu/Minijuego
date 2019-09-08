/*
LiteGfx
Public domain graphics library based on OpenGL
It is intended to be used as a graphics library for simple applications
that do not require shaders or any modern graphics techniques
(it uses the fixed pipeline)
Should work on ancient GPUs
Created by Javier San Juan Cervera
No warranty implied. Use as you wish and at your own risk
*/

#ifndef LITE_GFX_H
#define LITE_GFX_H

#ifdef __cplusplus
extern "C" {
#endif

	/* main */

	typedef enum {
		BLEND_SOLID,
		BLEND_ALPHA,
		BLEND_ADD,
		BLEND_MUL
	} lblend_t;

	void lgfx_setup2d(int width, int height);
	void lgfx_setup3d(int width, int height);
	void lgfx_setviewport(int x, int y, int width, int height);
	void lgfx_setorigin(float x, float y);
	void lgfx_setresolution(int width, int height);
	void lgfx_setprojection(const float* m);
	void lgfx_setmodelview(const float* m);
	void lgfx_setblend(lblend_t mode);
	void lgfx_setcolor(float r, float g, float b, float a);
	void lgfx_setusevertexcolor(int enable);
	void lgfx_setculling(int enable);
	void lgfx_setdepthwrite(int enable);
	void lgfx_setlighting(int enable, int numlights);
	void lgfx_setlight(int num, float x, float y, float z, float w, float r, float g, float b, float att);
	void lgfx_setambient(float r, float g, float b);
	void lgfx_setfog(int enable, float r, float g, float b, float start, float end);
	void lgfx_clearcolorbuffer(float r, float g, float b);
	void lgfx_cleardepthbuffer();
	void lgfx_drawpoint(float x, float y);
	void lgfx_drawline(float x0, float y0, float x1, float y1);
	void lgfx_drawrect(float x, float y, float width, float height);
	void lgfx_drawoval(float x, float y, float width, float height);

	/* texture */

	typedef struct {
		int glid;
		int width;
		int height;
	} ltex_t;

	ltex_t* ltex_alloc(int width, int height, int filtering);
	void ltex_free(ltex_t* tex);
	void ltex_setpixels(const ltex_t* tex, const unsigned char* pixels);
	void ltex_getpixels(const ltex_t* tex, unsigned char* out_pixels);
	void ltex_draw(const ltex_t* tex, float x, float y);
	void ltex_drawrot(const ltex_t* tex, float x, float y, float angle, float pivotx, float pivoty);
	void ltex_drawrotsized(const ltex_t* tex, float x, float y, float angle, float pivotx, float pivoty, float width, float height, float u0, float v0, float u1, float v1);
	void ltex_bindcolor(const ltex_t* tex);

	/* vertex */

	typedef enum {
		MODE_POINTS,
		MODE_LINES,
		MODE_TRIANGLES,
		MODE_TRIANGLE_STRIP,
		MODE_TRIANGLE_FAN
	} lrendermode_t;

	typedef struct {
		float pos[3];
		float nor[3];
		float tex[2];
		float tex2[2];
		float col[4];
	} lvert_t;

	lvert_t lvert(float x, float y, float z, float nx, float ny, float nz, float u, float v, float r, float g, float b, float a);
	void lvert_draw(const lvert_t* vertices, unsigned int count, lrendermode_t mode);
	void lvert_drawindexed(const lvert_t* vertices, const unsigned short* indices, unsigned int count, lrendermode_t mode);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LITE_GFX_H */




  /* IMPLEMENTATION */




#ifdef LITE_GFX_IMPLEMENTATION

  /* include opengl */
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#include <GL/gl.h>
#endif

#include <math.h>
#include <stdlib.h>
#include <string.h>

#define OVALPOINTS 64

#ifdef __cplusplus
extern "C" {
#endif

	/* setup */

	inline void lgfx_setup2d(int width, int height) {
		glDisable(GL_ALPHA_TEST);
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_SCISSOR_TEST);
		glEnable(GL_TEXTURE_2D);
		glEnableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		lgfx_setviewport(0, 0, width, height);
		lgfx_setorigin(0, 0);
		lgfx_setresolution(width, height);
		lgfx_setblend(BLEND_SOLID);
		lgfx_setcolor(1, 1, 1, 1);
		lgfx_setusevertexcolor(0);
		lgfx_setculling(0);
		lgfx_setlighting(0, 0);
		lgfx_setfog(0, 0, 0, 0, 0, 0);
		ltex_bindcolor(0);
	}

	inline void lgfx_setup3d(int width, int height) {
		glEnable(GL_ALPHA_TEST);
		glEnable(GL_BLEND);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_SCISSOR_TEST);
		glEnable(GL_TEXTURE_2D);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glAlphaFunc(GL_GEQUAL, 0.0001f);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		glDepthFunc(GL_LEQUAL);
		glFogi(GL_FOG_MODE, GL_LINEAR);
		glFrontFace(GL_CW);
		lgfx_setviewport(0, 0, width, height);
		lgfx_setorigin(0, 0);
		lgfx_setresolution(width, height);
		lgfx_setblend(BLEND_SOLID);
		lgfx_setcolor(1, 1, 1, 1);
		lgfx_setusevertexcolor(0);
		lgfx_setculling(1);
		lgfx_setdepthwrite(1);
		lgfx_setlighting(0, 0);
		lgfx_setfog(0, 0, 0, 0, 0, 0);
		ltex_bindcolor(0);
	}

	inline void lgfx_setviewport(int x, int y, int width, int height) {
		glViewport(x, y, width, height);
		glScissor(x, y, width, height);
		lgfx_setresolution(width, height);
	}

	inline void lgfx_setorigin(float x, float y) {
		glLoadIdentity();
		glTranslatef(-x, -y, 0);
	}

	inline void lgfx_setresolution(int width, int height) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, width, height, 0, 0, 1000);
		glMatrixMode(GL_MODELVIEW);
	}

	inline void lgfx_setprojection(const float* m) {
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(m);
		glMatrixMode(GL_MODELVIEW);
	}

	inline void lgfx_setmodelview(const float* m) {
		glLoadMatrixf(m);
	}

	inline void lgfx_setblend(lblend_t mode) {
		switch (mode) {
		case BLEND_SOLID:
			glBlendFunc(GL_ONE, GL_ZERO);
			break;
		case BLEND_ALPHA:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			break;
		case BLEND_ADD:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			break;
		case BLEND_MUL:
			glBlendFunc(GL_DST_COLOR, GL_ZERO);
			break;
		}
	}

	inline void lgfx_setcolor(float r, float g, float b, float a) {
		glColor4f(r, g, b, a);
	}

	inline void lgfx_setusevertexcolor(int enable) {
		if (enable) {
			glEnableClientState(GL_COLOR_ARRAY);
		}
		else {
			glDisableClientState(GL_COLOR_ARRAY);
		}
	}

	inline void lgfx_setculling(int enable) {
		if (enable) {
			glEnable(GL_CULL_FACE);
		}
		else {
			glDisable(GL_CULL_FACE);
		}
	}

	inline void lgfx_setdepthwrite(int enable) {
		glDepthMask(enable);
	}

	inline void lgfx_setlighting(int enable, int numlights) {
		if (enable) glEnable(GL_LIGHTING); else glDisable(GL_LIGHTING);
		for (int i = 0; i < numlights; ++i) glEnable(GL_LIGHT0 + i);
		for (int i = numlights; i < 8; ++i) glDisable(GL_LIGHT0 + i);
	}

	inline void lgfx_setlight(int num, float x, float y, float z, float w, float r, float g, float b, float att) {
		float pos[] = { x, y, z, w };
		float col[] = { r, g, b };
		glLightfv(GL_LIGHT0 + num, GL_POSITION, pos);
		glLightfv(GL_LIGHT0 + num, GL_DIFFUSE, col);
		glLightf(GL_LIGHT0 + num, GL_LINEAR_ATTENUATION, att);
	}

	inline void lgfx_setambient(float r, float g, float b) {
		float ambient[] = { r, g, b, 1 };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	}

	inline void lgfx_setfog(int enable, float r, float g, float b, float start, float end) {
		float color[] = { r, g, b, 1 };
		if (enable) {
			glEnable(GL_FOG);
		}
		else {
			glDisable(GL_FOG);
		}
		glFogfv(GL_FOG_COLOR, color);
		glFogf(GL_FOG_START, start);
		glFogf(GL_FOG_END, end);
	}

	inline void lgfx_clearcolorbuffer(float r, float g, float b) {
		glClearColor(r, g, b, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	inline void lgfx_cleardepthbuffer() {
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	inline void lgfx_drawpoint(float x, float y) {
		lvert_t vert = lvert(x, y, 0, 0, 0, -1, 0, 0, 1, 1, 1, 1);
		ltex_bindcolor(0);
		lvert_draw(&vert, 1, MODE_POINTS);
	}

	inline void lgfx_drawline(float x0, float y0, float x1, float y1) {
		lvert_t verts[2];
		verts[0] = lvert(x0, y0, 0, 0, 0, -1, 0, 0, 1, 1, 1, 1);
		verts[1] = lvert(x1, y1, 0, 0, 0, -1, 0, 0, 1, 1, 1, 1);
		ltex_bindcolor(0);
		lvert_draw(verts, 2, MODE_LINES);
	}

	inline void lgfx_drawrect(float x, float y, float width, float height) {
		lvert_t verts[4];
		verts[0] = lvert(x, y, 0, 0, 0, -1, 0, 0, 1, 1, 1, 1);
		verts[1] = lvert(x + width, y, 0, 0, 0, -1, 0, 0, 1, 1, 1, 1);
		verts[2] = lvert(x, y + height, 0, 0, 0, -1, 0, 0, 1, 1, 1, 1);
		verts[3] = lvert(x + width, y + height, 0, 0, 0, -1, 0, 0, 1, 1, 1, 1);
		ltex_bindcolor(0);
		lvert_draw(verts, 4, MODE_TRIANGLE_STRIP);
	}

	inline void lgfx_drawoval(float x, float y, float width, float height) {
		lvert_t verts[OVALPOINTS];
		float centerx = x + width * 0.5f;
		float centery = y + height * 0.5f;
		float inc = 6.28318530718f / OVALPOINTS;
		float halfwidth = width * 0.5f;
		float halfheight = height * 0.5f;
		for (int i = 0; i < OVALPOINTS; ++i) {
			verts[i] = lvert(centerx + ((float)cos(i * inc) * halfwidth), centery + ((float)sin(i * inc) * halfheight), 0, 0, 0, -1, 0, 0, 1, 1, 1, 1);
		}
		ltex_bindcolor(0);
		lvert_draw(verts, OVALPOINTS, MODE_TRIANGLE_FAN);
	}

	/* texture */

	inline ltex_t* ltex_alloc(int width, int height, int filtering) {
		GLuint gltex;
		ltex_t* tex;

		/* generate opengl texture */
		glGenTextures(1, &gltex);
		glBindTexture(GL_TEXTURE_2D, gltex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering ? GL_LINEAR : GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering ? GL_LINEAR : GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, 0);

		/* generate tex object */
		tex = (ltex_t*)malloc(sizeof(ltex_t));
		tex->glid = (int)gltex;
		tex->width = width;
		tex->height = height;

		return tex;
	}

	inline void ltex_free(ltex_t* tex) {
		if (tex && tex->glid != 0) glDeleteTextures(1, (const GLuint*)&tex->glid);
		free(tex);
	}

	inline void ltex_setpixels(const ltex_t* tex, const unsigned char* pixels) {
		glBindTexture(GL_TEXTURE_2D, (GLuint)tex->glid);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->width, tex->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	inline void ltex_getpixels(const ltex_t* tex, unsigned char* out_pixels) {
		glBindTexture(GL_TEXTURE_2D, (GLuint)tex->glid);
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, out_pixels);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	inline void ltex_draw(const ltex_t* tex, float x, float y) {
		ltex_drawrot(tex, x, y, 0, 0, 0);
	}

	inline void ltex_drawrot(const ltex_t* tex, float x, float y, float angle, float pivotx, float pivoty) {
		ltex_drawrotsized(tex, x, y, angle, pivotx, pivoty, (float)tex->width, (float)tex->height, 0, 0, 1, 1);
	}

	inline void ltex_drawrotsized(const ltex_t* tex, float x, float y, float angle, float pivotx, float pivoty, float width, float height, float u0, float v0, float u1, float v1) {
		lvert_t verts[4];
		verts[0] = lvert(-pivotx, -pivoty, 0, 0, 0, -1, u0, v0, 1, 1, 1, 1);
		verts[1] = lvert(1 - pivotx, -pivoty, 0, 0, 0, -1, u1, v0, 1, 1, 1, 1);
		verts[2] = lvert(-pivotx, 1 - pivoty, 0, 0, 0, -1, u0, v1, 1, 1, 1, 1);
		verts[3] = lvert(1 - pivotx, 1 - pivoty, 0, 0, 0, -1, u1, v1, 1, 1, 1, 1);
		glPushMatrix();
		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, -1);
		glScalef(width, height, 1);
		ltex_bindcolor(tex);
		lvert_draw(verts, 4, MODE_TRIANGLE_STRIP);
		glPopMatrix();
	}

	inline void ltex_bindcolor(const ltex_t* tex) {
		glBindTexture(GL_TEXTURE_2D, tex ? (GLuint)tex->glid : 0);
	}

	/* vertex */

	inline static GLenum _lgfx_pickglrendermode(lrendermode_t mode) {
		switch (mode) {
		case MODE_POINTS:
			return GL_POINTS;
		case MODE_LINES:
			return GL_LINES;
		case MODE_TRIANGLES:
			return GL_TRIANGLES;
		case MODE_TRIANGLE_STRIP:
			return GL_TRIANGLE_STRIP;
		case MODE_TRIANGLE_FAN:
			return GL_TRIANGLE_FAN;
		default:
			return GL_TRIANGLES;
		}
	}

	inline lvert_t lvert(float x, float y, float z, float nx, float ny, float nz, float u, float v, float r, float g, float b, float a) {
		lvert_t vert;
		vert.pos[0] = x;
		vert.pos[1] = y;
		vert.pos[2] = z;
		vert.nor[0] = nx;
		vert.nor[1] = ny;
		vert.nor[2] = nz;
		vert.tex[0] = u;
		vert.tex[1] = v;
		vert.tex2[0] = u;
		vert.tex2[1] = v;
		vert.col[0] = r;
		vert.col[1] = g;
		vert.col[2] = b;
		vert.col[3] = a;
		return vert;
	}

	inline void lvert_draw(const lvert_t* vertices, unsigned int count, lrendermode_t mode) {
		glVertexPointer(3, GL_FLOAT, sizeof(lvert_t), &vertices->pos[0]);
		glNormalPointer(GL_FLOAT, sizeof(lvert_t), &vertices->nor[0]);
		glTexCoordPointer(2, GL_FLOAT, sizeof(lvert_t), &vertices->tex[0]);
		glColorPointer(4, GL_FLOAT, sizeof(lvert_t), &vertices->col[0]);
		glDrawArrays(_lgfx_pickglrendermode(mode), 0, count);
	}

	inline void lvert_drawindexed(const lvert_t* vertices, const unsigned short* indices, unsigned int count, lrendermode_t mode) {
		glVertexPointer(3, GL_FLOAT, sizeof(lvert_t), &vertices->pos[0]);
		glNormalPointer(GL_FLOAT, sizeof(lvert_t), &vertices->nor[0]);
		glTexCoordPointer(2, GL_FLOAT, sizeof(lvert_t), &vertices->tex[0]);
		glColorPointer(4, GL_FLOAT, sizeof(lvert_t), &vertices->col[0]);
		glDrawElements(_lgfx_pickglrendermode(mode), count, GL_UNSIGNED_SHORT, indices);
	}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LITE_GFX_IMPLEMENTATION */
