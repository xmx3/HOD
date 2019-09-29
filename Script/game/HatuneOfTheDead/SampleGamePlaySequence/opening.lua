--
-- Opening
--

-- タイトル画面実装
subclass("Opening", Actor) {
		__tostring = function(self)
			return("class Title name="..self.name) 
		end
}

-- コンストラクタ
function Opening:ctor(...)
	print("Opening:ctor() called")
	Opening.super.ctor(self, ...)
end

-- 初期化
function Opening:init(cfg)
	-- スーパークラス(Actor)のinitを呼ぶ
	print("Opening:init");
	Actor.init(self, cfg)
end

-- Actor削除時に実行される
function Opening:on_destroy()
	print("Opening:on_destroy()");
end


-- 状態関数

function Opening:state_start(rt)
	print("Opening:state_start");
	
	-- FixedCameraの設定
	local pos = D3DXVECTOR3:new_local( 200, 0, 0 )
	local lookAt = D3DXVECTOR3:new_local( 0, 0, 0 )
	local up = D3DXVECTOR3:new_local( 0, 1, 0 )
	self.camera = Camera.FixedCamera:new_local(
		pos,
		lookAt,
		up,
		45,-- fieldOFViewwInDegree
		0.1, --near
		30000) --far
		
	
	-- Modelのローディング
	-- ミク
	local xmlMiku = XmlLoader.XmlLoader.MME.Object.ModelKai:new_local()
	xmlMiku:loadStart("")
	while not xmlMiku:isReady() do
		ちょっち考えたい
		state:displayString("loading miku")
		self:wait(0)
	end
	self.miku = Lua.ModelRootTransformTimeLineControllerModel(
		xmlMiku:instance() )
	
	playerをどう作るか
	ModelTimeLineController切り替えをどうする
	基本考えていたことはカットシーンとゲームの切り替え
	新しく作る場合
	切り替える場合
	
	
	まずはplayer作成
	新規ゲームの場合
	カメラの仕様が決まっていないのでC++から固定カメラ
	カメラの変更みたいなことが必要かも
	
	
	
	ロードゲームの場合
	セーブの仕様を決めないとかけない
	仲間は後で出しいいや
	まだ考えないだいたいはなんとなく頭にあるからいい
	<Miku>
		<Status/>
		<SelectAble/>
	</Miku>
	
	
	--[[
	luaばんのtittle欲しい
	if(newgame)
		openingに進む
	]]
	
	
	
	local xmlCharacter = XmlLoader.GameObject.Utils.Character:new()
	xmlCharacter:loadStart("Data/XmlLoader/GameObject/Utils/Character/miku.xml")
	while not xmlCharacter:isReady do
		byouga
	end
	
	local pCharacter = xmlCharacter:instance()
	
	-- 初期ステータスの読み込みよりも自分で書いたほうがいいのでは
	local pStatus = GameObjectData.Status.create()
	local status = pStatus:get()
	status:str   = 100
	status:inte  = 100
	status:will  = 100
	status:dex   = 100
	status:qui   = 100
	status:vit   = 100
	status:psy   = 100
	status:luck  = 100
	
	status:maxHp = 10000
	status:maxMp = 100
	status:maxLp = 10
	status:Stamina = 100
	status:elementalDefs = 0
	status:mass  = 30
	status:speed = 50
	status:speedLow = 25
	status:speedHigh = 75
	status:angleSpeed = 0.78500003
	status:accel = 14
	status:usageStaminaPerSecSpeedHigh = 30
	status:usageStaminaPerSecSpeed  = 1
	status:usageStaminaPerSecSpeedLow = 1
	status:usageStaminaPerJump = 10
	status:healingStaminaPerSec = 15
	status:group = 0
	
	self.pPlayer = GameObject::create( pCharacter, pStatus )
	

	local model =Lua.TimeLineCotrollerModel( pCharacter )
	model.insert(
		0,--time
		0, 0, 0, --pos
		0, 0, 0, --rotate
		"stand" )
		
	model.

	
	
	-- 棒人間
	local xmlBou = XmlLoader.XmlLoader.MME.Object.ModelKai:new_local()
	xmlBou:loadStart("")
	while not xmlBou:isReady() do
		ちょっち考えたい
		state:displayString("loading 棒人間")
		self:wait(0)
	end
	

	-- ただの平面
	
	self.pStage = GameObject::Stage::create("Data/XmlLoader/GameObject/Stage/stage02.xml");
	
	-- MMEのローディング
	local gameDrawer = MME.Drawer.GameDrawer:instance();
	while not gameDrawer:isReady() do
		ちょっち考えたい
		state:displayString("loading MME")
		self:wait(0)
	end
	

	
	self.time = 0
	
	local state = Sequence.HatuneOfTheDead.LuaImpl.State:instance()
	
	state:setCameraAnimation(self.camera);
	-- state:setEnemy(mEnemy);
	state:setPlayer(self.player);
	state:setStage(self.stage);
	
	return "goto", "state_frame"
	
end

function Opening:state_frame(rt)
	local gameDrawer = MME.Drawer.GameDrawer:instance();
	local mme = MME.Manager:instance()
	local player = self.player:get()
	local fw = GameLib.Framework:instance();

	--固定フレームレート
	local elapsedTime=1.0/60.0;

	self.time = self.time+elapsedTime
	
	local black = GameLib.Math.Vector4:new_local(1.0)
	mme:setEdgeColor( black );

	
	local state = Sequence.HatuneOfTheDead.LuaImpl.State:instance()
	
	while true do
		state:update()
		if true then
			change_scene(Stage01)
		end
		
		state:draw()
		self:wait(0)
	end
	

	return "exit"
end

