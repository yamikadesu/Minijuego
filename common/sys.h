#ifndef _SYS_H_
#define _SYS_H_
/*Valores generales*/
//Anchura del mapa
 #define SCR_WIDTH  1500
 //Altura del mapa
 #define SCR_HEIGHT 1000
 //Activa el fullscreen (1) o no (0)
 #define SCR_FULLSCREEN 0
// //Tiempo de espera entre diálogos (para evitar spam de input)
// #define WRL_TEXTTIME 1.0f
// 
// /*Player*/
// //Sprite del jugador
// #define PLY_SPRITE "data/player.png"
// //Número de frames del jugador (animación)
// #define PLY_FRAMES 8
// //Tiempo de espera entre frame y frame (animación)
// #define PLY_FRAMES_TIME 0.2f
// //Tamaño del sprite del jugador
// #define PLY_SIZE {90.0f, 90.0f}
// //Vidas del jugador
// #define PLY_LIFES 7
// //Tiempo de invulnerabilidad
// #define PLY_INV_TIME 5.0f
// //Tiempo que dura la visibilidad durante el tiempo de invulnerabilidad
// #define PLY_INV_TICKS 0.2f
// //Tiempo que dura la invisibilidad durante el tiempo de invulnerabilidad
// #define PLY_BLANK_TIME 0.05f
// //Radio de colisión
// #define PLY_COLL_RADIUS 300.0f
// 
// /*Balas (Jugador)*/
// //Sprite de la bala
// #define BLL_SPRITE "data/bullet2.png"
// //Tamaño del sprite del jugador
// #define BLL_SIZE { 32.0f, 24.0f }
// //Velocidad de la bala
// #define BLL_SPEED 1200.0f
// //Daño de la bala
// #define BLL_DAMAGE 20
// //Cooldown de la bala
// #define BLL_COOLDOWN 0.1f
// 
// /*Nivel 1*/
// //Textos iniciales (Deben escribirse en mayúscula y separados por coma)
// #define LVL_1_INIT_TEXT "PULSA ESPACIO PARA CONTINUAR", "USA EL RATON PARA MOVERTE", "PULSA CLICK IZQUIERDO PARA DISPARAR", "ESQUIVA TODAS LAS ENTIDADES"
// // #define LVL_1_INIT_TEXT
// //Textos iniciales (Deben escribirse en mayúscula y separados por coma)
// #define LVL_1_BOSS_TEXT "HACE UN BONITO DIA FUERA", "LOS PAJAROS CANTAN, LAS FLORES FLORECEN", "EN DIAS COMO ESTOS, LAS PERSONAS COMO TU", "DEBERAN ARDER EN EL INFIERNO"
// //#define LVL_1_BOSS_TEXT
// //Textos iniciales (Deben escribirse en mayúscula y separados por coma)
// #define LVL_1_END_TEXT "BIEN HECHO..."
// // #define LVL_1_END_TEXT
// //Tiempo de espera inicial del nivel
// #define LVL_1_INITWAIT 1.0f
// //Tiempo de espera entre ejecución del nivel y ejecución del nivel(Sirve para ajustar la dificultad junto con la velocidad)
// #define LVL_1_WAITTIME 0.018f
// //¿Es el nivel Horizontal?
// #define LVL_1_HORIZONTAL true
// //Cantidad de enemigos del nivel (no incluye los del/de los Boss/es)
// #define LVL_1_ENEMYAMOUNT 200
// //Anchura del nivel
// #define LVL_1_WIDTH SCR_WIDTH
// //Altura del nivel
// #define LVL_1_HEIGHT SCR_HEIGHT
// 
// /*Enemigo (Nivel 1)*/
// //Sprite del enemigo
// #define ENE_LVL_1_SPRITE "data/bone.png"
// //Tamaño del sprite del enemigo
// #define ENE_LVL_1_SIZE { 16.0f, 16.0f }
// //Máxima velocidad del enemigo
// #define ENE_LVL_1_MAXSPEED 650.0f
// //Mínima velocidad del enemigo
// #define ENE_LVL_1_MINSPEED 450.0f
// 
// /*Background (Nivel 1)*/
// //Sprite del background
// #define BCK_1_LVL_1_SPRITE "data/undertale.png"
// //Tamaño del sprite del background
// #define BCK_1_LVL_1_SIZE { 600.0f, 600.0f }
// //Reescalado según el tamaño del nivel
// #define BCK_1_LVL_1_RESIZE { 128.0f, 128.0f }
// //Posicion de inicio de colocación de los background
// #define BCK_1_LVL_1_RESIZEPOS { 128.0f,128.0f }
// //Offset de posicionamiento del background
// #define BCK_1_LVL_1_OFFSET { 64.0f, 64.0f }
// //Audio del background
// #define BCK_1_LVL_1_MUSIC "data/megalovania.wav"
// 
// /*Boss 1 (Nivel 1)*/
// //Posiciones disponibles del Boss (Separados por comas, la primera será siempre la posición inicial)
// #define BSS_1_LVL_1_POSS { SCR_WIDTH / 2.0f, 2.0f*SCR_HEIGHT / 3.0f, 0.1f }
// //Número de frames (animación)
// #define BSS_1_LVL_1_FRAMES 1
// //Tiempo de espera entre frame y frame (animación)
// #define BSS_1_LVL_1_FRAMES_TIME 0.f
// //Selección aleatoria de posiciones 
// #define BSS_1_LVL_1_RANDOM false
// //Sprite del Boss
// #define BSS_1_LVL_1_SPRITE "data/sans.png"
// //Tamaño del sprite del Boss
// #define BSS_1_LVL_1_SIZE { 180.0f, 180.0f }
// //Tiempo de espera entre disparo y disparo a menor tiempo mayor cantidad de disparos
// #define BSS_1_LVL_1_ROUNDWAIT 0.0f
// //Tiempo de espera inicial
// #define BSS_1_LVL_1_INITWAIT 2.0f
// //Vidas totales del Boss
// #define BSS_1_LVL_1_LIFES 7000
// //Radio de colisión
// #define BSS_1_LVL_1_RADIUS 3000.0f
// 
// /*Enemigo (Boss 1 - Nivel 1)*/
// //Sprite del enemigo
// #define ENE_BSS_1_LVL_1_SPRITE "data/bone.png"
// //Tamaño del sprite del enemigo
// #define ENE_BSS_1_LVL_1_SIZE { 16.0f, 16.0f }
// //Máxima velocidad del enemigo
// #define ENE_BSS_1_LVL_1_MAXSPEED 650.0f
// //Mínima velocidad del enemigo
// #define ENE_BSS_1_LVL_1_MINSPEED 450.0f
// //¿Puede rotar?
// #define ENE_BSS_1_LVL_1_ROTATE false
// //Error máximo de la dirección del enemigo (la dirección perfecta es hacia el jugador)
// #define ENE_BSS_1_LVL_1_ERROR 0.0f
// 
// /*Boss 2 (Nivel 1)*/
// //Posiciones disponibles del Boss (Separados por comas, la primera será siempre la posición inicial)
// #define BSS_2_LVL_1_POSS { SCR_WIDTH / 2.0f, SCR_HEIGHT - 100.0f, 2.0f }, { 100.0f, SCR_HEIGHT - 100.0f, 2.0f }, { SCR_WIDTH / 2.0f, SCR_HEIGHT / 2.0f, 2.0f }, { SCR_WIDTH - 100.0f, SCR_HEIGHT - 100.0f, 2.0f }
// //Número de frames (animación)
// #define BSS_2_LVL_1_FRAMES 1
// //Tiempo de espera entre frame y frame (animación)
// #define BSS_2_LVL_1_FRAMES_TIME 0.f
// //Selección aleatoria de posiciones 
// #define BSS_2_LVL_1_RANDOM true
// //Sprite del Boss
// #define BSS_2_LVL_1_SPRITE "data/gaster.png"
// //Tamaño del sprite del Boss
// #define BSS_2_LVL_1_SIZE { 120.0f, 120.0f }
// //Tiempo de espera entre disparo y disparo a menor tiempo mayor cantidad de disparos
// #define BSS_2_LVL_1_ROUNDWAIT 2.5f
// //Tiempo de espera inicial
// #define BSS_2_LVL_1_INITWAIT 0.0f
// //Vidas totales del Boss
// #define BSS_2_LVL_1_LIFES 10000
// //Radio de colisión
// #define BSS_2_LVL_1_RADIUS 1200.0f
// 
// /*Enemigo (Boss 2 - Nivel 1)*/
// //Sprite del enemigo
// #define ENE_BSS_2_LVL_1_SPRITE "data/blaster.png"
// //Tamaño del sprite del enemigo
// #define ENE_BSS_2_LVL_1_SIZE { 2.3f*SCR_WIDTH, 2.3f*SCR_WIDTH }
// //Máxima velocidad del enemigo
// #define ENE_BSS_2_LVL_1_MAXSPEED 1650.0f
// //Mínima velocidad del enemigo
// #define ENE_BSS_2_LVL_1_MINSPEED 450.0f
// //¿Puede rotar?
// #define ENE_BSS_2_LVL_1_ROTATE true
// //Error máximo de la dirección del enemigo (la dirección perfecta es hacia el jugador)
// #define ENE_BSS_2_LVL_1_ERROR 150.0f
// 
// /*Upgrade (Nivel 1)*/
// //Sprite del Upgrade
// #define UPG_1_LVL_1_SPRITE "data/three.png"
// //Tamaño del sprite del Upgrade
// #define UPG_1_LVL_1_SIZE {32.0f, 32.0f}
// //Tipo del Upgrade
// #define UPG_1_LVL_1_TYPE BULLET_THREE
// //Cantidad de mejora
// #define UPG_1_LVL_1_AMOUNT 3.0f
// //Delay de aparación del Upgrade
// #define UPG_1_LVL_1_DELAY 2.0f
// 
// /*Nivel 2*/
// //Textos iniciales (Deben escribirse en mayúscula y separados por coma)
// #define LVL_2_INIT_TEXT "MMMM, ESPERABAS ALGO MAS?", "BUENO, DIVIERTETE"
// // #define LVL_2_INIT_TEXT
// //Textos iniciales (Deben escribirse en mayúscula y separados por coma)
// #define LVL_2_BOSS_TEXT "MMMM INTERESANTE...", "HAS SUPERADO MIS EXPECTATIVAS", "PODRAS AHORA CONMIGO?"
// // #define LVL_2_BOSS_TEXT 
// //Textos iniciales (Deben escribirse en mayúscula y separados por coma)
// #define LVL_2_END_TEXT "NOOOOOOO!"
// // #define LVL_2_END_TEXT
// //Tiempo de espera inicial del nivel
// #define LVL_2_INITWAIT 1.0f
// //Tiempo de espera entre ejecución del nivel y ejecución del nivel(Sirve para ajustar la dificultad junto con la velocidad)
// #define LVL_2_WAITTIME 0.018f
// //¿Es el nivel Horizontal?
// #define LVL_2_HORIZONTAL false
// //Cantidad de enemigos del nivel (no incluye los del/de los Boss/es)
// #define LVL_2_ENEMYAMOUNT 200
// //Anchura del nivel
// #define LVL_2_WIDTH SCR_WIDTH
// //Altura del nivel
// #define LVL_2_HEIGHT SCR_HEIGHT
// 
// /*Enemigo (Nivel 2)*/
// //Sprite del enemigo
// #define ENE_LVL_2_SPRITE "data/firesmall.png"
// //Tamaño del sprite del enemigo
// #define ENE_LVL_2_SIZE { 16.0f, 16.0f }
// //Máxima velocidad del enemigo
// #define ENE_LVL_2_MAXSPEED 650.0f
// //Mínima velocidad del enemigo
// #define ENE_LVL_2_MINSPEED 480.0f
// 
// /*Background (Nivel 2)*/
// //Sprite del background
// #define BCK_1_LVL_2_SPRITE "data/circle-bkg-128.png"
// //Tamaño del sprite del background
// #define BCK_1_LVL_2_SIZE { 128.0f, 128.0f }
// //Reescalado según el tamaño del nivel
// #define BCK_1_LVL_2_RESIZE { 128.0f, 128.0f }
// //Posicion de inicio de colocación de los background
// #define BCK_1_LVL_2_RESIZEPOS { 128.0f,128.0f }
// //Offset de posicionamiento del background
// #define BCK_1_LVL_2_OFFSET { 64.0f, 64.0f }
// //Audio del background
// #define BCK_1_LVL_2_MUSIC "data/apo.wav"
// 
// /*Boss (Nivel 2)*/
// //Posiciones disponibles del Boss (Separados por comas, la primera será siempre la posición inicial)
// #define BSS_1_LVL_2_POSS { SCR_WIDTH / 2.0f, SCR_HEIGHT - 100.0f, 2.0f }, { 100.0f, SCR_HEIGHT - 100.0f, 4.0f }, { SCR_WIDTH / 2.0f, SCR_HEIGHT / 2.0f, 5.0f }, { SCR_WIDTH - 100.0f, SCR_HEIGHT - 100.0f, 4.0f }
// //Número de frames (animación)
// #define BSS_1_LVL_2_FRAMES 1
// //Tiempo de espera entre frame y frame (animación)
// #define BSS_1_LVL_2_FRAMES_TIME 0.f
// //Selección aleatoria de posiciones 
// #define BSS_1_LVL_2_RANDOM true
// //Sprite del Boss
// #define BSS_1_LVL_2_SPRITE "data/reimu.png"
// //Tamaño del sprite del Boss
// #define BSS_1_LVL_2_SIZE { 120.0f, 120.0f }
// //Tiempo de espera entre disparo y disparo a menor tiempo mayor cantidad de disparos
// #define BSS_1_LVL_2_ROUNDWAIT 0.0f
// //Tiempo de espera inicial
// #define BSS_1_LVL_2_INITWAIT 2.0f
// //Vidas totales del Boss
// #define BSS_1_LVL_2_LIFES 10000
// //Radio de colisión
// #define BSS_1_LVL_2_RADIUS 12000.0f
// 
// /*Enemigo (Boss - Nivel 2)*/
// //Sprite del enemigo
// #define ENE_BSS_1_LVL_2_SPRITE "data/firesmall.png"
// //Tamaño del sprite del enemigo
// #define ENE_BSS_1_LVL_2_SIZE { 16.0f, 16.0f }
// //Máxima velocidad del enemigo
// #define ENE_BSS_1_LVL_2_MAXSPEED 650.0f
// //Mínima velocidad del enemigo
// #define ENE_BSS_1_LVL_2_MINSPEED 480.0f
// //¿Puede rotar?
// #define ENE_BSS_1_LVL_2_ROTATE false
// //Error máximo de la dirección del enemigo (la dirección perfecta es hacia el jugador)
// #define ENE_BSS_1_LVL_2_ERROR 0.0f
// 
// /*Upgrade 1 (Nivel 2)*/
// //Sprite del Upgrade
// #define UPG_1_LVL_2_SPRITE "data/three.png"
// //Tamaño del sprite del Upgrade
// #define UPG_1_LVL_2_SIZE {32.0f, 32.0f}
// //Tipo del Upgrade
// #define UPG_1_LVL_2_TYPE BULLET_THREE
// //Cantidad de mejora
// #define UPG_1_LVL_2_AMOUNT 3.0f
// //Delay de aparación del Upgrade
// #define UPG_1_LVL_2_DELAY 2.0f
// 
// /*Upgrade 2 (Nivel 2)*/
// //Sprite del Upgrade
// #define UPG_2_LVL_2_SPRITE "data/updamage.png"
// //Tamaño del sprite del Upgrade
// #define UPG_2_LVL_2_SIZE {32.0f, 32.0f}
// //Tipo del Upgrade
// #define UPG_2_LVL_2_TYPE BULLET_DAMAGE_UP
// //Cantidad de mejora
// #define UPG_2_LVL_2_AMOUNT 3.0f
// //Delay de aparación del Upgrade
// #define UPG_2_LVL_2_DELAY 2.0f
// 
// /*Victory Background*/
// //Sprite del background
// #define BCK_VCT_SPRITE "data/victoryicon.png"
// //Tamaño del sprite del background
// #define BCK_VCT_SIZE { (float)SCR_WIDTH, (float)SCR_HEIGHT }
// //Reescalado según el tamaño del nivel
// #define BCK_VCT_RESIZE { (float)SCR_WIDTH, 1.0f }
// //Posicion de inicio de colocación de los background
// #define BCK_VCT_RESIZEPOS { 1.0f,1.0f }
// //Offset de posicionamiento del background
// #define BCK_VCT_OFFSET { (float)width/2.0f, -(float)height/2.0f }
// //Audio del background
// #define BCK_VCT_MUSIC "data/megalovania.wav"
// 
// /*Defeat Background*/
// //Sprite del background
// #define BCK_DFT_SPRITE "data/defeaticon.png"
// //Tamaño del sprite del background
// #define BCK_DFT_SIZE { (float)SCR_WIDTH, (float)SCR_HEIGHT }
// //Reescalado según el tamaño del nivel
// #define BCK_DFT_RESIZE { (float)SCR_WIDTH, 1.0f }
// //Posicion de inicio de colocación de los background
// #define BCK_DFT_RESIZEPOS { 1.0f,1.0f }
// //Offset de posicionamiento del background
// #define BCK_DFT_OFFSET { (float)width/2.0f, -(float)height/2.0f }
// //Audio del background
// #define BCK_DFT_MUSIC "data/dark.wav"
// 
// /*Menu Background*/
// //Sprite del background
// #define BCK_MENU_SPRITE "data/box.png"
// //Tamaño del sprite del background
// #define BCK_MENU_SIZE {100.f, 100.f}
// //Reescalado según el tamaño del nivel
// #define BCK_MENU_RESIZE { 100.f, 100.f }
// //Posicion de inicio de colocación de los background
// #define BCK_MENU_RESIZEPOS { 100.f, 100.f }
// //Offset de posicionamiento del background
// #define BCK_MENU_OFFSET { 60.f, 60.f }
// //Audio del background
// #define BCK_MENU_MUSIC "data/badapple.wav"
// 
// /*Play Button*/
// //Sprite del button
// #define BUTTON_SPRITE "data/start-button.png"
// //Tamaño del botón
// #define BUTTON_SIZE {300.f, 100.f}
// //Posición del botón
// #define BUTTON_POS { (float)SCR_WIDTH / 2.0f, (float)SCR_HEIGHT / 2.0f }
// //Frames del botón
// #define BUTTON_FRAMES 1
// //Tiempo de frames del botón
// #define BUTTON_FRAMES_TIME 0.f
// //Velocidad del botón
// #define BUTTON_SPEED { 0.0f, 0.0f }
// 
// 
// /*CheckBox*/
// //Sprite de checked
// #define CHECKED_SPRITE "data/three.png"
// //Sprite de unchecked
// #define UNCHECKED_SPRITE "data/updamage.png"
// //Is checked by default?
// #define CHECKED_STATE true
// //Posición del botón
// #define CHECKED_POS { (float)SCR_WIDTH / 2.0f, (float)SCR_HEIGHT / 2.0f +200.f}
// //Tamaño del botón
// #define CHECKED_SIZE { 60.f, 60.f }
// //Frames del botón
// #define CHECKED_FRAMES 1
// //Tiempo de frames del botón
// #define CHECKED_FRAMES_TIME 0.f
// //Velocidad del botón
// #define CHECKED_SPEED { 0.0f, 0.0f }


//#############################################################################
#ifdef _WIN32
/*Teclas*/
#define SYS_KEY_UP    VK_UP
#define SYS_KEY_DOWN  VK_DOWN
#define SYS_KEY_LEFT  VK_LEFT
#define SYS_KEY_RIGHT VK_RIGHT
#define SYS_KEY_SPACE 0x20

#define SYS_MB_LEFT   VK_LBUTTON
#define SYS_MB_RIGHT  VK_RBUTTON
#define SYS_MB_MIDDLE VK_MBUTTON

//#############################################################################
#elif defined(__APPLE__)
#include "TargetConditionals.h"
#if defined(__MACH__) && TARGET_OS_MAC && !TARGET_OS_IPHONE
//#############################################################################

#define SYS_KEY_UP    GLFW_KEY_UP
#define SYS_KEY_DOWN  GLFW_KEY_DOWN
#define SYS_KEY_LEFT  GLFW_KEY_LEFT
#define SYS_KEY_RIGHT GLFW_KEY_RIGHT
#define SYS_KEY_SPACE GLFW_KEY_SPACE

#define SYS_MB_LEFT   GLFW_MOUSE_BUTTON_LEFT
#define SYS_MB_RIGHT  GLFW_MOUSE_BUTTON_RIGHT
#define SYS_MB_MIDDLE GLFW_MOUSE_BUTTON_MIDDLE

#endif
#endif


void  SYS_Pump      ();
void  SYS_Show      ();
bool  SYS_GottaQuit ();
void  SYS_Sleep     (int ms);

struct ivec2 { int x, y; };

bool  SYS_KeyPressed       (int key);
ivec2 SYS_MousePos         ();
bool  SYS_MouseButonPressed(int button);


#endif
