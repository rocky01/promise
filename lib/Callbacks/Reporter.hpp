#ifndef _REPORTER_HPP_
#define _REPORTER_HPP_

#include <utility>
#include <tuple>

#include "Helpers/TypesDefinitions.hpp"

namespace prm
{
enum class Is
{
    Rejected,
    Resolved
};

template<typename ResolveArgT, typename ErrorT>
class Reporter
{
public:
    Reporter(const ErrorT error, bool) // bool is only to distinguish constructors in case ResolveArgT and ErrorT has the same types
        : error_(error)
        , isResolved_(false)
    {}

    Reporter(const ResolveArgT resolveArg)
        : resolveArg_(resolveArg)
        , isResolved_(true)
    {}

    bool isResolved()
    {
        return isResolved_;
    }

    bool isRejected()
    {
        return !isResolved_;
    }

    ErrorT getError()
    {
        return error_;
    }

    ResolveArgT getResolveArg()
    {
        return resolveArg_;
    }

private:
     ErrorT error_;
     ResolveArgT resolveArg_;
     const bool isResolved_;
};

template<typename ResolveArgT>
class Reporter<ResolveArgT, void>
{
public:
    Reporter()
        : isResolved_(false)
    {}

    Reporter(const ResolveArgT resolveArg)
        : resolveArg_(resolveArg)
        , isResolved_(true)
    {}

    bool isResolved()
    {
        return isResolved_;
    }

    bool isRejected()
    {
        return !isResolved_;
    }

    ResolveArgT getResolveArg()
    {
        return resolveArg_;
    }

private:
     ResolveArgT resolveArg_;
     const bool isResolved_;
};

template<typename ResolveArgT>
class Reporter<ResolveArgT, ErrorTypeUndefined>
{
public:
    Reporter(const ResolveArgT resolveArg)
        : resolveArg_(resolveArg)
        , isResolved_(true)
    {}

    bool isResolved()
    {
        return isResolved_;
    }

    bool isRejected()
    {
        return !isResolved_;
    }

    ResolveArgT getResolveArg()
    {
        return resolveArg_;
    }

private:
     const ResolveArgT resolveArg_;
     const bool isResolved_;
};

template<typename ErrorT>
class Reporter<void, ErrorT>
{
public:
    Reporter(const ErrorT error)
        : error_(error)
        , isResolved_(false)
    {}

    Reporter()
        : isResolved_(true)
    {}

    bool isResolved()
    {
        return isResolved_;
    }

    bool isRejected()
    {
        return !isResolved_;
    }

    ErrorT getError()
    {
        return error_;
    }

private:
     ErrorT error_;
     const bool isResolved_;
};

template<>
class Reporter<void, void>
{
public:
    Reporter(const Is is)
        : isResolved_(is == Is::Resolved)
    {}

    bool isResolved()
    {
        return isResolved_;
    }

    bool isRejected()
    {
        return !isResolved_;
    }

private:
     const bool isResolved_;
};

template<>
class Reporter<void, ErrorTypeUndefined>
{
public:
    Reporter()
        : isResolved_(true)
    {}

    bool isResolved()
    {
        return isResolved_;
    }

    bool isRejected()
    {
        return !isResolved_;
    }

private:
     const bool isResolved_;
};

template<typename Error>
class Reporter<ResolveArgTypeUndefined, Error>
{
public:
    Reporter(const Error error)
        : error_(error)
        , isResolved_(false)
    {}

    bool isResolved()
    {
        return isResolved_;
    }

    bool isRejected()
    {
        return !isResolved_;
    }

    Error getError()
    {
        return error_;
    }

private:
     const Error error_;
     bool isResolved_;
};

template<>
class Reporter<ResolveArgTypeUndefined, void>
{
public:
    Reporter()
        : isResolved_(false)
    {}

    bool isResolved()
    {
        return isResolved_;
    }

    bool isRejected()
    {
        return !isResolved_;
    }

private:
     const bool isResolved_;
};

}  // namespace prm

#endif  // _REPORTER_HPP_
