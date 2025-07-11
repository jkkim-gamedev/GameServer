#pragma once

/*----------------
	SendBuffer
-----------------*/

class SendBuffer
{
public:
	BYTE*		Buffer() { return _buffer; }
	uint32		WriteSize() { return _writeSize; }

private:
	BYTE*				_buffer;
	uint32				_writeSize = 0;
};

