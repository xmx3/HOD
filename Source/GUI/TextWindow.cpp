#include"TextWindow.h"
#include<assert.h>
#include<sstream>
#include<GameLib/GameLib.h>
#include<GameLib/Graphics/Enum.h>
#include<GameLib/Graphics/Texture.h>
#include<GameLib/PseudoXml/Document.h>
#include<GameLib/PseudoXml/Element.h>
#include<GameLib/PseudoXml/Attribute.h>
#include<GameLib/Base/OStringStream.h>
#include"MMD/MMDMacro.h"
#include"helper/MyOutputDebugString.h"
#include<GameLib/Scene/StringRenderer.h>
#include<GameLib/Scene/PrimitiveRenderer.h>
#include<GameLib/Input/Keyboard.h>
#include<GameLib/Math/Vector2.h>
#include<GameLib/Scene/PrimitiveRenderer.h>
#include<GameLib/Scene/StringRenderer.h>
#include<GameLib/Scene/Font.h>
#include"Manager.h"
#include"Fonts.h"
namespace GUI{
TextWindow::TextWindow(
		//int x, int y,
		//int sizeX, int sizeY,
		//unsigned int color,
		//unsigned int fontColor 
	)
		:mkMaxLengthOfLine(DEFALUT_MAX_LENGTH_OF_LINE),
		mkMaxDisplayLines(DEFALUT_MAX_DISPLAY_LINES ),
		mCurrentLine(0),
		mCurrentCharPos(0),
		mCurrentMessage(0),
		mX(100), mY(360),
		mSizeX(540), mSizeY(120),
		mIconX(0), mIconY(370),
		mIconSizeX(90), mIconSizeY(90),
		mFontOffsetX(10),mFontOffsetY(10),
		mIsEnable(true), mIsDrawAble(true),
		mColor(0xffffffff),
		mFontColor(0xffffffff),
		mIsEnableDepthTest(true),
		mIsEnableDepthWrite(true),
		mBlendMode(GameLib::Graphics::BLEND_LINEAR),
		mCullMode(GameLib::Graphics::CULL_NONE),
		mRender(NULL),
		mStringRender(NULL),
		mDocument(NULL),
		mWindowTexture(NULL),
		mMaxCharLengthInDisplay(0)
{
	using namespace GameLib::Scene;
	mRender = NEW PrimitiveRenderer();
	mStringRender = NEW StringRenderer();
	*mRender = PrimitiveRenderer::create( 12,  2 );
	//stringRenderのprimitiveRendererのcapcityの確保が2倍になってるけど6倍だろ。一つの文字に対して四角形一つ(頂点6個)なのでということで2*3の3
	*mStringRender = StringRenderer::create( (mkMaxLengthOfLine)*(mkMaxDisplayLines)*3, mkMaxDisplayLines );
	mStringRender->setFont( Fonts::getGothic() );
}
TextWindow::~TextWindow(){
	SAFE_DELETE( mWindowTexture );
	SAFE_DELETE(mDocument);
	SAFE_DELETE( mStringRender );
	SAFE_DELETE( mRender );
}
bool TextWindow::load( const char*fileName ){
	using namespace GameLib::PseudoXml;
	SAFE_DELETE( mDocument );
	mDocument = new Document;
	*mDocument = Document::create(fileName);

	SAFE_DELETE( mWindowTexture );
	mWindowTexture = new GameLib::Graphics::Texture;
	//*mWindowTexture = GameLib::Graphics::Texture::create("Data/GUI/window.png");
	*mWindowTexture = GameLib::Graphics::Texture::create("Data/GUI/simple.bmp");
	//*mWindowTexture = GameLib::Graphics::Texture::create("Data/GUI/naname_window.png");

	return !mDocument->isError() && !mWindowTexture->isError();
}

bool TextWindow::isReady(){
	using namespace GameLib::PseudoXml;
	using namespace GameLib::Graphics;
	if( mDocument && *mDocument ){
		if( mDocument->isReady() ){
			typedef std::map< const std::string, Icon >::iterator MapIterator;
			std::map< const std::string, Icon > nameIconMap;
		
			int childNum = mDocument->root().childNumber();
			for(int i=0; i<childNum; ++i){
				const Element e = mDocument->root().child(i);
				//icon 要素の場合
				if( strcmp( e.name(), "icon" )==0 )
				{
					std::string name;
					std::string file;
					assert( name.empty() && file.empty() );
					assert(2==e.attributeNumber());
					for( int j=0; j<2; ++j){
						GameLib::PseudoXml::ConstAttribute a = e.attribute(j);
						if( strcmp( a.name(), "name" )==0 ){
							assert( name.empty() && "xmlData is wrong! attribute( name in icon ) is doubled." );
							name.assign( a.value() );
							name.shrink_to_fit();
						} else if( strcmp( a.name(), "file" )==0 ){
							assert( file.empty() && "xmlData is wrong! attribute( file in icon ) is doubled." );
							file.assign( a.value() );
							file.shrink_to_fit();
						} else{
							assert( false && "xmlData is wrong! check  word spell( name or file in icon)." );			
						}
					}
					assert( !name.empty() && " name of attribute in icon is nothing!" );
					assert( !file.empty() && " file of attribute in icon is nothing!" );
					Texture tex = Texture::create( file.c_str() );
					Icon icon( name, tex );
					std::map< const std::string, Icon >::_Pairib pairib;
					//すでにkeyがあるなら上書きしない
					pairib=nameIconMap.insert( std::make_pair( name, icon ) );
					assert( pairib.second && "the name has already existed." );
				}
				else if( strcmp( e.name(), "message" )==0 )
				{
					std::string name;
					std::string text;
					assert( name.empty() && text.empty() );
					assert(0==e.childNumber());
					assert(2==e.attributeNumber());
					for( int j=0; j<2; ++j){
						GameLib::PseudoXml::ConstAttribute a = e.attribute(j);
						if( strcmp( a.name(), "name" )==0 ){
							assert( name.empty() && "xmlData is wrong! attribute( name in message ) is doubled." );
							name.assign( a.value() );
							name.shrink_to_fit();
						} else if( strcmp( a.name(), "text" )==0 ){
							assert( text.empty() && "xmlData is wrong! attribute( text in message ) is doubled." );
							text.assign( a.value() );
							text.shrink_to_fit();
						} else{
							assert( false && "xmlData is wrong! check  word spell( text or name in text)." );			
						}
					}
					assert( !name.empty() && " name of attribute in message is nothing!" );
					assert( !text.empty() && " text of attribute in message is nothing!" );
				
					MapIterator it = nameIconMap.find( name );
					if( it!=nameIconMap.end() ){
						//行ごとに分割
						std::istringstream iss(text);
						std::string line;
						Lines lines;
						while(!iss.eof()){
							std::getline( iss, line );
							int length = line.length();
							if( length <= mkMaxLengthOfLine ){
								line.shrink_to_fit();
								lines.push_back(line);
							} else{
								//一文字づつ取り出す。unsigned charにする必要あり
								int n = static_cast< int >( line.size() );
								const unsigned char* s = reinterpret_cast< const unsigned char* >( line.c_str() );
					
								//前の行の最後の文字を多めに取っている場合、切り取り開始位置が異なる
								int start=0;

								for ( int i = 0; i < n; ++i ){
									bool is2Byte=false;
									//Char準備
									int code = s[ i ];
									//ShiftJis範囲か？
									if ( ( code >= 0x81 && code <= 0x9F ) || ( code >= 0xE0 && code <= 0xFC ) ){
										if ( ( i + 1 < n ) ){
											code <<= 8;
											code |= s[ i + 1 ]; //2バイトコード
											is2Byte=true;
										}
									}
									//if ( code == '\n' ){ //改行文字ですな。
									//	//ここ、こないな。
									//	//たぶん\は2バイトコードとして処理されない
									//	assert(false);
									//}

									if( (i+1)%mkMaxLengthOfLine == 0 ){
										if( is2Byte ){
											lines.push_back( line.substr(start, i-start+2 ) );
											start=i+2;
										} else {
											lines.push_back( line.substr(start, i-start+1 ) );
											start=i+1;
										}
									}

									if(is2Byte){
										++i;
										if( (i+1)%mkMaxLengthOfLine == 0 ){
											lines.push_back( line.substr(start, i-start+1 ) );
											start=i+1;
										}
									}
								}
								if(n!=start){
									lines.push_back( line.substr(start, n-start+1 ) );
								}


							}
						}
						lines.shrink_to_fit();
		
						//const Message m( it->second,  lines );
						//mMessages.push_back( m );
						//mMessages.push_back( std::make_pair< Icon, const std::vector< const std::string > >( it->second,  lines ) );
						mMessages.push_back( std::make_pair( it->second,  lines ) );
						//mMessages.push_back( std::make_pair< Icon, const Lines >( it->second,  lines ) );
					} else{
						assert( false && "Icon is not found. Maybe order of elements is wrong! Icon element must be first. Or name spell is wrong." );
					}
				}
				else {
					assert( false && "xmlData is wrong! check word spell(icon or message)." );
				}
			}
			mMessages.shrink_to_fit();
			(*mDocument).release();
			assert(!*mDocument);
			return false;
		} else {
			return false;
		}
	} else if( mDocument && !(*mDocument) ){
		
		if( !mWindowTexture->isReady() ){
			return false;
		}


		bool result=true;
		BOOST_FOREACH( Message m, mMessages ){
			result = result && m.first.second.isReady();
		}

		if(result){
			calcMaxCharLengthInDisplay();

			//BOOST_FOREACH( Message &m, mMessages ){
			//	BOOST_FOREACH( const std::string &s ,m.second ){
			//		TRACE1("%s\n", s.c_str() );
			//	}
			//}
		}
		return result;
	}
	else {
		assert(false);
		return false;
	}
}


void TextWindow::update(){
	++mCurrentCharPos;

	GameLib::Input::Keyboard k;
	const Lines & lines = mMessages[mCurrentMessage].second;
	int numLines = lines.size();


	if( k.isTriggered( k.KEY_RETURN ) ){
		if( mMaxCharLengthInDisplay < mCurrentCharPos ){
			if( mCurrentLine < numLines-mkMaxDisplayLines ){
				mCurrentLine+=mkMaxDisplayLines;
				mCurrentCharPos=0;
				calcMaxCharLengthInDisplay();
			}
			//メッセージ単位のぺーじ送り
			else{
				//最後のせりふの場合
				if( mCurrentMessage == mMessages.size()-1 ){
					//なにもしない
				} else {
					++mCurrentMessage;
					mCurrentLine=0;
					mCurrentCharPos=0;
					calcMaxCharLengthInDisplay();
				}
				
			}
		}
		//ページ全表示
		else {
			mCurrentCharPos=mMaxCharLengthInDisplay;
		}
	}
}

void TextWindow::draw( Manager* mngr ){
	using namespace GameLib::Math;
	using namespace GameLib::Graphics;

	mRender->enableDepthTest( mIsEnableDepthTest );
	mRender->enableDepthWrite( mIsEnableDepthWrite );
	mRender->setBlendMode( mBlendMode );
	mRender->setCullMode( mCullMode );

	unsigned int displayCharNum = mCurrentCharPos;
	const Lines & lines = mMessages[mCurrentMessage].second;
	int numLines = lines.size();

	for( int i=0; i<mkMaxDisplayLines && mCurrentLine+i<numLines ; ++i){
		if( displayCharNum > lines[mCurrentLine+i].length() ){
			mStringRender->add( mX+mFontOffsetX, mY+32*i+mFontOffsetY , lines[mCurrentLine+i].c_str(), mFontColor );
			displayCharNum-=lines[mCurrentLine+i].length();
		} else {
			mStringRender->add( mX+mFontOffsetX, mY+32*i+mFontOffsetY , lines[mCurrentLine+i].substr(0, displayCharNum ).c_str(), mFontColor );
			break;
		}
	}

	if(*mWindowTexture)
	{
		mRender->setTexture( *mWindowTexture );

		mRender->addRectangle( 
			Vector2( static_cast<float>(mX), static_cast<float>(mY) ),
			Vector2( static_cast<float>(mX+mSizeX), static_cast<float>(mY+mSizeY) ),
			Vector2( 0.f, 0.f ),
			Vector2( 1.f, 1.f ),
			mColor );
	} else {
		//assert(false && "you don't set a Texture.");
	}

	const Icon &icon = mMessages[mCurrentMessage].first;
	const Texture & iconTex = icon.second;
	if( iconTex ){
		mRender->setTexture( iconTex );
		mRender->addRectangle(
			Vector2( static_cast<float>(mIconX), static_cast<float>(mIconY) ),
			Vector2( static_cast<float>(mIconX+mIconSizeX), static_cast<float>(mIconY+mIconSizeY) ),
			Vector2( 0.f, 0.f ),
			Vector2( 1.f, 1.f ),
			mColor );
	}

	mRender->draw();
	mStringRender->draw();
}


bool TextWindow::hasRead() const {
	const Lines & lines = mMessages[mCurrentMessage].second;
	unsigned int numLines = lines.size();


	return mMaxCharLengthInDisplay <= mCurrentCharPos &&  static_cast<int>(mMessages.size())-1 <= mCurrentMessage;
}


void TextWindow::calcMaxCharLengthInDisplay(){
	// 毎回計算するより必要になったとき計算
	//画面内の表示する文字数
	//totalCharLength
	//numCharsInDisplay
	mMaxCharLengthInDisplay=0;
	const Lines &currentLines = mMessages[mCurrentMessage].second;
	int numLines = currentLines.size();
	for( int i=0; i<mkMaxDisplayLines && mCurrentLine+i<numLines; ++i){
		mMaxCharLengthInDisplay += currentLines[mCurrentLine+i].length();
	}
}


} //end namespace GUI