--
-- Stage01
--

-- タイトル画面実装
subclass("Stage01", Actor) {
		__tostring = function(self)
			return("class Title name="..self.name) 
		end
}

-- コンストラクタ
function Stage01:ctor(...)
	print("Stage01:ctor() called")
	Stage01.super.ctor(self, ...)
end

-- 初期化
function Stage01:init(cfg)
	-- スーパークラス(Actor)のinitを呼ぶ
	print("Stage01:init");
	Actor.init(self, cfg)
end

-- Actor削除時に実行される
function Stage01:on_destroy()
	print("Stage01:on_destroy()");
	self.player:removeFromWorld()
end


-- 状態関数

function Stage01:state_start(rt)
	print("Stage01:state_start");
	
	self.camera = std.shared_ptr_MMD__CameraAnimation_:new_local()
	self.camera:reset( MMD.CameraAnimation:new() )
	local camera = self.camera:get()
	camera:load("Data/MMDData/vmd/camera_simple.vmd")
	
	local xmlPlayer = XmlLoader.GameObject.Player:new_local()
	xmlPlayer:loadXml("Data/XmlLoader/GameObject/Player/miku.xml")

	self.xmlEnemy = XmlLoader.GameObject.Enemy:new_local()
	self.xmlEnemy:loadXml("Data/XmlLoader/GameObject/Enemy/bou.xml")

	self.stage = GameObject.Stage:create("Data/XmlLoader/GameObject/Stage/stage01.xml");
	-- //mStage = GameObject::Stage::create("Data/XmlLoader/GameObject/Stage/stage02.xml");
	
	local gameDrawer = MME.Drawer.GameDrawer:instance();
	local isOk = 
		camera:isReady() and
		xmlPlayer:isReady() and
		self.xmlEnemy:isReady() and
		self.stage:get():isReady() and
		gameDrawer:isReady()
		
	
	while not isOk do
		isOk = 
		camera:isReady() and
		xmlPlayer:isReady() and
		self.xmlEnemy:isReady() and
		self.stage:get():isReady() and
		gameDrawer:isReady()
		
		self:wait(0)
	end
	

	
	self.player = xmlPlayer:instance()
	self.time = 0
	
	local state = Sequence.HatuneOfTheDead.LuaImpl.State:instance()
	
	state:setCameraAnimation(self.camera);
	-- state:setEnemy(mEnemy);
	state:setPlayer(self.player);
	state:setStage(self.stage);
	
	return "goto", "state_frame"
	
end

function Stage01:state_frame(rt)
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
		
		state:draw()
		self:wait(0)
	end
	

	return "exit"
end

