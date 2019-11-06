
SCR_WIDTH = 1500
SCR_HEIGHT = 1000

--Level 1
enemylvl1 = {ENE_SPRITE = "data/bone.png", ENE_SIZE = { 16.0, 16.0 }, ENE_MAXSPEED = 650.0, ENE_MINSPEED = 450.0}

backgroundlvl1 = {BCK_SPRITE = "data/undertale.png", BCK_SIZE = { 600.0, 600.0 }, BCK_RESIZE = { 128.0, 128.0 }, BCK_RESIZEPOS = { 128.0,128.0 }, BCK_OFFSET = { 64.0, 64.0 }, BCK_MUSIC = "data/megalovania.wav"}

upgradelvl1 = {UPG_SPRITE = "data/three.png", UPG_SIZE = {32.0, 32.0}, UPG_TYPE = 0, UPG_AMOUNT = 3.0, UPG_DELAY = 2.0}

--Level1 (boss1)
enemy1boss1 = {ENE_BSS_SPRITE = "data/bone.png", ENE_BSS_SIZE = { 16.0, 16.0 }, ENE_BSS_MAXSPEED = 650.0, ENE_BSS_MINSPEED = 450.0, ENE_BSS_ROTATE = false, ENE_BSS_ERROR = 0.0}

boss1lvl1 = {BSS_POSS = {{ SCR_WIDTH / 2.0, 2.0*(SCR_HEIGHT / 3.0), 0.1 }}, BSS_FRAMES = 1, BSS_FRAMES_TIME = 0.0, BSS_RANDOM = false, BSS_SPRITE = "data/sans.png", BSS_SIZE = { 180.0, 180.0 }, BSS_ROUNDWAIT = 0.0, BSS_INITWAIT = 2.0, BSS_LIFES = 7000, BSS_RADIUS = 3000.0, BSS_ENEMY = enemy1boss1}

--Level1 (boss2)
enemy2boss1 = {ENE_BSS_SPRITE = "data/blaster.png", ENE_BSS_SIZE = { 2.3*SCR_WIDTH, 2.3*SCR_WIDTH }, ENE_BSS_MAXSPEED = 1650.0, ENE_BSS_MINSPEED = 450.0, ENE_BSS_ROTATE = true, ENE_BSS_ERROR = 150.0}

boss2lvl1 = {BSS_POSS = {{ SCR_WIDTH / 2.0, SCR_HEIGHT - 100.0, 2.0 }, { 100.0, SCR_HEIGHT - 100.0, 2.0 }, { SCR_WIDTH / 2.0, SCR_HEIGHT / 2.0, 2.0 }, { SCR_WIDTH - 100.0, SCR_HEIGHT - 100.0, 2.0 }}, BSS_FRAMES = 1, BSS_FRAMES_TIME = 0.0, BSS_RANDOM = true, BSS_SPRITE = "data/gaster.png", BSS_SIZE = { 120.0, 120.0 }, BSS_ROUNDWAIT = 2.5, BSS_INITWAIT = 0.0, BSS_LIFES = 10000, BSS_RADIUS = 1200.0, BSS_ENEMY = enemy2boss1}

--Level1
level1 = {LVL_INIT_TEXT = {"PULSA ESPACIO PARA CONTINUAR", "USA EL RATON PARA MOVERTE", "PULSA CLICK IZQUIERDO PARA DISPARAR", "ESQUIVA TODAS LAS ENTIDADES"}, LVL_BOSS_TEXT = {"HACE UN BONITO DIA FUERA", "LOS PAJAROS CANTAN, LAS FLORES FLORECEN", "EN DIAS COMO ESTOS, LAS PERSONAS COMO TU", "DEBERAN ARDER EN EL INFIERNO"}, LVL_END_TEXT = {"BIEN HECHO..."}, LVL_INITWAIT = 1.0, LVL_WAITTIME = 0.018, LVL_HORIZONTAL = true, LVL_ENEMYAMOUNT = 200, LVL_WIDTH = SCR_WIDTH, LVL_HEIGHT = SCR_HEIGHT, LVL_ENEMY = enemylvl1, LVL_BACKGROUND = {backgroundlvl1}, LVL_BOSSES = {boss1lvl1, boss2lvl1}, LVL_UPGRADES = {upgradelvl1}}

--Level 2
enemylvl2 = {ENE_SPRITE = "data/firesmall.png", ENE_SIZE = { 16.0, 16.0 }, ENE_MAXSPEED = 650.0, ENE_MINSPEED = 480.0}

backgroundlvl2 = {BCK_SPRITE = "data/circle-bkg-128.png", BCK_SIZE = { 128.0, 128.0 }, BCK_RESIZE = { 128.0, 128.0 }, BCK_RESIZEPOS = { 128.0,128.0 }, BCK_OFFSET = { 64.0, 64.0 }, BCK_MUSIC = "data/apo.wav"}

upgrade1lvl2 = {UPG_SPRITE = "data/three.png", UPG_SIZE = {32.0, 32.0}, UPG_TYPE = 0, UPG_AMOUNT = 3.0, UPG_DELAY = 2.0}

upgrade2lvl2 = {UPG_SPRITE = "data/updamage.png", UPG_SIZE = {32.0, 32.0}, UPG_TYPE = 1, UPG_AMOUNT = 3.0, UPG_DELAY = 2.0}

--Level2 (boss1)
enemy1boss2 = {ENE_BSS_SPRITE = "data/firesmall.png", ENE_BSS_SIZE = { 16.0, 16.0 }, ENE_BSS_MAXSPEED = 650.0, ENE_BSS_MINSPEED = 480.0, ENE_BSS_ROTATE = false, ENE_BSS_ERROR = 0.0}

boss1lvl2 = {BSS_POSS = {{ SCR_WIDTH / 2.0, SCR_HEIGHT - 100.0, 2.0 }, { 100.0, SCR_HEIGHT - 100.0, 4.0 }, { SCR_WIDTH / 2.0, SCR_HEIGHT / 2.0, 5.0 }, { SCR_WIDTH - 100.0, SCR_HEIGHT - 100.0, 4.0 }}, BSS_FRAMES = 1, BSS_FRAMES_TIME = 0.0, BSS_RANDOM = true, BSS_SPRITE = "data/reimu.png", BSS_SIZE = { 120.0, 120.0 }, BSS_ROUNDWAIT = 0.0, BSS_INITWAIT = 2.0, BSS_LIFES = 10000, BSS_RADIUS = 12000.0, BSS_ENEMY = enemy1boss2}

--Level2
level2 = {LVL_INIT_TEXT = {"MMMM, ESPERABAS ALGO MAS?", "BUENO, DIVIERTETE"}, LVL_BOSS_TEXT = {"MMMM, INTERESANTE...", "HAS SUPERADO MIS EXPECTATIVAS", "PODRAS AHORA CONMIGO?"}, LVL_END_TEXT = {"NOOOOOOO!"}, LVL_INITWAIT = 1.0, LVL_WAITTIME = 0.018, LVL_HORIZONTAL = false, LVL_ENEMYAMOUNT = 200, LVL_WIDTH = SCR_WIDTH, LVL_HEIGHT = SCR_HEIGHT, LVL_ENEMY = enemylvl2, LVL_BACKGROUND = {backgroundlvl2}, LVL_BOSSES = {boss1lvl2}, LVL_UPGRADES = {upgradelvl2}}

--Other Backgrounds
backgroundVictory = {BCK_SPRITE = "data/victoryicon.png", BCK_SIZE = { SCR_WIDTH, SCR_HEIGHT }, BCK_RESIZE = { SCR_WIDTH, 1.0 }, BCK_RESIZEPOS = { 1.0,1.0 }, BCK_OFFSET = { SCR_WIDTH/2.0, -SCR_HEIGHT/2.0 }, BCK_MUSIC = "data/megalovania.wav"}
backgroundDefeat = {BCK_SPRITE = "data/defeaticon.png", BCK_SIZE = { SCR_WIDTH, SCR_HEIGHT }, BCK_RESIZE = { SCR_WIDTH, 1.0 }, BCK_RESIZEPOS = { 1.0,1.0 }, BCK_OFFSET = { SCR_WIDTH/2.0, -SCR_HEIGHT/2.0 }, BCK_MUSIC = "data/dark.wav"}
backgroundMenu = {BCK_SPRITE = "data/box.png", BCK_SIZE = { 100.0, 100.0 }, BCK_RESIZE = { 100.0, 100.0 }, BCK_RESIZEPOS = { 100.0,100.0 }, BCK_OFFSET = { 60.0, 60.0 }, BCK_MUSIC = "data/badapple.wav"}

--Buttons
button1 = {BUTTON_SPRITE = "data/start-button.png", BUTTON_SIZE = {300.0, 100.0}, BUTTON_POS = { SCR_WIDTH / 2.0, SCR_HEIGHT / 2.0 }, BUTTON_FRAMES = 1, BUTTON_FRAMES_TIME = 0.0, BUTTON_SPEED = { 0.0, 0.0 }}

checkBox1 = {CHECKED_SPRITE = "data/three.png", UNCHECKED_SPRITE = "data/updamage.png", CHECKED_STATE = true, BUTTON_SIZE = {60.0, 60.0}, CHECKED_POS = { SCR_WIDTH / 2.0, SCR_HEIGHT / 2.0 + 200.0 }, BUTTON_FRAMES = 1, BUTTON_FRAMES_TIME = 0.0, BUTTON_SPEED = { 0.0, 0.0 }}

--Player
bullet = { BLL_SPRITE = "data/bullet2.png", BLL_SIZE = { 32.0, 24.0 }, BLL_SPEED = 1200.0, BLL_DAMAGE = 20, BLL_COOLDOWN = 0.1}

player = { PLY_SPRITE = "data/player.png", PLY_FRAMES = 8, PLY_FRAMES_TIME = 0.2, PLY_SIZE = {90.0, 90.0}, PLY_LIFES = 7, PLY_INV_TIME = 5.0, PLY_INV_TICKS = 0.2, PLY_BLANK_TIME = 0.05, PLY_COLL_RADIUS = 300.0, PLY_BULLET = bullet}

buttons = {button1}

checkBoxes = {checkBox1}

levels = {level1, level2}



world = { WRL_WIDTH = SCR_WIDTH, WRL_HEIGHT = SCR_HEIGHT, WRL_FULLSCREEN = 0, WRL_TEXTTIME = 1.0, WRL_LEVELS = levels, WRL_PLAYER = player, WRL_BUTTONS = buttons, WRL_CHECKBOXES = checkBoxes, WRL_VICTORY = backgroundVictory, WRL_DEFEAT = backgroundDefeat, WRL_MENU = backgroundMenu }