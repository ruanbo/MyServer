/*
 * StreamWriter.h
 *
 *  Created on: Apr 23, 2014
 *      Author: Robert
 */

#ifndef STREAMWRITER_H_
#define STREAMWRITER_H_


#include "MessageStream.h"
#include "../NonCopyable.hpp"
#include "common/TypeDef.h"

class StreamWriter : public NonCopyable
{
protected:
	MessageStream * _stream;

public:
	StreamWriter(MessageStream * stream) : _stream(stream)
	{

	}
	virtual ~StreamWriter() {}

public:
	uint32 length() { return _stream->size(); }

	void write_bytes(const void *data, size_t size) { _stream->append(data, size); }

public:
	void write_int8(int8 value){write_bytes(&value, sizeof(value)); }
	void write_uint8(int8 value){write_bytes(&value, sizeof(value)); }

	void write_int16(int8 value){write_bytes(&value, sizeof(value)); }
	void write_uint16(int8 value){write_bytes(&value, sizeof(value)); }

	void write_int32(int8 value){write_bytes(&value, sizeof(value)); }
	void write_uint32(int8 value){write_bytes(&value, sizeof(value)); }

	void write_int64(int8 value){write_bytes(&value, sizeof(value)); }
	void write_uint64(int8 value){write_bytes(&value, sizeof(value)); }

	void write_float(int8 value){write_bytes(&value, sizeof(value)); }

	void write_double(int8 value){write_bytes(&value, sizeof(value)); }

	void write_string(const std::string & value)
	{
		size_t length = value.length();
		write_uint16(length);
		write_bytes(value.data(), length);
	}

public:
	template<typename T>
	void write(const T& value)
	{
		write_bytes(&value, sizeof(value));
	}

	void write(const std::string & value)
	{
		write_string(value);
	}


	template<typename T>
	void replace(size_t position, const T & value)
	{
		_stream->replace(position, &value, sizeof(T));
	}
};


#endif /* STREAMWRITER_H_ */
