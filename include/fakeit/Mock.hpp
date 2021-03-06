/*
 * Copyright (c) 2014 Eran Pe'er.
 *
 * This program is made available under the terms of the MIT License.
 *
 * Created on Mar 10, 2014
 */

#ifndef Mock_h__
#define Mock_h__

#include "fakeit/DomainObjects.hpp"
#include "fakeit/MockImpl.hpp"
#include "fakeit/ActualInvocation.hpp"

namespace fakeit {
	namespace internal {
	}
using namespace fakeit;
using namespace fakeit::internal;

template<typename C, typename ... baseclasses>
class Mock : public ActualInvocationsSource {
	MockImpl<C, baseclasses...> impl;
public:
	virtual ~Mock() = default;

	static_assert(std::is_polymorphic<C>::value, "Can only mock a polymorphic type");

	Mock() : impl(Fakeit) {
	}

	explicit Mock(C &obj) :impl(Fakeit, obj) {
	}

	virtual C& get() {
		return impl.get();
	}

	C& operator()() {
		return get();
	}

	void Reset() {
		impl.reset();
	}

//	void Detach() {
//		impl.detach();
//	}

	template<class DATA_TYPE, typename ... arglist,
			class = typename std::enable_if<std::is_member_object_pointer<DATA_TYPE C::*>::value>::type>
	DataMemberStubbingRoot<C, DATA_TYPE> Stub(DATA_TYPE C::* member, const arglist&... ctorargs) {
		return impl.stubDataMember(member, ctorargs...);
	}

	template<typename R, typename T, typename ... arglist, class = typename std::enable_if<!std::is_void<R>::value && std::is_base_of<T,C>::value>::type>
	MockingContext<R, arglist...> operator [](R (T::*vMethod)(arglist...) const) {
		auto methodWithoutConstVolatile = reinterpret_cast<R (T::*)(arglist...)>(vMethod);
		return impl.stubMethod(methodWithoutConstVolatile);
	}

	template < typename R, typename T, typename... arglist, class = typename std::enable_if<!std::is_void<R>::value && std::is_base_of<T,C>::value>::type>
	MockingContext<R, arglist...> operator [](R(T::*vMethod)(arglist...) volatile) {
		auto methodWithoutConstVolatile = reinterpret_cast<R(T::*)(arglist...)>(vMethod);
		return impl.stubMethod(methodWithoutConstVolatile);
	}

	template <typename R,typename T, typename... arglist, class = typename std::enable_if<!std::is_void<R>::value && std::is_base_of<T,C>::value>::type>
	MockingContext<R, arglist...> operator [](R(T::*vMethod)(arglist...) const volatile) {
		auto methodWithoutConstVolatile = reinterpret_cast<R(T::*)(arglist...)>(vMethod);
		return impl.stubMethod(methodWithoutConstVolatile);
	}

	template <typename R, typename T, typename... arglist, class = typename std::enable_if<!std::is_void<R>::value && std::is_base_of<T,C>::value>::type>
	MockingContext<R, arglist...> operator [](R(T::*vMethod)(arglist...)) {
		return impl.stubMethod(vMethod);
	}

	template <typename R, typename T, typename... arglist, class = typename std::enable_if<std::is_void<R>::value && std::is_base_of<T,C>::value>::type>
	MockingContext<void, arglist...> operator [](R(T::*vMethod)(arglist...) const) {
		auto methodWithoutConstVolatile = reinterpret_cast<void(T::*)(arglist...)>(vMethod);
		return impl.stubMethod(methodWithoutConstVolatile);
	}

	template <typename R, typename T, typename... arglist, class = typename std::enable_if<std::is_void<R>::value && std::is_base_of<T,C>::value>::type>
	MockingContext<void, arglist...> operator [](R(T::*vMethod)(arglist...) volatile) {
		auto methodWithoutConstVolatile = reinterpret_cast<void(T::*)(arglist...)>(vMethod);
		return impl.stubMethod(methodWithoutConstVolatile);
	}

	template <typename R,typename T, typename... arglist, class = typename std::enable_if<std::is_void<R>::value && std::is_base_of<T,C>::value>::type>
	MockingContext<void, arglist...> operator [](R(T::*vMethod)(arglist...) const volatile) {
		auto methodWithoutConstVolatile = reinterpret_cast<void(T::*)(arglist...)>(vMethod);
		return impl.stubMethod(methodWithoutConstVolatile);
	}

	template <typename R, typename T, typename... arglist, class = typename std::enable_if<std::is_void<R>::value && std::is_base_of<T,C>::value>::type>
	MockingContext<void, arglist...> operator [](R(T::*vMethod)(arglist...)) {
		auto methodWithoutConstVolatile = reinterpret_cast<void(T::*)(arglist...)>(vMethod);
		return impl.stubMethod(methodWithoutConstVolatile);
	}

	DtorMockingContext dtor() {
        return impl.stubDtor();
    }

    void getActualInvocations(std::unordered_set<Invocation*>& into) const override {
		impl.getActualInvocations(into);
	}
};

}
#endif // Mock_h__
