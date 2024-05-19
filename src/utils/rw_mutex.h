#include <condition_variable>
#include <mutex>

class ReadWriteLock {
public:
  ReadWriteLock() : readers(0), writers(0), waiting_writers(0) {}

  // 读锁
  void lock_shared() {
    std::unique_lock<std::mutex> lock(mutex_);
    while (writers > 0 || waiting_writers > 0) {
      cv_reader_.wait(lock);
    }
    ++readers;
  }

  // 读解锁
  void unlock_shared() {
    std::unique_lock<std::mutex> lock(mutex_);
    --readers;
    if (readers == 0) {
      cv_writer_.notify_one();
    }
  }

  // 写锁
  void lock() {
    std::unique_lock<std::mutex> lock(mutex_);
    ++waiting_writers;
    while (readers > 0 || writers > 0) {
      cv_writer_.wait(lock);
    }
    --waiting_writers;
    ++writers;
  }

  // 写锁
  bool try_lock() {
    std::unique_lock<std::mutex> lock(mutex_);
    if (readers > 0 || writers > 0) {
      return false;
    }
    ++writers;
    return true;
  }

  // 写解锁
  void unlock() {
    std::unique_lock<std::mutex> lock(mutex_);
    --writers;
    if (waiting_writers > 0) {
      cv_writer_.notify_one();
    } else {
      cv_reader_.notify_all();
    }
  }

private:
  std::mutex mutex_;
  std::condition_variable cv_reader_;
  std::condition_variable cv_writer_;
  int readers;
  int writers;
  int waiting_writers;
};
