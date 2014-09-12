#ifndef _PHOENIX_MEMBLOCK_HPP
#define _PHOENIX_MEMBLOCK_HPP

#include <string.h>
#include <functional>

class MemBlock 
{
    typedef unsigned int size_t;
    typedef unsigned int uint;
    typedef unsigned long offset_t;
    typedef std::function<bool(void*,size_t)> callback_t;

    MemBlock(char *data, size_t size)
        :pData(data), size(size)
    {
        this->off = 0;
    }
    MemBlock(const MemBlock &mb)
    {
        this->size  = mb.size;
        this->off   = mb.off;
        this->pData = new char[size];
        memcpy(pData, mb.pData, off);
    }
    MemBlock(MemBlock &&mb)
    {
        char *tmp   = mb.pData;
        mb.pData    = nullptr;
        this->size  = mb.size;
        this->off   = mb.off;
        this->pData = tmp;
    }
    MemBlock & operator = (const MemBlock &mb)
    {
        this->size  = mb.size;
        this->off   = mb.off;
        this->pData = new char[size];
        memcpy(pData, mb.pData, off);

        return *this;
    }
    MemBlock & operator = (MemBlock && mb)
    {
        char *tmp   = mb.pData;
        mb.pData    = nullptr;
        this->size  = mb.size;
        this->off   = mb.off;
        delete this->pData;
        this->pData = tmp;
        return *this;
    }
    void setFlushFn(const callback_t &fn)
    {
        this->flushFn = fn;
    }
    void setFlushFn(callback_t &&fn)
    {
        this->flushFn = fn;
    }
    unsigned long availBytes()const
    {
        return size - off;
    }
    size_t dataBytes()const
    {
        return this->off;
    }
    size_t getOffset()const
    {
        return this->off;
    }
    void setOffset(size_t off)
    {
        this->off = off;
    }
    uint append(char *s, size_t len)
    {
        if(availBytes()>len){
            memcpy(getPtr(), s, len);
            off += len;
            return 0;
        }
        // may call flush callback
        uint left = len - availBytes();
        memcpy(getPtr(), s, availBytes());
        bool b=true;
        if(flushFn)
            b = this->flushFn(this->pData, this->size);
        if(b)
            off += availBytes();
        return left;
    }
    void flush()
    {
        if(this->off > 0 && this->flushFn)
            this->flushFn(this->pData, this->off);
        this->off = 0;
    }
    void reset()
    {
        this->off   = 0;
    }
    void reset(char *buffer, size_t len)
    {
        this->pData = buffer;
        this->size  = len;
        this->off   = 0;
    }

    private:
    char * getPtr()const
    {
        return pData+off;
    }
    private:
        char *pData;
        size_t size;
        offset_t off;
        callback_t flushFn;
};

#endif /* _PHOENIX_MEMBLOCK_HPP */
