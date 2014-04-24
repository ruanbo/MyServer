/*
 * NonCopyable.hpp
 *
 *  Created on: Apr 23, 2014
 *      Author: Robert
 */

#ifndef NONCOPYABLE_HPP_
#define NONCOPYABLE_HPP_


class NonCopyable
{
private:
	NonCopyable(const NonCopyable&);
	NonCopyable & operator = (const NonCopyable &);

protected:
	NonCopyable()
	{

	}
	~NonCopyable()
	{

	}
};



#endif /* NONCOPYABLE_HPP_ */
