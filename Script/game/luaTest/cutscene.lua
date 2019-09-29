--
-- CutScene
--

-- タイトル画面実装
subclass("CutScene", Actor) {
		__tostring = function(self)
			return("class Title name="..self.name) 
		end
}

-- コンストラクタ
function CutScene:ctor(...)
	print("CutScene:ctor() called")
	CutScene.super.ctor(self, ...)
end

-- 初期化
function CutScene:init(cfg)
	-- スーパークラス(Actor)のinitを呼ぶ
	print("CutScene:init");
	Actor.init(self, cfg)
end

-- Actor削除時に実行される
function CutScene:on_destroy()
	print("CutScene:on_destroy()");
	self.miku:reset()
	BulletPhysics.Manager:instance(BulletPhysics.CutSceneWorldIndex):release()
	MME.Drawer.CutScene.destroy()
end


-- 状態関数

function CutScene:state_start(rt)
	print("CutScene:state_start");
	local model = XmlLoader.MME.Object.ModelKai:new_local()
	model:loadStart( "Data/XmlLoader/Model/dance.xml" );
	local camera = MMD.MMDDataBase:loadVMD("Data/MMDData/vmd/kisimencamera.vmd")
	local isOk = 
		model:isReady() and
		camera:get():isReady()
	
	print("load start Data/XmlLoader/Model/dance.xml Data/MMDData/vmd/kisimencamera.vmd"  )
	while not isOk do
		isOk = 
			model:isReady() and
			camera:get():isReady() and
			MME.Drawer.CutScene.isReady()
		self:wait(0)
	end
	self.miku = model:instance()
	self.camera = camera:get():getCameraAnimation()
	self.time = 0
	
	local w = D3DXMATRIX:new_local();
	D3DXMatrixIdentity(w);
	self.miku:get():init(w, "dance" );

	
	local mme = MME.Manager:instance()
	MME.Drawer.CutScene.add(self.miku)
	
	self.miku:get():addToWorld(BulletPhysics.CutSceneWorldIndex)
	return "goto", "state_frame"
	
end

function CutScene:state_frame(rt)

	local mme = MME.Manager:instance()
	local miku = self.miku:get()
	local fw = GameLib.Framework:instance();
	local world = D3DXMATRIX:new_local();
	D3DXMatrixIdentity(world);

	while true do
		if(miku:isAnimOver()) then
			self.time=0.0;
			-- Telop.setTime(0.0);
			-- miku:init( world, "dance" );
			return "exit"
		end

		local isPlaying = true
		local elapsedTime=0.0;

		if( isPlaying ) then
			--可変フレームレート
			--local deltaMilliSec = fw:previousFrameInterval();
			--local elapsedTime = deltaMilliSec*0.001;
			--
			--固定フレームレート
			elapsedTime= 1.0/60.0;
		end

		self.time = self.time+elapsedTime
		local black = GameLib.Math.Vector4:new_local(1.0)
		mme:setEdgeColor( black );

		local gm = GameLib.Graphics.Manager:instance();

		-- GameLib::Input::Keyboard k;

		miku:update(world, elapsedTime );

		-- ////F1 reload lua
		-- //if(k.isTriggered(GameLib::Input::Keyboard::KEY_F1) ){
		-- //	ReloadLuaFiles( "all" );		
		-- //}
		-- //
		-- //// フレーム関数を呼ぶ（失敗したらリロードして再度チャレンジ）
		-- //Lua::LuaFuncParam result;
		-- //while (!CallLuaFunc("framefunc", &result, 1)) {
		-- //	WaitInputOnError( GetLuaError(), "Reload OK?");
		-- //	ReloadLuaFiles( "all");
		-- //}
		-- //const char *str = result.GetString(0);
		--

		-- //カメラの設定
		local view = D3DXMATRIX:new_local() 
		local proj = D3DXMATRIX:new_local() 
		local pos = D3DXVECTOR3:new_local()
		local lookAt = D3DXVECTOR3:new_local()
		local up = D3DXVECTOR3:new_local()

		local viewAngle=0


		viewAngle = self.camera:get():calc( self.time, pos, lookAt, up, viewAngle );
		
		-- print("pos    :", pos.x, pos.y, pos.z )
		-- print("lookAt :", lookAt.x, lookAt.y, lookAt.z )
		-- print("up     :", up.x, up.y, up.z )
		-- print("angle :", viewAngle )
		
		D3DXMatrixLookAtLH( view, pos, lookAt, up );

		local aspect = fw:width()/fw:height();
		-- print(aspect)

		D3DXMatrixPerspectiveFovLH( proj, viewAngle, aspect, 0.1, 3000.0 );
		mme:setWorldMatrix( world ); 
		mme:setViewMatrix( view );
		mme:setProjectionMatrix( proj );
		mme:setZNear( 0.1 );
		mme:setZFar( 3000.0 );

		BulletPhysics.Manager:instance(BulletPhysics.CutSceneWorldIndex):update(elapsedTime)
		
		-- draw
		-- local gm = GameLib.Graphics.Manager:instance();

		MME.Drawer.CutScene.draw();

		-- GUI::Manager::instance()->draw();

		-- //以下フロントエンド描画
		-- //モデル描画でいじられたものを元に戻す
		local rgbBlack = GameLib.Math.Vector3( 1.0, 1.0, 1.0 )
		gm:setDiffuseColor( rgbBlack );
		gm:setTransparency( 1.0 );
		gm:setLightingMode( GameLib.Graphics.LIGHTING_NONE );

		-- Telop.draw( elapsedTime*60.0 );--//フレームに直す
		
		self:wait(0)
		
		
	end--end game loop

	return "exit"
end

