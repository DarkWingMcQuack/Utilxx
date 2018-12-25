#pragma once

#include <boost/fiber/condition_variable.hpp>
#include <boost/fiber/mutex.hpp>
#include <mutex>

class FiberReadWriteLock
{
public:
    auto readLock()
    {
        std::unique_lock lock{mutex_};
        waiting_readers_.wait(lock,
                              [this] {
                                  return !active_writer_
                                      && queued_writers_ == 0;
                              });
        ++active_readers_;
    }

    auto readUnlock()
    {
        std::unique_lock lock{mutex_};
        --active_readers_;
        if(active_readers_ == 0 && queued_writers_ > 0) {
            lock.unlock();
            waiting_writers_.notify_one();
        }
    }

    auto writeLock()
    {
        std::unique_lock lock{mutex_};
        ++queued_writers_;
        waiting_writers_.wait(lock,
                              [this] {
                                  return !active_writer_
                                      && active_readers_ == 0;
                              });
        --queued_writers_;
        active_writer_ = true;
    }

    auto writeUnlock()
    {
        std::unique_lock lock{mutex_};

        if(queued_writers_ > 0) {
            lock.unlock();
            waiting_writers_.notify_one();
        } else {
            active_writer_ = false;
            lock.unlock();
            waiting_readers_.notify_all();
        }
    }

private:
    boost::fibers::mutex mutex_;
    boost::fibers::condition_variable waiting_readers_;
    boost::fibers::condition_variable waiting_writers_;

    int active_readers_ = 0;
    int queued_writers_ = 0;
    bool active_writer_ = false;
};
