--
-- Clear
--

-- タイトル画面実装
subclass("Clear", Actor) {
		__tostring = function(self)
			return("class Clear name="..self.name) 
		end
}

-- コンストラクタ
function Clear:ctor(...)
	print("Clear:ctor() called")
	Clear.super.ctor(self, ...)
end

-- 初期化
function Clear:init(cfg)
	-- スーパークラス(Actor)のinitを呼ぶ
	print("Clear:init");
	Actor.init(self, cfg)
	-- print(cfg.score)
	self.score = cfg.score+cfg.playerHp;
	
	local fw = GameLib.Framework:instance();
	self.label = GUI.Label:new_local(
		0,0,
		fw:width(), fw:height() );
		
	self.label:setText(
	cfg.txt
	.."残りHP: " ..tostring(cfg.playerHp) .."\n"
	.."倒した敵の数: " ..tostring(cfg.numKilled) .."\n"
	.."スコア: " ..tostring(self.score)
	);
		
	GUI.Manager:instance():add(self.label)
	
	
end

-- Actor削除時に実行される
function Clear:on_destroy()
	print("Clear:on_destroy()");
	GUI.Manager:destory()--静的クラス関数
	
	local state = Sequence.HatuneOfTheDead.LuaImpl.State:instance()
	state:setNeedDrawCall(false);
end


-- 状態関数

function Clear:state_start(rt)
	print("Clear:state_start");
	while not GUI.Manager:instance():isReady() do
		self:wait(0)
	end
	
	local state = Sequence.HatuneOfTheDead.LuaImpl.State:instance()
	state:setNeedDrawCall(true);
	
	return "goto", "state_frame"
end

function Clear:state_frame(rt)
	
	local state = Sequence.HatuneOfTheDead.LuaImpl.State:instance()

	local i=0;
	while i< 600 do
		i = i+1;
		self:wait(0)
	end
	
	change_scene(Title)
	self:wait(0)--ないと下の行実行してon_destroy()が2度呼ばれる
	return "exit"
	
end

