#ifndef UNIQUE_PTR
#define UNIQUE_PTR
#include <memory>
using namespace std;

template<typename Point>
class UniquePtr {
 public:
  UniquePtr() : _p(nullptr){}
  explicit UniquePtr(Point *p) noexcept: _p(p) {}
  explicit UniquePtr(unique_ptr<Point> ptr) : _p(ptr.release()) {}
  UniquePtr(const UniquePtr &ptr) = delete;
  Point &operator*() { return *_p; }
  Point *operator->() { return _p; }
  UniquePtr &operator=(const UniquePtr &ptr) = delete;
  operator bool() const noexcept { return get() != nullptr; }
  void reset() {
    delete _p;
    _p = nullptr;
  }
  void reset(Point *ptr) {
    delete _p;
    _p = ptr;
  }
  Point* release() {
    Point* p = _p;
    _p = 0;
    return p;
  }
  Point *get() const { return _p; }
  ~UniquePtr() noexcept {
    delete _p;
    _p = nullptr;
  }
 private:
  Point *_p = nullptr;
};
#endif //UNIQUE_PTR