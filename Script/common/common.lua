
-- ローカル変数にするとグローバルテーブルの検索がなくなり少し高速化する
local tremove = table.remove
local rawset = rawset
local tinsert = table.insert


global "orig_print"
if not _G.orig_print then
    orig_print = print
    if rawget(_G, "decoda_output") then
        print = function(...)
            local t = {}
            for i,v in ipairs({...}) do
                tinsert(t, tostring(v))
            end
            decoda_output(table.concat(t))
        end
    end
end


-- テーブルの内容を表示
local nest_level_limit = 6

function get_table_string(t, str_buf)
	return table.concat(get_table_string_sub(str_buf or {}, t, 0, {}))
end
function get_value_string(v, str_buf)
	return table.concat(get_value_string_sub(str_buf or {}, v, 0, {}))
end

-- s: 文字列バッファ
-- t: 対象テーブル
-- level: ネスティングレベル(nil可)
-- stack: 上位スタック(nil可)
function get_table_string_sub(s, t, level, stack)
	local level = level or 0
	local stack = stack or {}
	local indent = string.rep("  ", level)
	if level > nest_level_limit then
        tinsert(s, indent)
        tinsert(s, "table : nest too deep") --
        tinsert(s, tostring(t))
	    return s
	end
	for i,v in ipairs(stack) do
		if v == t then
			tinsert(s, indent)
			tinsert(s, "table : << same as parent >> : ")
			tinsert(s, tostring(t))
			return s
		end
	end
	tinsert(stack, t)
	tinsert(s, indent)
	tinsert(s, "{ (= ")
	tinsert(s, tostring(t))
	tinsert(s, ")\n")
	for k,v in pairs(t) do
		tinsert(s, indent)
		tinsert(s, "  [")
		get_value_string_sub(s, k, level, stack)
		tinsert(s, "] = ")
		get_value_string_sub(s, v, level, stack)
		tinsert(s, "\n")
	end
    if getmetatable(t) ~= nil then
	  tinsert(s, indent)
      tinsert(s, "  <metatable> ")
      get_table_string_sub(s, getmetatable(t), level+1, stack)
	  tinsert(s, indent)
      tinsert(s, "  </metatable>\n")
    end
	tinsert(s, indent)
	tinsert(s, "}\n")
	tremove(stack)

	return s
end

-- 値から文字列を作成
function get_value_string_sub(s, v, level, stack)
	local level = level or 0
	local typ = type(v)
	if typ == "table" then
		get_table_string_sub(s, v, level+1, stack)
	elseif typ == "string" then
		tinsert(s, '"')
		tinsert(s, v)
		tinsert(s, '"')
	else
		tinsert(s, typ)
		tinsert(s, ":")
		tinsert(s, tostring(v))
	end
	return s
end

-- 配列型のテーブル(t)中に指定値(value)があればそれを削除して詰める。
-- 値が発見されれば元のインデックスを返す。
-- 値がなければnilを返す。
function remove_value_from_array(t, value)
    for i,v in ipairs(t) do
        if v == value then
            tremove(t,i)
            return i
        end
    end
	return nil
end


-- テーブルから値をすべて削除する
function clear_table(t)
	-- 配列要素を削除
	while tremove(t) do end

	-- それ以外の要素を削除
	for k,v in pairs(t) do
		rawset(t, k, nil)
	end
end



-- テーブルをクローン
-- リンクが循環する場合はスタックオーバーフローになります

--[[ 循環に弱いバージョン
function clonetable(newtable, t)
	for k,v in pairs(t) do
		if type(v) == "table" then
			newtable[k] = clonetable({}, v)
		else
			newtable[k] = v
		end
	end
	return newtable
end
]]

-- テーブルをクローン
-- リンクが循環する場合はnilを返します
function clonetable(newtable, t, nestcheck)
	-- 循環チェック(cycle)
    local nestcheck = nestcheck or {}
    for i,v in ipairs(nestcheck) do
        if v == t then
            --error("detected nesting in clonetable()")
            print("WARNING: detected nesting in clonetable()")
			return nil
        end
    end
	
	-- テーブルの要素をそれぞれクローン
    tinsert(nestcheck, t) -- テーブル巡回中はネスト情報を追加しておく
	for k,v in pairs(t) do
		if type(v) == "table" then
			if is_class_instance(v) then
				-- クラスだったら新しいインスタンスを作ってcloneする
				-- clone関数がなければエラーになる
				local class = get_class(v)
				newtable[k] = class:new(v)
			else
				-- テーブルならさらにクローン
				newtable[k] = clonetable({}, v, nestcheck)
			end
		else
			newtable[k] = v
		end
	end
    tremove(nestcheck)

	return newtable
end
