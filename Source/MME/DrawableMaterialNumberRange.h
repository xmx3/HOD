#pragma once

namespace MME {

class DrawableMaterialNumberRange {
public:
	//"0,3,5"のように、カンマ区切りで番号を列挙することで、複数の番号を指定できる。
	//また、"6-10"などのように、番号をハイフンでつなぐことで、範囲指定ができる。
	//"12-"のように、範囲の開始番号のみを指定した場合は、それ以降の全ての番号が対象となる。
	DrawableMaterialNumberRange( const char *text );
	~DrawableMaterialNumberRange();

	bool canDraw( unsigned int materialIndex ) const;

private:
	class Impl;
	Impl *mImpl;
};
}

