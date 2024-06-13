#ifndef __PROXY_HPP__
#define __PROXY_HPP__

template<typename Reference>
struct Proxy {
    Reference r;

    Reference operator->()
    { return &r; }
};

#endif //__PROXY_HPP__
