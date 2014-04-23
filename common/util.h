/*
 * util.h
 *
 *  Created on: Apr 18, 2014
 *      Author: Robert
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <map>

//template<typename T>
//struct auto_container
//{
//	typedef typename T::iterator iterator;
//	typedef typename T::const_iterator const_iterator;
//};

template<class Key, class ValueType>
ValueType find_container(const std::map<Key, ValueType>& container, const Key& key, const ValueType& default_value)
{
	typedef typename std::map<Key, ValueType>::const_iterator const_iterator;
	const_iterator iter = container.find(key);

	if(iter != container.end())
	{
		return iter->second;
	}

	return default_value;
}

//template<typename T, typename U, typename V>
//U find_container(const std::map<T, U, V> &container, const T &key, const U &defval)
//{
//	typedef typename std::map<T, U, V>::const_iterator iterator;
//	iterator iter = container.find(key);
//	if (iter != container.end())
//	{
//		return iter->second;
//	}
//	return defval;
//}


#endif /* UTIL_H_ */
