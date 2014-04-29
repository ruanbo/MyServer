/*
 * StreamReader.h
 *
 *  Created on: Apr 29, 2014
 *      Author: Robert
 */

#ifndef STREAMREADER_H_
#define STREAMREADER_H_

#include "MessageStream.h"
#include "../NonCopyable.hpp"
#include "common/TypeDef.h"

class StreamReader : public NonCopyable
{
protected:
	size_t _read;
	MessageStream *_stream;

public:
	StreamReader(MessageStream *stream) : _read(0), _stream(stream)
	{

	}
	virtual ~StreamReader()
	{

	}
private:
	void step(size_t step)
	{
		_read += step;
	}

	size_t read_bytes(void *out, size_t size)
	{
		size_t len = _stream->read(_read, out, size);
		step(len);
		return len;
	}

public:
	int8 read_int8()
	{
		int8 value = 0;
		read_bytes(&value, sizeof(value));
		return value;
	}

	int16 read_int16()
	{
		int16 value = 0;
		read_bytes(&value, sizeof(value));
		return value;
	}
	int32 read_int32()
	{
		int32 value = 0;
		read_bytes(&value, sizeof(value));
		return value;
	}
	int64 read_int64()
	{
		int64 value = 0;
		read_bytes(&value, sizeof(value));
		return value;
	}

	uint8 read_uint8()
	{
		uint8 value = 0;
		read_bytes(&value, sizeof(value));
		return value;
	}
	uint16 read_uint16()
	{
		uint16 value;
		read_bytes(&value, sizeof(value));
		return value;
	}
	uint32 read_uint32()
	{
		uint32 value;
		read_bytes(&value, sizeof(value));
		return value;
	}
	uint64 read_uint62()
	{
		uint32 value;
		read_bytes(&value, sizeof(value));
		return value;
	}

	float read_float()
	{
		float value = 0;
		read_bytes(&value, sizeof(value));
		return value;
	}
	double read_double()
	{
		double value;
		read_bytes(&value, sizeof(value));
		return value;
	}

	std::string read_string()
	{
		uint16 str_len = read_uint16();
		std::string value;
		size_t len = _stream->read(_read, value, str_len);

		step(len);

		return value;
	}

public:
	template<typename T>
	void read(T& v)
	{
		read_bytes(&v, sizeof(v));
	}
	void read(std::string& v)
	{
		v = read_string();
	}

	size_t left_size()const
	{
		return _stream->size() - _read;
	}
};




#endif /* STREAMREADER_H_ */
