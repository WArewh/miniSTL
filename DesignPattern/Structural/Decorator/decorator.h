#ifndef STRUCTURAL_DECORATOR_DECORATOR_H_
#define STRUCTURAL_DECORATOR_DECORATOR_H_

// 以前接口


class Stream {
public:
    virtual char read(int number);
    virtual void seek();
    virtual void write(char ch);
};

class FileStream : public Stream {
public:
    virtual char read(int number);
    virtual void seek();
    virtual void write(char ch);
};

class NetworkStream : public Stream {
public:
    virtual char read(int number);
    virtual void seek();
    virtual void write(char ch);
};

//...

// End

// 加密拓展

class DecoratorStream {
public:
    DecoratorStream(Stream*);

protected:
    Stream* m_stream;
};

class CryptoStream : public DecoratorStream {
public:
    virtual char read(int number);
    virtual void seek();
    virtual void write(char ch);
};

char CryptoStream::read(int number) {
    //加密
    char ch = m_stream->read(number);
    //加密
    return ch;
}

//...

#endif