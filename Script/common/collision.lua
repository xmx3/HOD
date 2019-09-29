

-- ２つの矩形が衝突するかどうかを返す
local function is_intersect_rects(x1,y1,w1,h1, x2,y2,w2,h2)
	local x_center1, y_center1, x_size1, y_size1 = x1,y1,w1,h1
	local x_center2, y_center2, x_size2, y_size2 = x2,y2,w2,h2
	local x_size1_half = x_size1 * 0.5
	local y_size1_half = y_size1 * 0.5
	local x_size2_half = x_size2 * 0.5
	local y_size2_half = y_size2 * 0.5
	local x1L = x_center1 - x_size1_half
	local x1R = x_center1 + x_size1_half
	local y1U = y_center1 - y_size1_half
	local y1D = y_center1 + y_size1_half
	local x2L = x_center2 - x_size2_half
	local x2R = x_center2 + x_size2_half
	local y2U = y_center2 - y_size2_half
	local y2D = y_center2 + y_size2_half
	if (x1R < x2L) or (x2R < x1L) or (y1D < y2U) or (y2D < y1U) then return false end
	return true
end


-- 衝突判定クラス
class ("CollisionDetector") {
}

-- コンストラクタ
function CollisionDetector:ctor(...)
    self.grid = {}
    self.x_gridspan = 100
    self.y_gridspan = 100
    self.x_fieldsize = 640*4
    self.y_fieldsize = 480
    self.x_gridcount = 0
    self.y_gridcount = 0
    self.total_gridcount = 0
    
    self.results = {}
end

local floor = math.floor

function CollisionDetector:init(fieldsize_x, fieldsize_y, gridspan_x, gridspan_y)
	self.x_gridspan = gridspan_x
    self.y_gridspan = gridspan_y
    self.x_fieldsize = fieldsize_x
    self.y_fieldsize = fieldsize_y
	
    self.x_gridcount = floor((self.x_fieldsize - 1) / self.x_gridspan) + 1
    self.y_gridcount = floor((self.y_fieldsize - 1) / self.y_gridspan) + 1
    self.total_gridcount = self.x_gridcount * self.y_gridcount
    
    -- テーブルが「配列」として扱われるように細心の注意を払う
	self.grid = {}
    for i= 1, self.total_gridcount do
        self.grid[i] = {}
    end
end

-- オブジェクト（アクター）を衝突判定グリッドに追加
function CollisionDetector:add_object(actor, x1,y1,w1,h1)
	local x_center, y_center, x_size, y_size = x1,y1,w1,h1
	local x_size_half = x_size * 0.5
	local y_size_half = y_size * 0.5
	local cx1 = floor((x_center - x_size_half) / self.x_gridspan)
	local cy1 = floor((y_center - y_size_half) / self.y_gridspan)
	local cx2 = floor((x_center + x_size_half) / self.x_gridspan)
	local cy2 = floor((y_center + y_size_half) / self.y_gridspan)
	
	-- オブジェクトの範囲がかかるすべてのセルにアクターを追加
	for x = cx1,cx2 do
		for y = cy1,cy2 do
			local cellpos = y * self.x_gridcount + x + 1
			if cellpos >= 1 and cellpos <= self.total_gridcount then
				local cell = self.grid[cellpos]
				cell[#cell+1] = actor
			end
		end
	end
end

-- 衝突するオブジェクトを収集
function CollisionDetector:search_collided_objects(x1,y1,w1,h1)
	return self:search_near_objects(x1,y1,w1,h1, true)
end

-- 近くにあるオブジェクトを収集
-- 見つかったカウントを返す。結果はget_resultで得る
function CollisionDetector:search_near_objects(x1,y1,w1,h1, check_collision)
	local x_center, y_center, x_size, y_size = x1,y1,w1,h1
	local x_size_half = x_size/2
	local y_size_half = y_size/2
	local cx1 = floor((x_center - x_size_half) / self.x_gridspan)
	local cy1 = floor((y_center - y_size_half) / self.y_gridspan)
	local cx2 = floor((x_center + x_size_half) / self.x_gridspan)
	local cy2 = floor((y_center + y_size_half) / self.y_gridspan)
	local results = self.results
	local unique_check = {} -- 同一のものを複数追加しないためのチェックテーブル
	
	clear_table(results)

	-- 探索範囲がかかるすべてのセルからアクター情報を収集
	for x = cx1,cx2 do
		for y = cy1,cy2 do
			local cellpos = y * self.x_gridcount + x + 1
			if cellpos >= 1 and cellpos <= self.total_gridcount then
				for i,v in ipairs(self.grid[cellpos]) do
					if unique_check[v] ~= true then
						-- 正確な衝突判定をする場合は行う。そうでなければ
						-- 大雑把な判定で返す
						if not check_collision 
							or is_intersect_rects(x1,y1,w1,h1, v:get_collision_rect()) then
							results[#results+1] = v
							unique_check[v] = true
						end
					end
				end
			end
		end
	end
	return #results
end

-- グリッド内のデータをすべて空にして、init後の状態まで戻す。
function CollisionDetector:clear()
    -- 全グリッドセル内のオブジェクトリストを空にする
    for i= 1, self.total_gridcount do
        local t = self.grid[i]
        for i,v in ipairs(t) do
            t[i] = nil
        end
    end
end

-- 結果アクターを返す
-- indexは0ベースとする
function CollisionDetector:get_result(index)
    return self.results[index+1]
end


