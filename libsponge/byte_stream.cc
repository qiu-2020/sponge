#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity):_buffer(""),_capacity(capacity),_eof(false),_bytes_read(0),_bytes_written(0),_error(false){ 
//    DUMMY_CODE(capacity); 
}

size_t ByteStream::write(const string &data) {
//    DUMMY_CODE(data);
    size_t data_len = data.length();
    if(data_len <= remaining_capacity()){
        _bytes_written += data_len;
        _buffer += data;
        return data_len;
    }
    else{
        size_t b_written = remaining_capacity(); 
        _bytes_written += b_written;
        _buffer += data.substr(0,b_written);
        return b_written;
    }
    // error();   
    return 0;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
//    DUMMY_CODE(len);
    if(len <= _buffer.length())
        return _buffer.substr(0,len);
    else
        return _buffer;    
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    if(len <= _buffer.length()){
        _buffer.erase(0,len);
        _bytes_read += len;
    }    
    else{
        _bytes_read +=_buffer.length();
        _buffer.clear();
    }        
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    // DUMMY_CODE(len);
    string str_read = peek_output(len);
    pop_output(len);
    _bytes_read += str_read.length();
    return str_read;
}

void ByteStream::end_input() {
    _eof = true;
}

bool ByteStream::input_ended() const { 
    return _eof; 
}

size_t ByteStream::buffer_size() const { 
    return _buffer.length();
}

bool ByteStream::buffer_empty() const {
    // return remaining_capacity() == _capacity;
    return _buffer.length() == 0;
}

bool ByteStream::eof() const {
    return _eof && buffer_empty();
}

size_t ByteStream::bytes_written() const { 
    return _bytes_written;
}

size_t ByteStream::bytes_read() const {
    return _bytes_read;
}

size_t ByteStream::remaining_capacity() const { 
    return _capacity - _buffer.length();
}
