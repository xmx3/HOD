#pragma once
#include<vector>

namespace MME{
class BaseEffect;

namespace Object{
	class IObject;
	typedef std::shared_ptr<IObject> IObjectSharedPtr;
	typedef std::weak_ptr<IObject> IObjectWeakPtr;
}
//DrawObjects;
//DrawObjectList;
//DrawableObjects;
//DrawContainer
//共有リストにしたのはzbufferでソートしたときにリスト毎(effectbatch毎)にソートするのが効率悪そうだから
//半透明出すためにzソートが必要のときのため
//コンテナの種類はvector, listがいいと思う
//挿入削除を考えるとlistだが、
//後でまとめて削除する方式を取っている＋中に入っているのがポインタなので
//ソートするとき
typedef std::vector<Object::IObjectWeakPtr> DrawObjects;
typedef std::shared_ptr< DrawObjects > DrawObjectsSharedPtr;

namespace Batch {





}//Batch

}//MME