#ifndef _IEXECUTORANDREJECTOR_HPP_
#define _IEXECUTORANDREJECTOR_HPP_

#include <memory>

#include "IExecutor.hpp"
#include "IRejector.hpp"

namespace prm
{

template<typename ExecuteArgT, typename ErrorT>
class IExecutorAndRejector : public IExecutor<ExecuteArgT>, public IRejector<ErrorT>
{
public:
    virtual ~IExecutorAndRejector(){}
};

template<typename ExecuteArgT, typename ErrorT>
using IExecutorAndRejectorUPtr = std::unique_ptr<IExecutorAndRejector<ExecuteArgT, ErrorT>>;

}  // namespace prm

#endif  // _IEXECUTORANDREJECTOR_HPP_

