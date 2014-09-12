#ifndef _PHOENIX_ERROR_HPP
#define _PHOENIX_ERROR_HPP
#include <string>
#include <boost/noncopyable.hpp>
class Error : boost::noncopyable {
    public:
    Error(std::string &error)
        :err_(error){}
    Error(std::string &&error)
        :err_(error){}

    const std::string& toString()const
    {
        return err_;
    }
    private:
    std::string err_;
};

#endif /* _PHOENIX_ERROR_HPP */

