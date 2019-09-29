--
-- Lobby
--

-- タイトル画面実装
subclass("Lobby", Actor) {
		__tostring = function(self)
			return("class Title name="..self.name) 
		end
}

-- コンストラクタ
function Lobby:ctor(...)
	print("Lobby:ctor() called")
	Lobby.super.ctor(self, ...)
end

-- 初期化
function Lobby:init(cfg)
	-- スーパークラス(Actor)のinitを呼ぶ
	print("Lobby:init");
	Actor.init(self, cfg)
end

-- Actor削除時に実行される
function Lobby:on_destroy()
	print("Lobby:on_destroy()");
end


-- 状態関数

function Lobby:state_start(rt)
	print("Lobby:state_start");
	
	-- リソースとインスタンス化したゲームオブジェクトはluaでは管理しない
	
	
	-- リソースの準備
	local resource = Sequence.HatuneOfTheDead.LuaImpl.Resource:instance()
	resource:loadCameraAnimation("Data/MMDData/vmd/camera_simple.vmd")
	resource:loadPlayer("Data/XmlLoader/GameObject/Player/miku.xml")
	resource:loadEnemy("Data/XmlLoader/GameObject/Enemy/bou.xml")
	resource:loadStage("Data/XmlLoader/GameObject/Stage/stage01.xml");
	--
	local gameDrawer = MME.Drawer.GameDrawer:instance();
	local isOk = resource:isReady() and
		gameDrawer:isReady()
	--	
	--
	while not isOk do
    isOk = 
      resource:isReady() and
		  gameDrawer:isReady()
		self:wait(0)
	end
	
	self.time = 0
	
	local state = Sequence.HatuneOfTheDead.LuaImpl.State:instance()
	state:build(resource)
	
	local init_transform = btTransform:new()
	init_transform:setIdentity()
	init_transform:getBasis():setEulerZYX(
		0,
		-3.14/2,
		0 );
	
	
	init_transform:getOrigin():setValue( -200, 55,-2 );
	-- init_transform:getOrigin():setValue( -80, 80,0);
	
	state:reserveEnemySpawn("棒人間", 0.1, init_transform )
	--
	-- init_transform:getOrigin():setValue( -220, 55,-2 );
	-- state:reserveEnemySpawn("棒人間", 2, init_transform )
	--
	-- init_transform:getOrigin():setValue( -180, 55,-2 );
	-- state:reserveEnemySpawn("棒人間", 2, init_transform )
	--
	-- init_transform:delete()
	--
	return "goto", "state_frame"
	
end


function Lobby:state_frame(rt)
	local gameDrawer = MME.Drawer.GameDrawer:instance();
	local mme = MME.Manager:instance()
	local state = Sequence.HatuneOfTheDead.LuaImpl.State:instance()
	local player = state:getPlayer()
	local fw = GameLib.Framework:instance();

	--固定フレームレート
	local elapsedTime=1.0/60.0;

	self.time = self.time+elapsedTime
	
	local black = GameLib.Math.Vector4:new_local(0.0)
	mme:setEdgeColor( black );
	
	
	local time = 0.0
	-- while time < 20 do
	while true do
		
		time = time+elapsedTime
		
		state:update()
		
		state:draw()
		self:wait(0)
	end
	
	
	
	
	-- 3秒後敵出現
	--その敵は画面外または10秒経過で削除
	-- if true then
	-- 	change_scene(Stage01)
	-- end
	--
	
	return "exit"
end

