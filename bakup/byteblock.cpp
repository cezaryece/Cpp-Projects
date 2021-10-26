/**
* A block buffer type that can be used with std::copy() and
istream_iterators without
* having to write a special form of copy or an istream_iterator.
*/

#include "byteblock.h"

ByteBlock::ByteBlock() : m_bytesRead(0), m_fileSize(-1), m_totalRead(0) {
}

std::istream& operator >> (std::istream& stream, ByteBlock& block) {
    if (block.m_fileSize == -1) {
        stream.seekg(0, std::ios::end);
        block.m_fileSize = stream.tellg();
        stream.seekg(0, std::ios::beg);
    }
    std::size_t leftToRead = block.m_fileSize - block.m_totalRead;
    if (leftToRead) {
        stream.read((char*)block.m_block, std::min(sizeof(block.m_block), leftToRead));
        block.m_bytesRead = stream.gcount();
        block.m_totalRead += block.m_bytesRead;
    }
    else {
        stream.setstate(std::ios_base::eofbit | std::ios_base::badbit);
    }
    return stream;
}

std::ostream& operator << (std::ostream& stream, const ByteBlock& block) {
    stream.write((char*)block.m_block, block.m_bytesRead);
    return stream;
}
