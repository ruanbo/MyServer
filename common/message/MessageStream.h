/*
 * MessageStream.h
 *
 *  Created on: Apr 23, 2014
 *      Author: Robert
 */

#ifndef MESSAGESTREAM_H_
#define MESSAGESTREAM_H_

#include <cstddef>
#include <string>


class MessageStream
{
private:
	std::string _buffer;

public:
	MessageStream(size_t size=1024)
	{
		_buffer.reserve(size);
	}
	MessageStream(const char* data, size_t size) : _buffer(data, size)
	{
	}
	~MessageStream()
	{
	}

	void swap(MessageStream & rhs)
	{
		_buffer.swap(rhs._buffer);
	}

	size_t size()
	{
		return _buffer.size();
	}

public:
	char *begin()
	{
		return &*_buffer.begin();
	}
	std::string buffer()
	{
		return _buffer;
	}

	void append(const void *data, size_t length)
	{
		_buffer.append((const char *)data, length);
	}

	size_t read(size_t position, void *out, size_t length)
	{
		if(position + length > size())
		{
			return 0;
		}
		_buffer.copy((char *)out, length, position);
		return length;
	}

	size_t read(size_t position, std::string &out, size_t length)
	{
		if(position + length > size())
		{
			return 0;
		}
		out.append(_buffer, position, length);

		return length;
	}

	void replace(size_t position, const void *data, size_t length)
	{
		if(position + length > size())
		{
			return;
		}
		char *char_data = (char*)data;
		char *data_begin = begin() + position;

		std::copy(char_data, char_data+length, data_begin);
	}
};




#endif /* MESSAGESTREAM_H_ */
