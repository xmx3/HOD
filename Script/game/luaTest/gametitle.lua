--
-- GameTitle
--

-- タイトル画面実装
subclass("GameTitle", Actor) {
		__tostring = function(self)
			return("class Title name="..self.name) 
		end
}

-- コンストラクタ
function GameTitle:ctor(...)
	print("GameTitle:ctor() called")
	GameTitle.super.ctor(self, ...)
end

-- 初期化
function GameTitle:init(cfg)
	-- スーパークラス(Actor)のinitを呼ぶ
	print("GameTitle:init");
	Actor.init(self, cfg)
	self.label = GUI.Label:new_local(0,0,200,200)
	GUI.Manager:instance():add(self.label)
	glue_test.setState("start");
end

-- Actor削除時に実行される
function GameTitle:on_destroy()
	print("GameTitle:on_destroy()");
	GUI.Manager:destory()--静的クラス関数
	-- self.label:delete()
end


-- 状態関数

function GameTitle:state_start(rt)
	print("GameTitle:state_start");
	while not GUI.Manager:instance():isReady() do
		self:wait(0)
	end
	return "goto", "state_frame"
end

function GameTitle:state_frame(rt)
	-- NameSpaceA__func();
	-- print("3")
	-- print( type( glue_test.getNull()) );
	local d = Delivered:new_local()
	d:foo()
	d:vfunc()
	
	local btTr0 = btTransform:new_local();
	btTr0:setIdentity()
	local btTr1 = btTransform:new_local(btTr0);
	local btTr2 = btTr0*btTr1
j	
	local spi = std.shared_ptr_int_:new_local()
	local spiv = std.vector_IntSharedPtr_:new_local()
	print(type(spiv))
	spiv:push_back(spi)
	
	-- local spi1 = IntSharedPtr:new_local()--コンパイルエラーtypedefの形はpkgでは使うべきではない
	
	local sptr = Hellow:create()
	-- local sptr = std.shared_ptr_Hellow_:new_local()
	print(type(sptr))
	print(type(sptr:get()))
	sptr:get():hellow()
	
	self.sptr = Hellow:create()
	self.sptr:get()
	
	local t = btTransform:getIdentity()
	
	local v = std.vector_int_:new_local()
	v:push_back(0)
	v:push_back(1)
	v:push_back(2)
	print( "vector ", v[0], v[1], v[2] );
	
	NamespaceTest.func();
	self.label:setText("3")
	self:wait(60)
	-- print("2")
	self.label:setText("2")
	self:wait(60)
	-- print("1")
	self.label:setText("1")
	self:wait(60)
	-- print("0")
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
	
	glue_test.setState("exit");
	
	change_scene(GameTitle2)
	return "exit"
	
end

