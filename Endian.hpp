#ifndef _PHOENIX_ENDIAN_HPP
#define _PHOENIX_ENDIAN_HPP
#include <endian.h>
#include <boost/noncopyable.hpp>
#include <stdint.h>

//static inline bool isLitterEndian()
//{
//    union{
//        char m[sizeof(int)];
//        int i;
//    }a;
//    a.i = 1;
//    return a.m[0] != 0;
//}
//
class Endian : boost::noncopyable 
{
    public:
        enum class ByteOrder {
            LE,
            BE,
        };
# if __BYTE_ORDER == __LITTLE_ENDIAN
        static ByteOrder getByteOrder()
        { return ByteOrder::LE; }
        static const char * toString(){return "LE";}
#elif __BYTE_ORDER == __BIG_ENDIAN
        static ByteOrder getByteOrder()
        { return ByteOrder::BE; }
        static const char * toString(){return "BE";}
#else
# error "no ByteOrder defined"
#endif
        static bool isLitterEndian()
        {
            return getByteOrder()==ByteOrder::LE;
        }
        static bool isBigEndian()
        {
            return getByteOrder()==ByteOrder::BE;
        }
        static uint16_t ntoh16(uint16_t u16x)
        {
            return htobe16(u16x);
        }
        static uint32_t ntoh32(uint32_t u32x)
        {
            return htobe32(u32x);
        }
        static uint64_t ntoh64(uint64_t u64x)
        {
            return htobe64(u64x);
        }
        static uint16_t hton16(uint16_t u16x)
        {
            return htobe16(u16x);
        }
        static uint32_t hton32(uint32_t u32x)
        {
            return htobe32(u32x);
        }
        static uint64_t hton64(uint64_t u64x)
        {
            return htobe64(u64x);
        }
        static uint16_t cpu2Le16(uint16_t x)
        {
            return htole16(x);
        }
        static uint32_t cpu2Le32(uint32_t x)
        {
            return htole32(x);
        }
        static uint64_t cpu2Le64(uint64_t x)
        {
            return htole64(x);
        }
        static uint16_t cpu2Be16(uint16_t x)
        {
            return htobe16(x);
        }
        static uint32_t cpu2Be32(uint32_t x)
        {
            return htobe32(x);
        }
        static uint64_t cpu2Be64(uint64_t x)
        {
            return htobe64(x);
        }
        static uint16_t le2cpu16(uint16_t x)
        {
            return le16toh(x);
        }
        static uint32_t le2cpu32(uint32_t x)
        {
            return le32toh(x);
        }
        static uint64_t le2cpu64(uint64_t x)
        {
            return le64toh(x);
        }
        static uint16_t be2cpu16(uint16_t x)
        {
            return be16toh(x);
        }
        static uint32_t be2cpu32(uint32_t x)
        {
            return be32toh(x);
        }
        static uint64_t be2cpu64(uint64_t x)
        {
            return be64toh(x);
        }
    private:
        Endian()=delete;
};

#endif  /* _PHOENIX_ENDIAN_HPP */

