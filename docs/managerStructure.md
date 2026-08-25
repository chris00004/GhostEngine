//managers
//tier-0
GameManager (GameMgr)
Debugger (DebugMgr)

//tier-1
InputManager (InputMgr)
AudioManager (AudioMgr)
DrawManager (DrawMgr)
MenuManager (MenuMgr)
LevelManager (LevelMgr)
DialogueManager (DialogueMgr)
AssetPakManager (PakMgr)
GameDataManager (GameDataMgr)

//managerDataStructs
Input input
Display display
Volume volume
Settings settings 
    -> holds: [display, volume]
GameData gameData 
    -> holds: [settings]

//-----------------------------------------------//

//--- [ GameManager ] -----------------------------------

Overview:
- owns all mgrs
- owns all mgrs data structs

Structure:
1. create all mgrs
2. create all mgrs data structs
3. on construction pass data structs as params to mgrs
4. on INIT:
    - call all mgrs' INIT funcs
    - set gameState to GAMELOOP
5. on GAMELOOP:
    - run all mgrs update()





















