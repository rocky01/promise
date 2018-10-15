#ifndef _IFINISHER_HPP_
#define _IFINISHER_HPP_

#include <memory>

#include "Helpers/TypesDefinitions.hpp"

namespace prm
{

class IFinisher
{
public:
    virtual ~IFinisher(){}
    virtual void finish() =0;
};

using IFinisherUPtr = std::unique_ptr<IFinisher>;

}  // namespace prm

#endif  // _IFINISHER_HPP_

