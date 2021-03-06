/*
 * Finally.hpp
 * Copyright (c) 2014 Eran Pe'er.
 *
 * This program is made available under the terms of the MIT License.
 * 
 * Created on Aug 30, 2014
 */
#ifndef FINALLY_HPP_
#define FINALLY_HPP_

#include <functional>

namespace fakeit {

class Finally {
private:
	std::function<void()> _finallyClause;
	Finally(const Finally &);
	Finally& operator=(const Finally &);
public:
	explicit Finally(std::function<void()> f) :
			_finallyClause(f) {
	}

	~Finally() {
		_finallyClause();
	}
};
}



#endif /* FINALLY_HPP_ */
