#ifndef BYTEBLOCK_H
#define BYTEBLOCK_H

/**
* A block buffer type that can be used with std::copy() and
istream_iterators without
* having to write a special form of copy or an istream_iterator.
*/
#include <iostream>

class ByteBlock
{
public:
    ByteBlock();

private:
    unsigned char m_block[10240];
    int m_bytesRead;
    long m_fileSize;
    long m_totalRead;
    friend std::istream& operator >> (std::istream& stream, ByteBlock& byte);
    friend std::ostream& operator << (std::ostream& stream, const ByteBlock& byte);
};

#endif // BYTEBLOCK_H
