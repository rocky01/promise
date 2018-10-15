#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <functional>
#include <queue>

namespace sch {

enum class Do
{
    Resolve,
    Reject
};

using TaskT = std::function<void(Do)>;

class Scheduler {
public:
  void addNextTask(TaskT task);
  void executeNextTask(Do doResolved);
  void executeNextTask();

private:
  std::queue<TaskT> queue_;
};

template <typename ResolverT, typename RejectorT, typename ResolveArgT, typename RejectArgT>
TaskT task(ResolverT resolve, RejectorT reject, ResolveArgT resolveArg, RejectArgT rejectArg)
{
  return [resolve, reject, resolveArg, rejectArg](Do doResolve) {
    if (Do::Resolve == doResolve) {
      return resolve(resolveArg);
    }
    return reject(rejectArg);
  };
}

template <typename ResolverRejectorT, typename ResolveRejectArgT>
TaskT task(ResolverRejectorT resolveReject, ResolveRejectArgT resolverejectArg)
{
  return [resolveReject, resolverejectArg](Do doResolve) { resolveReject(resolverejectArg); };
}

template <typename ResolverRejectorT>
TaskT task(ResolverRejectorT resolveReject)
{
  return [resolveReject](Do doResolve) { resolveReject(); };
}
} // namespace sch

#endif // SCHEDULER_H
