--
-- Lobby
--

-- タイトル画面実装
subclass("GameEngineIntroduction", Actor) {
		__tostring = function(self)
			return("class Title name="..self.name) 
		end
}

-- コンストラクタ
function GameEngineIntroduction:ctor(...)
	print("GameEngineIntroduction:ctor() called")
	GameEngineIntroduction.super.ctor(self, ...)
end

-- 初期化
function GameEngineIntroduction:init(cfg)
	-- スーパークラス(Actor)のinitを呼ぶ
	print("GameEngineIntroduction:init");
	Actor.init(self, cfg)
end

-- Actor削除時に実行される
function GameEngineIntroduction:on_destroy()
	print("GameEngineIntroduction:on_destroy()");
	local state = Sequence.HatuneOfTheDead.LuaImpl.State:instance();
	state:resetAll();
	GUI.Manager:destory();
	Telop.destroy();
	
end


-- 状態関数

function GameEngineIntroduction:state_start(rt)
	print("GameEngineIntroduction:state_start");
	
		--字幕の設定
-- 	local telop = [[
-- @0, 200
-- 簡単なGameEngineの説明をしたいと思います
-- @200, 200
-- このGameEngineの特徴は
-- @400, 200 : 0xffff0000
-- MMDとMME、Luaを組み込んだこととです
-- @600, 200
-- luaを使うことでビルドなしで変更できます
-- @800, 200
-- ではやってみます
-- ]];

-- 	local telop = [[
-- @0, 200
-- 敵の配置,数を変えました
-- @200, 200
-- ついでにモデルも変えました
-- ]];
--
	local telop = [[
@0, 200
一度読み込めばロードが必要ない設計にしています
@200, 200
Luaでリソースを削除すれば
@400, 200
再ロードされます
]];




	local isOk = Telop.parse( telop, #telop);
	Telop.setTime(0.0);
	
	if isOk then
		print("Telop ok!\n")
	else
		print("Telop NG!\n")
		change_scene(Title)
		wait();
	end
	
	
	
	-- リソースとインスタンス化したゲームオブジェクトはluaでは管理しない
	
	
	-- リソースの準備
	local resource = Sequence.HatuneOfTheDead.LuaImpl.Resource:instance()
	
	--スクリプトを読み込むたびに再ロードしたければ下2行をコメントアウト
	-- resource:release();
	-- resource = Sequence.HatuneOfTheDead.LuaImpl.Resource:instance()
	
	
	resource:loadCameraAnimation("Data/MMDData/vmd/camera_simple.vmd")
	-- resource:loadPlayer("Data/XmlLoader/GameObject/Player/miku.xml")
	resource:loadPlayer("Data/XmlLoader/GameObject/Player/rin.xml")
	-- resource:loadPlayer("Data/XmlLoader/GameObject/Player/miku_lat.xml")
	resource:loadEnemy("Data/XmlLoader/GameObject/Enemy/bou.xml")
	resource:loadEnemy("Data/XmlLoader/GameObject/Enemy/mikudayo.xml")
	resource:loadStage("Data/XmlLoader/GameObject/Stage/stage01.xml");
	--
	local gameDrawer = MME.Drawer.GameDrawer:instance();
	
	isOk = resource:isReady() and gameDrawer:isReady()
	
	
	while not isOk do
    isOk = 
      resource:isReady() and
		  gameDrawer:isReady()
		self:wait(0)
	end
	
	self.time = 0
	
	local state = Sequence.HatuneOfTheDead.LuaImpl.State:instance()
	state:build(resource)
	
	--敵キャラクターの配置
	local init_transform = btTransform:new()
	init_transform:setIdentity()
	init_transform:getBasis():setEulerZYX(
		0,
		-3.14/2,
		0 );
	
	
	-- 縦に3体
	-- init_transform:getOrigin():setValue( -250, 55,-2 );
	-- state:reserveEnemySpawn("棒人間", 0.1, init_transform )
	--
	-- init_transform:getOrigin():setValue( -300, 55,-2 );
	-- state:reserveEnemySpawn("棒人間", 0.1, init_transform )
	--
	-- init_transform:getOrigin():setValue( -350, 55,-2 );
	-- state:reserveEnemySpawn("棒人間", 0.1, init_transform )
	--
	
	-- 上横に6体
	init_transform:getOrigin():setValue( -350, 55,-2 );
	state:reserveEnemySpawn("ミクダヨー", 0.1, init_transform )
	
	init_transform:getOrigin():setValue( -350, 80,-2 );
	state:reserveEnemySpawn("ミクダヨー", 0.1, init_transform )
	
	init_transform:getOrigin():setValue( -350, 100,-2 );
	state:reserveEnemySpawn("ミクダヨー", 0.1, init_transform )
	
	init_transform:getOrigin():setValue( -350, 55,-20 );
	state:reserveEnemySpawn("ミクダヨー", 0.1, init_transform )
	
			init_transform:getOrigin():setValue( -350, 55,-2 );
	state:reserveEnemySpawn("ミクダヨー", 0.1, init_transform )
	
	init_transform:getOrigin():setValue( -350, 55, 20 );
	state:reserveEnemySpawn("ミクダヨー", 0.1, init_transform )
	
	
	

	init_transform:delete()
	
	

	return "goto", "state_frame"
		
end


function GameEngineIntroduction:state_frame(rt)
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
	while time < 30 do
		
		time = time+elapsedTime
		
		state:update()
		
		state:draw()
		
		Telop.draw( 1 );--//フレーム単位
		self:wait(0)
	end
	
	
	
	change_scene(GameEngineIntroduction)
	
	
	return "exit"
end

