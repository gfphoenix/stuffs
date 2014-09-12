#ifndef _PHOENIX_IPADDR_HPP
#define _PHOENIX_IPADDR_HPP
#include <endian.h>
#include <stdint.h>
#include <iostream>

class IPAddr 
{
    public:
        // construct "a.b.c.d" ipv4
        IPAddr(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
        {
        }
        IPAddr(const std::string &ip)
        {
        }
    private:
};

#endif  /* _PHOENIX_IPADDR_HPP */

