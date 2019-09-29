--
-- GameTitle2
--

-- タイトル画面実装
subclass("GameTitle2", Actor) {
}

-- コンストラクタ
function GameTitle2:ctor(...)
	print("GameTitle2:ctor() called")
	GameTitle2.super.ctor(self, ...)
end

-- 初期化
function GameTitle2:init(cfg)
	print("GameTitle2:init() called")
	-- スーパークラス(Actor)のinitを呼ぶ
	Actor.init(self, cfg)
	self.label = GUI.Label:new_local(300,0,200,200)
	GUI.Manager:instance():add(self.label)
end

-- Actor削除時に実行される
function GameTitle2:on_destroy()
	-- self.label:delete()
end


-- 状態関数

function GameTitle2:state_start(rt)
	return "goto", "state_frame"
end

function GameTitle2:state_frame(rt)
	analyze_instances()
	print("gametitle2.lua")
	print("3")
	self.label:setText("3")
	self:wait(60)
	print("2")
	self.label:setText("2")
	self:wait(60)
	print("1")
	
	return "exit"

end


