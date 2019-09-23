#include"StateMachineImpl.h"
namespace FSM{
	namespace Player{
		//現在の C++ では、特定の翻訳単位でテンプレートを強制的にインスタンス化する方法がいくつかある
		// 方法1
		//template class boost::msm::back::state_machine<Impl_t>;
		// 方法2
		//sizeof(std::vector<Hoge>);

	}
}
