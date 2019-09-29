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
	self.label = GUI.Label:new_local(0,0,200,200)
	GUI.Manager:instance():add(self.label)
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
	
	self.label:setText("3")
	self:wait(60)
	
	print("2")
	self.label:setText("2")
	self:wait(60)
	
	print("1")
	self.label:setText("1")
	self:wait(60)
	
	print("0")
	-- self.label:setIsEnable(false)
	self.label:setFontColor(0xffff0000)
	local ok = GUI.OkDialog:new_local()
	ok:show()
	while not ok:isOk() do
		self:wait(0)
	end
	ok:hide()
	
	self.label:setText("go")
	self:wait(60)
	
	
	change_scene(Lobby)
	self:wait(0)--ないと下の行実行してon_destroy()が2度呼ばれる
	return "exit"
	
end

