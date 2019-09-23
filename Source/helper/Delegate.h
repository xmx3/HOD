#pragma once
#include <functional>
#include<vector>

//メンバー関数をを登録する場合
//auto func = std::bind(&Enemy::onCollisionEnter, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
//mRigidBodyComponent->getOnEnterCallback().add(func);

template<class RetType, class... Args>
class MultiCastDelegater_Param0
{
public:
	MultiCastDelegater_Param0() = default;
	~MultiCastDelegater_Param0() = default;

	MultiCastDelegater_Param0(const MultiCastDelegater_Param0 &) = delete;
	void operator=(const MultiCastDelegater_Param0 &) = delete;

	void add(const std::function<RetType(Args...)> &function) {
		mFunctions.push_back(function);	
	}

	void addStatic(typename RetType(*f)(Args...)) {
		constexpr std::size_t template_parameter_pack_size = sizeof...(Args);

		static_assert(template_parameter_pack_size == 0, "バインドする関数の引数の数がおかしい");
		std::function<RetType(Args...)> func =
			std::bind(
				f);

		mFunctions.push_back(func);
	}


	//呼ぶ前に開放されていたりしてその関数が使えない場合とかの考慮は全くしてない
	template< class UserClass >
	void addRaw(UserClass *user, typename RetType(UserClass::*f)(Args...)) {
		constexpr std::size_t template_parameter_pack_size = sizeof...(Args);

		static_assert(template_parameter_pack_size == 0, "bindする関数の引数の数がおかしい");
		std::function<RetType(Args...)> func =
			std::bind(
				f,
				user );

		mFunctions.push_back(func);
	}

	template< class UserClass >
	void addSP(std::shared_ptr<UserClass> user, typename RetType(UserClass::*f)(Args...)) {
		constexpr std::size_t template_parameter_pack_size = sizeof...(Args);

		static_assert(template_parameter_pack_size == 0, "bindする関数の引数の数がおかしい");
		std::function<RetType(Args...)> func =
			std::bind(
				f,
				user );

		mFunctions.push_back(func);
	}

	void clear() {
		mFunctions.clear()
	}

	void exec(Args... args...) {
		for (auto d : mFunctions)
		{
			d(args...);
		}
	}
private:
	std::vector<std::function<RetType(Args...)> > mFunctions;
};

template<class RetType, class... Args>
class MultiCastDelegater_Param1
{
public:
	MultiCastDelegater_Param1() = default;
	~MultiCastDelegater_Param1() = default;

	MultiCastDelegater_Param1(const MultiCastDelegater_Param1 &) = delete;
	void operator=(const MultiCastDelegater_Param1 &) = delete;

	void add(const std::function<RetType(Args...)> &function) {
		mFunctions.push_back(function);
	}

	void addStatic(typename RetType(*f)(Args...)) {
		constexpr std::size_t template_parameter_pack_size = sizeof...(Args);

		static_assert(template_parameter_pack_size == 1, "バインドする関数の引数の数がおかしい");
		std::function<RetType(Args...)> func =
			std::bind(
				f,
				std::placeholders::_1);

		mFunctions.push_back(func);
	}


	//呼ぶ前に開放されていたりしてその関数が使えない場合とかの考慮は全くしてない
	template< class UserClass >
	void addRaw(UserClass *user, typename RetType(UserClass::*f)(Args...)) {
		constexpr std::size_t template_parameter_pack_size = sizeof...(Args);

		static_assert(template_parameter_pack_size == 1, "bindする関数の引数の数がおかしい");
		std::function<RetType(Args...)> func =
			std::bind(
				f,
				user,
				std::placeholders::_1 );

		mFunctions.push_back(func);
	}

	template< class UserClass >
	void addSP(std::shared_ptr<UserClass> user, typename RetType(UserClass::*f)(Args...)) {
		constexpr std::size_t template_parameter_pack_size = sizeof...(Args);

		static_assert(template_parameter_pack_size == 1, "bindする関数の引数の数がおかしい");
		std::function<RetType(Args...)> func =
			std::bind(
				f,
				user,
				std::placeholders::_1 );

		mFunctions.push_back(func);
	}

	void clear() {
		mFunctions.clear()
	}

	void exec(Args... args...) {
		for (auto d : mFunctions)
		{
			d(args...);
		}
	}
private:
	std::vector<std::function<RetType(Args...)> > mFunctions;
};

template<class RetType, class... Args>
class MultiCastDelegater_Param2
{
public:
	MultiCastDelegater_Param2() = default;
	~MultiCastDelegater_Param2() = default;

	MultiCastDelegater_Param2(const MultiCastDelegater_Param2 &) = delete;
	void operator=( const MultiCastDelegater_Param2 & ) = delete;

	void add(const std::function<RetType(Args...)> &function) {
		mFunctions.push_back(function);
	}

	void addStatic(typename RetType(*f)(Args...)) {
		constexpr std::size_t template_parameter_pack_size = sizeof...(Args);

		static_assert(template_parameter_pack_size == 2, "バインドする関数の引数の数がおかしい");
		std::function<RetType(Args...)> func =
			std::bind(
				f,
				std::placeholders::_1,
				std::placeholders::_2);

		mFunctions.push_back(func);
	}

	//呼ぶ前に開放されていたりしてその関数が使えない場合とかの考慮は全くしてない
	template< class UserClass >
	void addRaw(UserClass *user, typename RetType(UserClass::*f)(Args...)) {
		constexpr std::size_t template_parameter_pack_size = sizeof...(Args);

		static_assert(template_parameter_pack_size == 2, "バインドする関数の引数の数がおかしい");
		std::function<RetType(Args...)> func =
			std::bind(
				f,
				user,
				std::placeholders::_1,
				std::placeholders::_2);

		mFunctions.push_back(func);
	}

	template< class UserClass >
	void addSP(std::shared_ptr<UserClass> user, typename RetType(UserClass::*f)(Args...)) {
		constexpr std::size_t template_parameter_pack_size = sizeof...(Args);

		static_assert(template_parameter_pack_size == 2, "bindする関数の引数の数がおかしい");
		std::function<RetType(Args...)> func =
			std::bind(
				f,
				user,
				std::placeholders::_1,
				std::placeholders::_2);

		mFunctions.push_back(func);
	}

	void clear() {
		mFunctions.clear()
	}

	void exec(Args... args...) {
		for (auto d : mFunctions)
		{
			d(args...);
		}
	}
private:
	std::vector<std::function<RetType(Args...)> > mFunctions;
};

template<class RetType, class... Args>
class MultiCastDelegater_Param3
{
public:
	MultiCastDelegater_Param3() = default;
	~MultiCastDelegater_Param3() = default;

	MultiCastDelegater_Param3(const MultiCastDelegater_Param3 &) = delete;
	void operator=(const MultiCastDelegater_Param3 &) = delete;

	void add(const std::function<RetType(Args...)> &function) {
		mFunctions.push_back(function);
	}

	void addStatic( typename RetType(*f)(Args...)) {
		constexpr std::size_t template_parameter_pack_size = sizeof...(Args);

		static_assert(template_parameter_pack_size == 3, "バインドする関数の引数の数がおかしい");
		std::function<RetType(Args...)> func =
			std::bind(
				f,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3);

		mFunctions.push_back(func);
	}

	//呼ぶ前に開放されていたりしてその関数が使えない場合とかの考慮は全くしてない
	template< class UserClass >
	void addRaw(UserClass *user, typename RetType(UserClass::*f)(Args...)) {
		constexpr std::size_t template_parameter_pack_size = sizeof...(Args);

		static_assert(template_parameter_pack_size == 3, "バインドする関数の引数の数がおかしい");
		std::function<RetType(Args...)> func =
			std::bind(
				f,
				user,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3 );

		mFunctions.push_back(func);
	}

	template< class UserClass >
	void addSP(std::shared_ptr<UserClass> user, typename RetType(UserClass::*f)(Args...)) {
		constexpr std::size_t template_parameter_pack_size = sizeof...(Args);

		static_assert(template_parameter_pack_size == 3, "bindする関数の引数の数がおかしい");
		std::function<RetType(Args...)> func =
			std::bind(
				f,
				user,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3 );

		mFunctions.push_back(func);
	}

	void clear() {
		mFunctions.clear()
	}

	void exec(Args... args...) {
		for (auto d : mFunctions)
		{
			d(args...);
		}
	}
private:
	std::vector<std::function<RetType(Args...)> > mFunctions;
};


#define DECLARE_MULTICAST_DELEGATE_PARAM_0(DelegateName, ReturnType )										typedef MultiCastDelegater_Param0<ReturnType>										DelegateName;
#define DECLARE_MULTICAST_DELEGATE_PARAM_1( DelegateName, ReturnType, ParamType1 )							typedef MultiCastDelegater_Param1<ReturnType, ParamType1>							DelegateName;
#define DECLARE_MULTICAST_DELEGATE_PARAM_2( DelegateName, ReturnType, ParamType1, ParamType2)				typedef MultiCastDelegater_Param2<ReturnType, ParamType1, ParamType2>				DelegateName;
#define DECLARE_MULTICAST_DELEGATE_PARAM_3( DelegateName, ReturnType, ParamType1, ParamType2, ParamType3)	typedef MultiCastDelegater_Param3<ReturnType, ParamType1, ParamType2, ParamType3>	DelegateName;



