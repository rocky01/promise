#ifndef _IEXECUTOR_HPP_
#define _IEXECUTOR_HPP_

#include <memory>

#include "Helpers/TypesDefinitions.hpp"

namespace prm
{

template<typename ExecuteArgT>
class IExecutor
{
public:
    virtual ~IExecutor(){}
    virtual void execute(ExecuteArgT executeArg) =0;
};

template<>
class IExecutor<void>
{
public:
    virtual ~IExecutor(){}
    virtual void execute() =0;
};

template<typename ExecuteArgT>
using IExecutorUPtr = std::unique_ptr<IExecutor<ExecuteArgT>>;

}  // namespace prm

#endif  // _IEXECUTOR_HPP_

