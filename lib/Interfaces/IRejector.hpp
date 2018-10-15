#ifndef _IREJECTOR_HPP_
#define _IREJECTOR_HPP_

#include <memory>

#include "Helpers/TypesDefinitions.hpp"

namespace prm
{

template<typename ErrorT>
class IRejector
{
public:
    virtual ~IRejector(){}
    virtual void reject(ErrorT error) =0;
};

template<>
class IRejector<void>
{
public:
    virtual ~IRejector(){}
    virtual void reject() =0;
};

template<typename ErrorT>
using IRejectorUPtr = std::unique_ptr<IRejector<ErrorT>>;

}  // namespace prm

#endif  // _IREJECTOR_HPP_

