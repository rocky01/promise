#include "Scheduler.hpp"

namespace sch {

void Scheduler::addNextTask(TaskT task)
{
    queue_.push(task);
}

void Scheduler::executeNextTask(Do doResolved)
{
    queue_.front()(doResolved);
    queue_.pop();
}

void Scheduler::executeNextTask()
{
    queue_.front()(Do::Resolve);
    queue_.pop();
}

} // namespace sch
