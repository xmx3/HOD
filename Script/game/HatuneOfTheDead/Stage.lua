--
-- Lobby
--

-- タイトル画面実装
subclass("Stage", Actor) {
		__tostring = function(self)
			return("class Title name="..self.name) 
		end
}

-- コンストラクタ
function Stage:ctor(...)
	print("Stage:ctor() called")
	Stage.super.ctor(self, ...)
end

-- 初期化
function Stage:init(cfg)
	-- スーパークラス(Actor)のinitを呼ぶ
	print("Stage:init");
	Actor.init(self, cfg)
end

-- Actor削除時に実行される
function Stage:on_destroy()
	print("Stage:on_destroy()");
	local state = Sequence.HatuneOfTheDead.LuaImpl.State:instance()
	state:resetAll();
	GUI.Manager:destory()
	Telop.destroy();
end


-- 状態関数

function Stage:state_start(rt)
	print("Stage:state_start");
		
	-- 字幕の設定
	local telop = [[
@0, 200
同時にいっぱい倒してください
@200, 200
左クリック 指定位置に移動
@400, 200
右クリック 攻撃
@600, 200
連打すると強い攻撃が出るよ
@900, 200 : 0xffff0000
わあ！伏兵だ!
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
	resource:loadCameraAnimation("Data/MMDData/vmd/camera_simple.vmd")
	resource:loadPlayer("Data/XmlLoader/GameObject/Player/miku.xml")
	resource:loadEnemy("Data/XmlLoader/GameObject/Enemy/bou.xml")
	resource:loadStage("Data/XmlLoader/GameObject/Stage/stage01.xml");
	resource:loadEnemy("Data/XmlLoader/GameObject/Enemy/mikudayo.xml")
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
	
	
	--敵キャラクターの配置
	local init_transform = btTransform:new()
	init_transform:setIdentity()
	init_transform:getBasis():setEulerZYX(
		0,
		-3.14/2,
		0 );
	
	
	init_transform:getOrigin():setValue( -250, 55,-2 );
	state:reserveEnemySpawn("棒人間", 0.1, init_transform )
	
	init_transform:getOrigin():setValue( -300, 55,-2 );
	state:reserveEnemySpawn("棒人間", 0.1, init_transform )
	
	init_transform:getOrigin():setValue( -350, 55,-2 );
	state:reserveEnemySpawn("棒人間", 0.1, init_transform )
	
	init_transform:getOrigin():setValue( -400, 55,-2 );
	state:reserveEnemySpawn("棒人間", 0.1, init_transform )
	
	init_transform:setIdentity()
	init_transform:getBasis():setEulerZYX(
		0,
		-3.14/2.5,
		0 );
	
	init_transform:getOrigin():setValue( -250, 55, 40 );
	state:reserveEnemySpawn("棒人間", 0.1, init_transform )
	
	init_transform:getOrigin():setValue( -300, 55, 40 );
	state:reserveEnemySpawn("棒人間", 0.1, init_transform )
	
	init_transform:getOrigin():setValue( -350, 55, 40 );
	state:reserveEnemySpawn("棒人間", 0.1, init_transform )
	
	init_transform:setIdentity()
	init_transform:getBasis():setEulerZYX(
		0,
		-3.14/1.5,
		0 );
	
	init_transform:getOrigin():setValue( -250, 55, -40 );
	state:reserveEnemySpawn("棒人間", 0.1, init_transform )
	
	init_transform:getOrigin():setValue( -300, 55, -40 );
	state:reserveEnemySpawn("棒人間", 0.1, init_transform )
	
	init_transform:getOrigin():setValue( -350, 55, -40 );
	state:reserveEnemySpawn("棒人間", 0.1, init_transform )
	
	init_transform:getBasis():setEulerZYX(
		0,
		-3.14/2,
		0 );
	
	
	init_transform:getOrigin():setValue( -500, 55,-45 );
	state:reserveEnemySpawn("棒人間", 0.1, init_transform )
	
	init_transform:getOrigin():setValue( -500, 55,-30 );
	state:reserveEnemySpawn("棒人間", 0.1, init_transform )
	
	init_transform:getOrigin():setValue( -500, 55,-15 );
	state:reserveEnemySpawn("棒人間", 0.1, init_transform )
	
	init_transform:getOrigin():setValue( -500, 55, 0 );
	state:reserveEnemySpawn("棒人間", 0.1, init_transform )
	
	
	
	
	init_transform:getBasis():setEulerZYX(
		0,
		-3.14/2,
		0 );
	
		
	init_transform:getOrigin():setValue( -450, 55, -90 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -450, 55, -75 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -450, 55, -60 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -450, 55,-45 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -450, 55,-30 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -450, 55,-15 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -450, 55,-0 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -450, 55, 15 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -450, 55, 30 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -450, 55, 45 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	
	init_transform:getOrigin():setValue( -600, 55, -90 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -600, 55, -75 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -600, 55, -60 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -600, 55,-45 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -600, 55,-30 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -600, 55,-15 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -600, 55,-0 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -600, 55, 15 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -600, 55, 30 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -600, 55, 45 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	
	init_transform:getOrigin():setValue( -550, 55, -90 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -550, 55, -75 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -550, 55, -60 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -550, 55,-45 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -550, 55,-30 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -550, 55,-15 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -550, 55,-0 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -550, 55, 15 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -550, 55, 30 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -550, 55, 45 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
		init_transform:getOrigin():setValue( -500, 55, -90 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -500, 55, -75 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -500, 55, -60 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -500, 55,-45 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -500, 55,-30 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -500, 55,-15 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -500, 55,-0 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -500, 55, 15 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -500, 55, 30 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	init_transform:getOrigin():setValue( -500, 55, 45 );
	state:reserveEnemySpawn("ミクダヨー", 15, init_transform )
	
	
	
	init_transform:delete()
	


	if isOk then
		return "goto", "state_frame"
	else
		change_scene(Title)
		wait();
	end
	
	return "exit";
		
end


function Stage:state_frame(rt)
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
		-- 
		if state:getPlayerHp()<= 0 then
				local cfg={};
				cfg.txt = "Game Over!\n残念でした！\n";
				cfg.score = state:getScore()-2000;
				cfg.numKilled = state:getNumberKilledEnemy();
				cfg.playerHp = state:getPlayerHp()
				change_scene(Clear, cfg )
				self:wait(0)
		end
		
		self:wait(0)
	end
	
	
	local cfg={};
	cfg.txt = "Game Clear!\nおめでとうございます！\n";
	cfg.score = state:getScore();
	cfg.numKilled = state:getNumberKilledEnemy();
	cfg.playerHp = state:getPlayerHp()
	change_scene(Clear, cfg )
	
	
	-- 3秒後敵出現
	--その敵は画面外または10秒経過で削除
	-- if true then
	-- end
	--
	
	return "exit"
end

