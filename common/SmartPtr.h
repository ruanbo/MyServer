/*
 * smartcount.h
 *
 *  Created on: Apr 11, 2014
 *      Author: root
 */

#ifndef SMARTCOUNT_H_
#define SMARTCOUNT_H_

#include <sys/types.h>
#include <cstdlib>

class smart_count
{
private:
	u_int32_t _ref_count;

public:
	smart_count()
	{
			_ref_count = 0;
	}
	virtual ~smart_count()
	{

	}

	inline u_int32_t inc_ref_count()
	{
		return ++_ref_count;
	}

	inline u_int32_t dec_ref_count()
	{
		return --_ref_count;
	}

	inline u_int32_t get_ref_count()
	{
		return _ref_count;
	}
};

inline void add_smart_ptr_ref_count(smart_count* p)
{
	p->inc_ref_count();
}

inline void dec_smart_ptr_ref_count(smart_count* p)
{
	p->dec_ref_count();

	if(p->get_ref_count() == 0)
	{
		delete p;
	}
}




template<class T>
class smart_ptr
{
private:
	typedef smart_ptr this_type;
	typedef T element_type;

public:
	T* _p;

public:
	smart_ptr()
	{
		_p = NULL;
	}

	smart_ptr(element_type *p)
	{
		_p = p;
		if(p != NULL)
		{
			add_smart_ptr_ref_count(_p);
		}
	}
	smart_ptr(smart_ptr const &rhs)
	{
		_p = rhs._p;
		if(_p != NULL)
		{
			add_smart_ptr_ref_count(_p);
		}
	}
	~smart_ptr()
	{
		if(_p != NULL)
		{
			dec_smart_ptr_ref_count(_p);
		}
	}

	smart_ptr & operator = (smart_ptr const &rhs)
	{
		this_type(rhs).swap(*this);
		return *this;
	}
	smart_ptr & operator = (T *rhs)
	{
		this_type(rhs).swap(*this);
		return *this;
	}

public:
	T & operator * ()const
	{
		return *_p;
	}
	T * operator ->()const
	{
		return _p;
	}
	bool operator ! ()const
	{
		return _p == NULL;
	}
	element_type* get()
	{
		return _p;
	}
	void swap(smart_ptr &rhs)
	{
		element_type *temp;
		temp = _p;

		_p = rhs._p;
		rhs._p = temp;
	}

};

#endif /* SMARTCOUNT_H_ */
