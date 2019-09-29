

print("Hello!from gameinit.lua");

collectgarbage("setpause", 105)
collectgarbage("setstepmul", 1000)
collectgarbage("collect")

--
--  GS : GameSystem
--

global "GS"

GS = {
	scheduler = nil,        -- スケジューラー
	scene = nil,            -- 現在のシーン（アクター）
}

local GS = GS

-- 開始処理
function startfunc()
	print("startfunc() start!" )

	GS.routinepool = RoutinePool:new()
	GS.routinepool:init(50)

	GS.scheduler = Scheduler:new()

	-- 最初はタイトル画面シーンを設定する
	GS.scene = GameTitle:new()
	GS.scene:init()
	
	GS.next_scene = nil
	GS.next_scene_cfg = nil
end

-- Lua版でもC言語版でも結果リストの指定インデックスのActorオブジェクトを返す
function get_result_actor(index, collision_obj)
	if GS.use_c_collision then
		return Actor.get_actor_by_id(collision_obj:get_result(index))
	else
		return collision_obj:get_result(index)
	end
end


function endfunc()
	if GS.scene ~= nil then
		GS.scheduler:delete_actor(GS.scene)
	end
	if GS.cursor ~= nil then
		GS.scheduler:delete_actor(GS.cursor)
	end
	--GS.scheduler:process_deleted_actors()	
	GS.scheduler:schedule()	
	GS.cursor = nil
	GS.scene = nil
end

-- シーンを変更
function change_scene(scene_class, ...)
	GS.next_scene_class = scene_class
	GS.next_scene_cfg = {...}
end

--テスト
function change_scene_test(scene_class, ...)
	local class = rawget(_G, scene_class)
	assert(class~=nil)
	GS.next_scene_class = class
	GS.next_scene_cfg = {...}
end



-- フレームの進行処理
function framefunc()
	-- シーン移行の場合
	if GS.next_scene_class ~= nil then
		if GS.scene ~= nil then
			GS.scheduler:delete_actor(GS.scene)
		end
		GS.scheduler:process_deleted_actors()
		GS.scene = GS.next_scene_class:new()
		GS.scene:init(unpack(GS.next_scene_cfg))
		GS.next_scene_class = nil
		GS.next_scene_cfg = nil
	end

	if GS.scene == nil then
		return "no scene"
	end
	
	-- -- マウスカーソル位置取得
	-- local x,y = cfunc.GetMousePos()
	-- if GS.cursor ~= nil then
	-- 	GS.cursor.params.x = x
	-- 	GS.cursor.params.y = y
	-- end
	
	-- シーンごとのスケジューラー前処理
	if GS.scene.pre_schedule ~= nil then
		GS.scene:pre_schedule()
	end
	
	-- スケジューラー処理
	GS.scheduler:schedule()	

	-- シーンごとのスケジューラー後処理
	if GS.scene.post_schedule ~= nil then
		GS.scene:post_schedule()
	end
	
	-- print(GS.scheduler:has_actor())
	-- print(GS.scheduler:number_of_actors())
	-- GS.scheduler:print_actors()
	return GS.scheduler:number_of_actors()
	-- return "ok"
end

--[[
-- キー入力イベントハンドラ
function on_keyevent(key, is_down, is_ctrl, is_alt, is_shift)
	-- キー情報をモニタリング（デバッグ用）
	print("on_keydown(key=",key, " is_ctrl=", is_ctrl, " is_alt=", is_alt, " is_shift=", is_shift, ")")
	
	if is_down then
		-- 特殊機能
		-- F1 : キャラ部分リロード
		-- F2 : 全スクリプトリロード
		-- F9 : 実行情報出力
		if key == SDLK_F1 then
			cfunc.ReloadLuaFiles("chars")
			return
		end
		if key == SDLK_F2 then
			cfunc.ReloadLuaFiles("all")
			return
		end
		if key == SDLK_F9 then
			print("GC count = ",collectgarbage("count"))
			print("F9 pressed")
			analyze_instances()
			SDL.SDL_Delay(5000)
			return
		end
	end
	
	-- イベントをシーンに投げる
	if GS.scene ~= nil and GS.scene.on_keyevent ~= nil then
		GS.scene:on_keyevent(key, is_down, is_ctrl, is_alt, is_shift)
	end
end

-- マウスイベントハンドラ
function on_mouseevent(evtype, button, x, y)
	-- マウス情報をモニタリング（デバッグ用）
	if evtype == "down" then
		print("mousedown(button=",button, " x=", x, " y=", y, ")")
	elseif evtype == "up" then
		print("mouseup(button=",button, " x=", x, " y=", y, ")")
	end

	-- イベントをシーンに投げる
	if GS.scene ~= nil then
		GS.scene:on_mouse(evtype, button, x, y)
	end
end
]]

