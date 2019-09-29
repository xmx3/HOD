#include<string>
#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
#include<GameLib/Scene/Font.h>
#include<GameLib/Scene/StringRenderer.h>
#include<GameLib/Framework.h>
#include<GameLib/FileIO/OutFile.h>
#include<assert.h>

#include <boost/config/warning_disable.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/tuple.hpp>

namespace{
static const int skMaxTelopsPerFrame = 32;
static const int skMaxStringLength = 128;
static float skDefalutDuration = 1800.f;
static unsigned int skDefalutFontColor = 0xffffffff;

}

struct Request{
	Request(){}
	Request( const std::string &text, float start, float duration, unsigned int color=skDefalutFontColor )
	:mText(text),
	mStart(start),
	mDuration(duration),
	mFontColor( color )
	{}
	
	~Request(){}

	bool isRange( float time )const{
		return mStart < time && time < mStart+mDuration;
	}
	void print()const{
		std::cout << mStart << ", "<< mDuration << ", " << mText << std::endl;
	}

	void addStringTo(GameLib::Scene::StringRenderer *render, int x, int y )const{
		render->add( x, y, mText.c_str(), mFontColor );
	}
	void validate()const{
		assert( mText.length()<skMaxStringLength );
	}
	
	bool operator<(const Request & right )const{
		return mStart < right.mStart;
	}
	bool operator<(const float & start_right )const{
		return mStart < start_right;
	}
	
	float mStart;
	float mDuration;
	unsigned int mFontColor;
	//一行表示 文字数制限しろ
	std::string mText;
};

// We need to tell fusion about our request struct
// to make it a first-class fusion citizen. This has to
// be in global scope.
BOOST_FUSION_ADAPT_STRUCT(
		Request,
		(float, mStart)
		(float, mDuration)
		(unsigned int, mFontColor)
		(std::string, mText)
		)

namespace {

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct my_grammar 
: qi::grammar<Iterator, Request()>
{
	my_grammar()
		: my_grammar::base_type(start)
	{
		
		using qi::float_;
		using qi::hex;
		using qi::lit;
		using qi::lexeme;
		using qi::attr;

		quoted_string %= lexeme[ +(qi::char_ - '\n') ];

		start %=
			lit("@") >> *(lit(' '))
			>>  float_  >> *(lit(' ')) 
			>> ( (',' >> *(lit(' ')) >> float_ ) | attr(skDefalutDuration) ) >> *(lit(' '))
			>> ( (':' >> *(lit(' ')) >> lit("0x") >> hex ) | attr(0xffffffff) ) >> *(lit(' '))
			>> '\n'
			>>  quoted_string
			;
	}

	qi::rule<Iterator, std::string()> quoted_string;
	qi::rule<Iterator, Request()> start;
};

//明示的インスタンス化
template struct my_grammar<const char*>;

struct IsRequestEqualed{
	IsRequestEqualed(const Request &r)
	:mRequest(r)
	{}

	bool operator()( const Request &r )const{
		return
			mRequest.mStart == r.mStart &&
			mRequest.mDuration == r.mDuration &&
			mRequest.mText == r.mText;
	}
	
	bool operator()( const Request *r )const{
		return
			mRequest.mStart == r->mStart &&
			mRequest.mDuration == r->mDuration &&
			mRequest.mText == r->mText;
	}
	const Request &mRequest;
};



//telop time line telopline
class TelopImpl{
public:
	TelopImpl()
		:mTime(0.f),
		mStringRender(nullptr),
		mFontHeight(0)
	{
		mStringRender = new GameLib::Scene::StringRenderer();
		*mStringRender = GameLib::Scene::StringRenderer::create( skMaxStringLength, skMaxTelopsPerFrame );
		GameLib::Framework f;
		int width = f.width(), height=f.height();

		mX = 0;// width / 10;
		mY=height*9/10;

	}
	
	
	~TelopImpl(){
		SAFE_DELETE(mStringRender);
		mRequests.clear();
		mRequests.shrink_to_fit();
		mEnables.clear();
	}
	

	void insert( const char* text, float start, float duration ){
		assert( strlen(text)<skMaxStringLength );
		auto it=std::lower_bound(mRequests.begin(), mRequests.end(), start  );
		mRequests.insert( it, Request( std::string(text), start, duration ) );
	}
	
	//draw(elapsed)にしたのはアルゴリズム的に考えて、
	//それが一番計算量が少なくそうで、実装が楽だったから
	//draw()のほうが使いやすくはあるかも
	void draw( float elapsed ){
		//新たに(それ以前のものは前の処理でmEnablesに入っていると仮定)表示するのを探す
		auto it=std::lower_bound(mRequests.begin(), mRequests.end(), mTime );
			// std::cout << "debug-----time" << mTime<<"-" << mTime+elapsed << std::endl;;
		//逆再生のときは字幕は表示しない
		while( it!=mRequests.end() && it->mStart < mTime+elapsed ){
			// (*it)->print();
			auto pairib = mEnables.insert( &(*it) );
			if(pairib.second){
				// std::cout << "insert ";
				// (*it)->print();
			}
			++it;
		}
		// std::cout << "---------------------------------------\n";
		int x=mX, y=mY;
		for( auto it=mEnables.begin(); it!=mEnables.end(); ){
			if( (*it)->isRange(mTime+elapsed) )
			{
				(*it)->addStringTo(mStringRender, x, y);
				y+=mFontHeight;
				++it;
			} else {
				// std::cout << "remove ";
				// (*it)->print();
				it = mEnables.erase(it);
			}
		}
		mStringRender->draw();
		mTime += elapsed;
	}

	bool parse( const char *data, unsigned int size ){
		mRequests.clear();
		my_grammar<const char*> g;
		const char *first = data;
		const char *last = data+size;
		bool success = qi::parse(
				first,
				last,
				g >> *(+(qi::lit('\n')) >> g),
				mRequests );
		std::sort( mRequests.begin(), mRequests.end() );
		mRequests.shrink_to_fit();
		if (success)
		{
			if(first==last) {
			}else {
				//残りが空行かどうか調べる
				const char *it=first;
				for(
						;
						it < last;
						++it ){
					if( ((*it)=='\n') | ((*it)==' ') ){}
					else {
						break;
					}
				}

				if(it==last) {
				} else {
					assert(false);
					std::cout << "解析できなかった文字列" << first << std::endl;
				}
			}
			for(unsigned int i=0, size=mRequests.size(); i<size; ++i ){
				mRequests[i].validate();
			}
			return true;
		}
		else {
			assert(false);
			return false;
		}
	}
	
	void setFont( GameLib::Scene::Font f ){
		mStringRender->setFont( f );
		mFontHeight = f.charHeight()+1;
	}
	
	void setTime( float t ){
		mTime = t;
	}
	
	//字幕の位置を個々に変える場合仕様変更が必要
	void setPos( unsigned int x, unsigned int y ){
		mX=x;
		mY=y;
	}
	
	bool isFinished()const{
		unsigned int size=mRequests.size();
		if(size!=0){
			const Request & r = mRequests[size-1];
			return mTime > r.mStart+r.mDuration;
		}
		return true;
	}

	void eraseNow(){
		for( std::set<const Request*>::iterator
			it=mEnables.begin(), end=mEnables.end();
			it!=end;
			++it )
		{	
			IsRequestEqualed f( *(*it) );
			std::vector<Request>::iterator removePos =
				std::remove_if( mRequests.begin(), mRequests.end(), f ); 
			mRequests.erase( removePos, mRequests.end() );
		}
		mEnables.clear();
	
	}

	GameLib::FileIO::OutFile write(const char* fileName ){
		std::stringstream ss;
		for( 
			std::vector<Request>::iterator it=mRequests.begin(), end=mRequests.end();
			it!=end;
			++it )
		{
			const Request &r=*it;
			ss <<
				"@" << r.mStart << ", " << r.mDuration <<" :0x" <<  std::hex << r.mFontColor <<"\n" <<
				r.mText << "\n";

		}
		std::string str = ss.str();
		//strは一時ファイルだけど平気なのか。ここでファイル書き込むの待ったほうが良いのではないか？
		GameLib::FileIO::OutFile f = GameLib::FileIO::OutFile::create( fileName, str.c_str(), str.size() );
		return f;
	}


	float mTime;
	//一回構築したら削除することないのでvector
	//フレーム毎に追加したりするならlist
	std::vector<Request> mRequests;
	//同じものを重複しないように
	std::set<const Request*> mEnables;//mDisplayable;
	//elementで持たせるよりもこっちのほうが効率的
	//stringrenderが一つですむので
	GameLib::Scene::StringRenderer *mStringRender;
	int mX;
	int mY;
	int mFontHeight;
};
}//end unnamespace

namespace Telop{

std::unique_ptr< TelopImpl > gTelop;
TelopImpl* instance(){
	if( !gTelop ){
		gTelop.reset( new TelopImpl);
		gTelop->setFont(
			GameLib::Scene::Font::create("ＭＳ ゴシック", 32, false, false, false, true) //MSは全角、次のスペースは半角。気をつけよう。
		);
	}
	return gTelop.get();

}

void destroy() {
	gTelop.reset();
}

void insert( const char* text, float start, float duration ){
	instance()->insert( text, start, duration );
}
void draw( float elapsed ){
	instance()->draw(elapsed);
}

bool parse(const std::string &str) {
	return instance()->parse(str.c_str(), str.size());
}

bool parse( const char *data, unsigned int size ){
	return instance()->parse( data, size );
}

void setFont( GameLib::Scene::Font f ){
	instance()->setFont(f);
}

void setDefalutFontColor( unsigned int c){
	skDefalutFontColor=c;
}

void setDefalutDuration( float duration){
	skDefalutDuration = duration;
}


void setTime( float t ){
	instance()->setTime(t);
}

void setPos(unsigned int x, unsigned int y) {
	instance()->setPos( x, y);
}

bool isFinished(){
	return instance()->isFinished();
}

void eraseNow(){
	instance()->eraseNow();
}

GameLib::FileIO::OutFile write(const char*filename ){
	return instance()->write(filename);
}

}//end namespace Telop


/*
// debug用
#include <GameLib/DebugScreen.h>
namespace GameLib{
	void Framework::configure( Configuration* c ){
		c->setWidth(640);
		c->setHeight(480);
	}
	void Framework::update(){
		static TelopImpl telop;
		static int t=0;
		if(t==0){
			std::string s("\
@100,200\n 1にゃろめ\n@200,200\n 2 亜 a\n@300,200\n3できた？\n\n\n@400,200:0xff000000  \n4しろ？\n@500:0xffff0000  \n500red\n\
@900\nwwwwwwwwwwwwwwwwwwwww\n\
余分な文字");
			// 	telop.insert( "1", 100, 200 );
			// 	telop.insert( "2", 200, 200 );
			// 	telop.insert( "3", 300, 200 );
			// 	telop.insert( "4", 400, 200 );
			// 	telop.insert( "5", 500, 200 );
			// 	telop.insert( "6", 600, 200 );
			GameLib::Scene::Font f = GameLib::Scene::Font::create( "ＭＳ ゴシック", 24, false, false, false, true ); //MSは全角、次のスペースは半角。気をつけよう。
			telop.setFont(f);
			telop.parse( s.c_str(), s.size() );
		}
		++t;
		telop.draw(1);
		GameLib::DebugScreen sc;
		sc.setPosition( 0, 20 );
		sc.precision( 3 );
		sc << t;
		
		
		if(telop.isFinished()){
			telop.setTime(0);
			t=0;
		}
	}
}
*/

