--
-- Title
--

-- タイトル画面実装
subclass("Title", Actor) {
		__tostring = function(self)
			return("class Title name="..self.name) 
		end
}

-- コンストラクタ
function Title:ctor(...)
	print("Title:ctor() called")
	Title.super.ctor(self, ...)
end

-- 初期化
function Title:init(cfg)
	-- スーパークラス(Actor)のinitを呼ぶ
	print("Title:init");
	Actor.init(self, cfg)
	
	
	local fw = GameLib.Framework:instance();
	self.imageButton = GUI.ImageButton:new_local( 
		0, 0,
		fw:width(), fw:height() );
		
	self.logo_texture = GameLib.Graphics.Texture:create("Data/GUI/image/Title/logo.png");
	while not self.logo_texture:isReady() do
		-- self:wait(0)
	end
	--
	self.title_texture = GameLib.Graphics.Texture:create("Data/GUI/image/Title/title.png");
	while not self.title_texture:isReady() do
		-- self:wait(0)
	end
	

	self.imageButton:setTexture(self.logo_texture);
	GUI.Manager:instance():add(self.imageButton)
	
	
	
end

-- Actor削除時に実行される
function Title:on_destroy()
	print("Title:on_destroy()");
	GUI.Manager:destory()--静的クラス関数
	
	local state = Sequence.HatuneOfTheDead.LuaImpl.State:instance()
	state:setNeedDrawCall(false);
	-- self.label:delete()
end


-- 状態関数

function Title:state_start(rt)
	print("Title:state_start");
	while not GUI.Manager:instance():isReady() do
		self:wait(0)
	end
	
	local state = Sequence.HatuneOfTheDead.LuaImpl.State:instance()
	state:setNeedDrawCall(true);
	
	return "goto", "state_frame"
end

function Title:state_frame(rt)
	
	local state = Sequence.HatuneOfTheDead.LuaImpl.State:instance()
	local count=0;
	while not self.imageButton:isPushed() do
		self:wait(0)
		count = count+1;
		if count>=6000 then
			break;
		end
	end
	
	
	self:wait(0)
	self.imageButton:setTexture(self.title_texture);
	
	local fw = GameLib.Framework:instance();

	
	self.label = GUI.Label:new_local(
		fw:width()/3, fw:height()/5*4,--position
		200, 200,--size
		0x00000000 ) --backgroundcolor
	self.label:setFontColor(0xff333333)
	self.label:setText("click start!");
	GUI.Manager:instance():add(self.label)
	--
	-- local ok = GUI.OkDialog:new_local()
	-- ok:setText("click start!");
	-- ok:show()
	-- while not ok:isOk() do
	-- 	self:wait(0)
	-- end
	-- ok:hide()
	--
	local i=0;
	while not self.imageButton:isPushed() do
		i = i+1;
		if i%30==0 then
			self.label:setFontColor(0xffaaaaaa)
		else
			self.label:setFontColor(0xff333333)
		end
		self:wait(0)
	end
	
	change_scene(Stage)
	self:wait(0)--ないと下の行実行してon_destroy()が2度呼ばれる
	return "exit"
	
end

