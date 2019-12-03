--Anchura de la pantalla
SCR_WIDTH = 1500
--Altura de la pantalla
SCR_HEIGHT = 1000
--Activa el fullscreen (1) o no (0)
SCR_FULLSCREEN = 0

---------------------Level 1 (others)-------------------
--ENE_SPRITE: Sprite del enemigo
--ENE_SIZE: Tamaño del sprite del enemigo
--ENE_MAXSPEED: Máxima velocidad del enemigo
--ENE_MINSPEED: Mínima velocidad del enemigo
enemylvl1 = {ENE_SPRITE = "data/bone.png", ENE_SIZE = { 16.0, 16.0 }, ENE_MAXSPEED = 650.0, ENE_MINSPEED = 450.0}

--BCK_SPRITE: Sprite del background
--BCK_SIZE: Tamaño del sprite del background
--BCK_RESIZE: Reescalado según el tamaño del nivel
--BCK_RESIZEPOS: Posicion de inicio de colocación de los background
--BCK_OFFSET: Offset de posicionamiento del background
--BCK_MUSIC: Audio del background
backgroundlvl1 = {BCK_SPRITE = "data/undertale.png", BCK_SIZE = { 600.0, 600.0 }, BCK_RESIZE = { 128.0, 128.0 }, BCK_RESIZEPOS = { 128.0,128.0 }, BCK_OFFSET = { 64.0, 64.0 }, BCK_MUSIC = "data/megalovania.wav"}

--UPG_SPRITE: Sprite del Upgrade
--UPG_SIZE: Tamaño del sprite del Upgrade
--UPG_TYPE: Tipo del Upgrade (0 = BULLET_THREE; 1 = BULLET_DAMAGE_UP)
--UPG_AMOUNT: Cantidad de mejora
--UPG_DELAY: Delay de aparación del Upgrade
upgradelvl1 = {UPG_SPRITE = "data/three.png", UPG_SIZE = {32.0, 32.0}, UPG_TYPE = 0, UPG_AMOUNT = 3.0, UPG_DELAY = 2.0}

------------------Level1 (boss1)------------------
--ENE_BSS_SPRITE: Sprite del enemigo
--ENE_BSS_SIZE: Tamaño del sprite del enemigo
--ENE_BSS_MAXSPEED: Máxima velocidad del enemigo
--ENE_BSS_MINSPEED: Mínima velocidad del enemigo
--ENE_BSS_ROTATE: ¿Puede rotar?
--ENE_BSS_ERROR: Error máximo de la dirección del enemigo (la dirección perfecta es hacia el jugador)
enemy1boss1 = {ENE_BSS_SPRITE = "data/bone.png", ENE_BSS_SIZE = { 16.0, 16.0 }, ENE_BSS_MAXSPEED = 650.0, ENE_BSS_MINSPEED = 450.0, ENE_BSS_ROTATE = false, ENE_BSS_ERROR = 0.0}

--BSS_POSS: Posiciones disponibles del Boss (Separados por comas, la primera será siempre la posición inicial) (En caso de usar BSS_BEHAVIOUR es recomendable solamente indicar una posición (inicial))
--BSS_BEHAVIOUR: Lista de estados del boss (es un lista que contiene estados que es otra lista que contiene comportamientos que a su vez es otro lista que contiene un primer valor que es el comportamiento concreto y el resto son los parámetros de entrada (ver instrucciones del juego)), sino se quiere usar se puede dejar vacío.
--BSS_FRAMES: Número de frames (animación)
--BSS_FRAMES_TIME: Tiempo de espera entre frame y frame (animación)
--BSS_RANDOM: Selección aleatoria de posiciones (Solo funciona si hay varias BSS_POSS disponibles)
--BSS_SPRITE: Sprite del Boss
--BSS_SIZE: Tamaño del sprite del Boss
--BSS_ROUNDWAIT: Tiempo de espera entre disparo y disparo a menor tiempo mayor cantidad de disparos
--BSS_INITWAIT: Tiempo de espera inicial
--BSS_LIFES: Vidas totales del Boss
--BSS_RADIUS: Radio de colisión
--BSS_ENEMY: Tipo de enemigos (proyectiles) del boss
boss1lvl1 = {BSS_POSS = {{ SCR_WIDTH / 2.0, 2.0*(SCR_HEIGHT / 3.0), 0.1 }}, BSS_BEHAVIOUR = {{{"4"}, {"7", "5000"}}, {{"5"}}, {{"6","1"}, {"5"}}, {{"7", "3000"}}, {{"5"}}, {{"6","1"}, {"5"}}, {{"7", "2000"}}, {{"6","2"}, {"8"}, {"5"}, {"7", "0"}}}, BSS_FRAMES = 1, BSS_FRAMES_TIME = 0.0, BSS_RANDOM = false, BSS_SPRITE = "data/sans.png", BSS_SIZE = { 180.0, 180.0 }, BSS_ROUNDWAIT = 0.0, BSS_INITWAIT = 2.0, BSS_LIFES = 7000, BSS_RADIUS = 3000.0, BSS_ENEMY = enemy1boss1}

-------------------Level1 (boss2)-------------------
--ENE_BSS_SPRITE: Sprite del enemigo
--ENE_BSS_SIZE: Tamaño del sprite del enemigo
--ENE_BSS_MAXSPEED: Máxima velocidad del enemigo
--ENE_BSS_MINSPEED: Mínima velocidad del enemigo
--ENE_BSS_ROTATE: ¿Puede rotar?
--ENE_BSS_ERROR: Error máximo de la dirección del enemigo (la dirección perfecta es hacia el jugador)
enemy2boss1 = {ENE_BSS_SPRITE = "data/blaster.png", ENE_BSS_SIZE = { 2.3*SCR_WIDTH, 2.3*SCR_WIDTH }, ENE_BSS_MAXSPEED = 1650.0, ENE_BSS_MINSPEED = 450.0, ENE_BSS_ROTATE = true, ENE_BSS_ERROR = 150.0}

--BSS_POSS: Posiciones disponibles del Boss (Separados por comas, la primera será siempre la posición inicial) (En caso de usar BSS_BEHAVIOUR es recomendable solamente indicar una posición (inicial))
--BSS_BEHAVIOUR: Lista de comportamientos del boss (es un lista que contiene comportamientos que es otro lista que contiene estados que a su vez es otro lista que contiene un primer valor que es el estado concreto y el resto son los parámetros de entrada (ver instrucciones del juego)), sino se quiere usar se puede dejar vacío.
--BSS_FRAMES: Número de frames (animación)
--BSS_FRAMES_TIME: Tiempo de espera entre frame y frame (animación)
--BSS_RANDOM: Selección aleatoria de posiciones (Solo funciona si hay varias BSS_POSS disponibles)
--BSS_SPRITE: Sprite del Boss
--BSS_SIZE: Tamaño del sprite del Boss
--BSS_ROUNDWAIT: Tiempo de espera entre disparo y disparo a menor tiempo mayor cantidad de disparos
--BSS_INITWAIT: Tiempo de espera inicial
--BSS_LIFES: Vidas totales del Boss
--BSS_RADIUS: Radio de colisión
--BSS_ENEMY: Tipo de enemigos (proyectiles) del boss
boss2lvl1 = {BSS_POSS = {{ SCR_WIDTH / 2.0, SCR_HEIGHT - 100.0, 2.0 }, { 100.0, SCR_HEIGHT - 100.0, 2.0 }, { SCR_WIDTH / 2.0, SCR_HEIGHT / 2.0, 2.0 }, { SCR_WIDTH - 100.0, SCR_HEIGHT - 100.0, 2.0 }}, BSS_BEHAVIOUR = {}, BSS_FRAMES = 1, BSS_FRAMES_TIME = 0.0, BSS_RANDOM = true, BSS_SPRITE = "data/gaster.png", BSS_SIZE = { 120.0, 120.0 }, BSS_ROUNDWAIT = 2.5, BSS_INITWAIT = 0.0, BSS_LIFES = 10000, BSS_RADIUS = 1200.0, BSS_ENEMY = enemy2boss1}

----------------------Level1--------------------
--LVL_INIT_TEXT: Textos iniciales (Deben escribirse en mayúscula, sin tildes y separados por coma)
--LVL_BOSS_TEXT: Textos antes del boss (Deben escribirse en mayúscula, sin tildes y separados por coma)
--LVL_END_TEXT: Textos finales (Deben escribirse en mayúscula, sin tildes y separados por coma)
--LVL_INITWAIT: Tiempo de espera inicial del nivel 
--LVL_WAITTIME: Tiempo de espera entre ejecución del nivel y ejecución del nivel (Sirve para ajustar la dificultad junto con la velocidad)
--LVL_HORIZONTAL: ¿Es el nivel Horizontal?
--LVL_ENEMYAMOUNT: Cantidad de enemigos del nivel (no incluye los del/de los Boss/es ya que son los que salen antes del boss)
--LVL_WIDTH: Anchura del nivel
--LVL_HEIGHT: Altura del nivel
--LVL_ENEMY: Es el tipo de enemigo del nivel (antes del boss)
--LVL_BACKGROUND: Es un lista de backgrounds del nivel
--LVL_BOSSES: Es un lista de bosses del nivel 
--LVL_UPGRADES: Es un lista de upgrades del nivel
level1 = {LVL_INIT_TEXT = {"PULSA ESPACIO PARA CONTINUAR", "USA EL RATON PARA MOVERTE", "PULSA CLICK IZQUIERDO PARA DISPARAR", "ESQUIVA TODAS LAS ENTIDADES"}, LVL_BOSS_TEXT = {"HACE UN BONITO DIA FUERA", "LOS PAJAROS CANTAN, LAS FLORES FLORECEN", "EN DIAS COMO ESTOS, LAS PERSONAS COMO TU", "DEBERAN ARDER EN EL INFIERNO"}, LVL_END_TEXT = {"BIEN HECHO..."}, LVL_INITWAIT = 1.0, LVL_WAITTIME = 0.018, LVL_HORIZONTAL = true, LVL_ENEMYAMOUNT = 200, LVL_WIDTH = SCR_WIDTH, LVL_HEIGHT = SCR_HEIGHT, LVL_ENEMY = enemylvl1, LVL_BACKGROUND = {backgroundlvl1}, LVL_BOSSES = {boss1lvl1, boss2lvl1}, LVL_UPGRADES = {upgradelvl1}}

--------------------Level 2 (others)----------------------
--ENE_SPRITE: Sprite del enemigo
--ENE_SIZE: Tamaño del sprite del enemigo
--ENE_MAXSPEED: Máxima velocidad del enemigo
--ENE_MINSPEED: Mínima velocidad del enemigo
enemylvl2 = {ENE_SPRITE = "data/firesmall.png", ENE_SIZE = { 16.0, 16.0 }, ENE_MAXSPEED = 650.0, ENE_MINSPEED = 480.0}

--BCK_SPRITE: Sprite del background
--BCK_SIZE: Tamaño del sprite del background
--BCK_RESIZE: Reescalado según el tamaño del nivel
--BCK_RESIZEPOS: Posicion de inicio de colocación de los background
--BCK_OFFSET: Offset de posicionamiento del background
--BCK_MUSIC: Audio del background
backgroundlvl2 = {BCK_SPRITE = "data/circle-bkg-128.png", BCK_SIZE = { 128.0, 128.0 }, BCK_RESIZE = { 128.0, 128.0 }, BCK_RESIZEPOS = { 128.0,128.0 }, BCK_OFFSET = { 64.0, 64.0 }, BCK_MUSIC = "data/apo.wav"}

--UPG_SPRITE: Sprite del Upgrade
--UPG_SIZE: Tamaño del sprite del Upgrade
--UPG_TYPE: Tipo del Upgrade (0 = BULLET_THREE; 1 = BULLET_DAMAGE_UP)
--UPG_AMOUNT: Cantidad de mejora
--UPG_DELAY: Delay de aparación del Upgrade
upgradelvl2 = {UPG_SPRITE = "data/updamage.png", UPG_SIZE = {32.0, 32.0}, UPG_TYPE = 1, UPG_AMOUNT = 3.0, UPG_DELAY = 2.0}

-------------------Level2 (boss1)---------------------
--ENE_BSS_SPRITE: Sprite del enemigo
--ENE_BSS_SIZE: Tamaño del sprite del enemigo
--ENE_BSS_MAXSPEED: Máxima velocidad del enemigo
--ENE_BSS_MINSPEED: Mínima velocidad del enemigo
--ENE_BSS_ROTATE: ¿Puede rotar?
--ENE_BSS_ERROR: Error máximo de la dirección del enemigo (la dirección perfecta es hacia el jugador)
enemy1boss2 = {ENE_BSS_SPRITE = "data/firesmall.png", ENE_BSS_SIZE = { 16.0, 16.0 }, ENE_BSS_MAXSPEED = 650.0, ENE_BSS_MINSPEED = 480.0, ENE_BSS_ROTATE = false, ENE_BSS_ERROR = 0.0}

--BSS_POSS: Posiciones disponibles del Boss (Separados por comas, la primera será siempre la posición inicial) (En caso de usar BSS_BEHAVIOUR es recomendable solamente indicar una posición (inicial))
--BSS_BEHAVIOUR: Lista de comportamientos del boss (es un lista que contiene comportamientos que es otro lista que contiene estados que a su vez es otro lista que contiene un primer valor que es el estado concreto y el resto son los parámetros de entrada (ver instrucciones del juego)), sino se quiere usar se puede dejar vacío.
--BSS_FRAMES: Número de frames (animación)
--BSS_FRAMES_TIME: Tiempo de espera entre frame y frame (animación)
--BSS_RANDOM: Selección aleatoria de posiciones (Solo funciona si hay varias BSS_POSS disponibles)
--BSS_SPRITE: Sprite del Boss
--BSS_SIZE: Tamaño del sprite del Boss
--BSS_ROUNDWAIT: Tiempo de espera entre disparo y disparo a menor tiempo mayor cantidad de disparos
--BSS_INITWAIT: Tiempo de espera inicial
--BSS_LIFES: Vidas totales del Boss
--BSS_RADIUS: Radio de colisión
--BSS_ENEMY: Tipo de enemigos (proyectiles) del boss
boss1lvl2 = {BSS_POSS = {{ SCR_WIDTH / 2.0, SCR_HEIGHT - 100.0, 2.0 }, { 100.0, SCR_HEIGHT - 100.0, 4.0 }, { SCR_WIDTH / 2.0, SCR_HEIGHT / 2.0, 5.0 }, { SCR_WIDTH - 100.0, SCR_HEIGHT - 100.0, 4.0 }}, BSS_BEHAVIOUR = {}, BSS_FRAMES = 1, BSS_FRAMES_TIME = 0.0, BSS_RANDOM = true, BSS_SPRITE = "data/reimu.png", BSS_SIZE = { 120.0, 120.0 }, BSS_ROUNDWAIT = 0.0, BSS_INITWAIT = 2.0, BSS_LIFES = 10000, BSS_RADIUS = 12000.0, BSS_ENEMY = enemy1boss2}

----------------------Level2--------------------
--LVL_INIT_TEXT: Textos iniciales (Deben escribirse en mayúscula, sin tildes y separados por coma)
--LVL_BOSS_TEXT: Textos antes del boss (Deben escribirse en mayúscula, sin tildes y separados por coma)
--LVL_END_TEXT: Textos finales (Deben escribirse en mayúscula, sin tildes y separados por coma)
--LVL_INITWAIT: Tiempo de espera inicial del nivel 
--LVL_WAITTIME: Tiempo de espera entre ejecución del nivel y ejecución del nivel (Sirve para ajustar la dificultad junto con la velocidad)
--LVL_HORIZONTAL: ¿Es el nivel Horizontal?
--LVL_ENEMYAMOUNT: Cantidad de enemigos del nivel (no incluye los del/de los Boss/es ya que son los que salen antes del boss)
--LVL_WIDTH: Anchura del nivel
--LVL_HEIGHT: Altura del nivel
--LVL_ENEMY: Es el tipo de enemigo del nivel (antes del boss)
--LVL_BACKGROUND: Es un lista de backgrounds del nivel
--LVL_BOSSES: Es un lista de bosses del nivel 
--LVL_UPGRADES: Es un lista de upgrades del nivel
level2 = {LVL_INIT_TEXT = {"MMMM, ESPERABAS ALGO MAS?", "BUENO, DIVIERTETE"}, LVL_BOSS_TEXT = {"MMMM, INTERESANTE...", "HAS SUPERADO MIS EXPECTATIVAS", "PODRAS AHORA CONMIGO?"}, LVL_END_TEXT = {"NOOOOOOO!"}, LVL_INITWAIT = 1.0, LVL_WAITTIME = 0.018, LVL_HORIZONTAL = false, LVL_ENEMYAMOUNT = 200, LVL_WIDTH = SCR_WIDTH, LVL_HEIGHT = SCR_HEIGHT, LVL_ENEMY = enemylvl2, LVL_BACKGROUND = {backgroundlvl2}, LVL_BOSSES = {boss1lvl2}, LVL_UPGRADES = {upgradelvl1, upgradelvl2}}

-----------------Other Backgrounds------------------
--BCK_SPRITE: Sprite del background
--BCK_SIZE: Tamaño del sprite del background
--BCK_RESIZE: Reescalado según el tamaño del nivel
--BCK_RESIZEPOS: Posicion de inicio de colocación de los background
--BCK_OFFSET: Offset de posicionamiento del background
--BCK_MUSIC: Audio del background
backgroundVictory = {BCK_SPRITE = "data/victoryicon.png", BCK_SIZE = { SCR_WIDTH, SCR_HEIGHT }, BCK_RESIZE = { SCR_WIDTH, 1.0 }, BCK_RESIZEPOS = { 1.0,1.0 }, BCK_OFFSET = { SCR_WIDTH/2.0, -SCR_HEIGHT/2.0 }, BCK_MUSIC = "data/megalovania.wav"}

--BCK_SPRITE: Sprite del background
--BCK_SIZE: Tamaño del sprite del background
--BCK_RESIZE: Reescalado según el tamaño del nivel
--BCK_RESIZEPOS: Posicion de inicio de colocación de los background
--BCK_OFFSET: Offset de posicionamiento del background
--BCK_MUSIC: Audio del background
backgroundDefeat = {BCK_SPRITE = "data/defeaticon.png", BCK_SIZE = { SCR_WIDTH, SCR_HEIGHT }, BCK_RESIZE = { SCR_WIDTH, 1.0 }, BCK_RESIZEPOS = { 1.0,1.0 }, BCK_OFFSET = { SCR_WIDTH/2.0, -SCR_HEIGHT/2.0 }, BCK_MUSIC = "data/dark.wav"}

--BCK_SPRITE: Sprite del background
--BCK_SIZE: Tamaño del sprite del background
--BCK_RESIZE: Reescalado según el tamaño del nivel
--BCK_RESIZEPOS: Posicion de inicio de colocación de los background
--BCK_OFFSET: Offset de posicionamiento del background
--BCK_MUSIC: Audio del background
backgroundMenu = {BCK_SPRITE = "data/box.png", BCK_SIZE = { 100.0, 100.0 }, BCK_RESIZE = { 100.0, 100.0 }, BCK_RESIZEPOS = { 100.0,100.0 }, BCK_OFFSET = { 60.0, 60.0 }, BCK_MUSIC = "data/badapple.wav"}

-------------------Buttons-------------------
--BUTTON_SPRITE: Sprite del button
--BUTTON_SIZE: Tamaño del botón
--BUTTON_POS: Posición del botón
--BUTTON_FRAMES: Frames del botón
--BUTTON_FRAMES_TIME: Tiempo de frames del botón
--BUTTON_SPEED: Velocidad del botón
button1 = {BUTTON_SPRITE = "data/start-button.png", BUTTON_SIZE = {300.0, 100.0}, BUTTON_POS = { SCR_WIDTH / 2.0, SCR_HEIGHT / 2.0 }, BUTTON_FRAMES = 1, BUTTON_FRAMES_TIME = 0.0, BUTTON_SPEED = { 0.0, 0.0 }}

--CHECKED_SPRITE: Sprite de checked
--UNCHECKED_SPRITE: Sprite de unchecked
--CHECKED_STATE: ¿Está checked por defecto?
--BUTTON_POS: Posición del botón
--BUTTON_SIZE: Tamaño del botón
--BUTTON_FRAMES: Frames del botón
--BUTTON_FRAMES_TIME: Tiempo de frames del botón
--BUTTON_SPEED: Velocidad del botón
checkBox1 = {CHECKED_SPRITE = "data/three.png", UNCHECKED_SPRITE = "data/updamage.png", CHECKED_STATE = true, BUTTON_SIZE = {60.0, 60.0}, BUTTON_POS = { SCR_WIDTH / 2.0, SCR_HEIGHT / 2.0 + 200.0 }, BUTTON_FRAMES = 1, BUTTON_FRAMES_TIME = 0.0, BUTTON_SPEED = { 0.0, 0.0 }}

-------------------Bullet--------------------
--BLL_SPRITE: Sprite de la bala
--BLL_SIZE: Tamaño del sprite del jugador
--BLL_SPEED: Velocidad de la bala
--BLL_DAMAGE: Daño de la bala
--BLL_COOLDOWN: Cooldown de la bala
bullet = { BLL_SPRITE = "data/bullet2.png", BLL_SIZE = { 32.0, 24.0 }, BLL_SPEED = 1200.0, BLL_DAMAGE = 20, BLL_COOLDOWN = 0.3}

-------------------Player--------------------
--PLY_SPRITE: Sprite del jugador
--PLY_FRAMES: Número de frames del jugador (animación)
--PLY_FRAMES_TIME: Tiempo de espera entre frame y frame (animación)
--PLY_SIZE: Tamaño del sprite del jugador
--PLY_LIFES: Vidas del jugador
--PLY_INV_TIME: Tiempo de invulnerabilidad
--PLY_INV_TICKS: Tiempo que dura la visibilidad durante el tiempo de invulnerabilidad
--PLY_BLANK_TIME: Tiempo que dura la invisibilidad durante el tiempo de invulnerabilidad
--PLY_COLL_RADIUS: Radio de colisión
--PLY_BULLET: Bala del jugador
player = { PLY_SPRITE = "data/player.png", PLY_FRAMES = 8, PLY_FRAMES_TIME = 0.2, PLY_SIZE = {90.0, 90.0}, PLY_LIFES = 13, PLY_INV_TIME = 5.0, PLY_INV_TICKS = 0.2, PLY_BLANK_TIME = 0.05, PLY_COLL_RADIUS = 300.0, PLY_BULLET = bullet}

--Lista de botones (TODO: AÑADIR CADA BOTÓN NUEVO QUE SE AÑADA)
buttons = {button1}

--Lista de checkboxes (TODO: AÑADIR CADA CHECKBOX NUEVA QUE SE AÑADA)
checkBoxes = {checkBox1}

--Lista de niveles (TODO: AÑADIR CADA NIVEL NUEVO QUE SE AÑADA)
levels = {level1, level2}

--------------------World-------------------------
--WRL_WIDTH: Anchura del mundo (es recomendable que sea el mismo que SCR_WIDTH)
--WRL_HEIGHT: Altura del mundo (es recomendable que sea el mismo que SCR_HEIGHT)
--WRL_FULLSCREEN: Activa el fullscreen
--WRL_TEXTTIME: Tiempo de espera entre diálogos (para evitar spam de input)
--WRL_LEVELS: Lista de niveles del mundo
--WRL_PLAYER: Referencia al jugador 
--WRL_BUTTONS: Lista de botones
--WRL_CHECKBOXES: Lista de checkboxes
--WRL_VICTORY: Background de victoria
--WRL_DEFEAT: Background de derrota
--WRL_MENU: Background de menú
world = { WRL_WIDTH = SCR_WIDTH, WRL_HEIGHT = SCR_HEIGHT, WRL_FULLSCREEN = SCR_FULLSCREEN, WRL_TEXTTIME = 1.0, WRL_LEVELS = levels, WRL_PLAYER = player, WRL_BUTTONS = buttons, WRL_CHECKBOXES = checkBoxes, WRL_VICTORY = backgroundVictory, WRL_DEFEAT = backgroundDefeat, WRL_MENU = backgroundMenu }