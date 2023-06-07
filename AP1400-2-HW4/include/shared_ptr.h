#ifndef SHARED_PTR
#define SHARED_PTR
#include <memory>
using namespace std;

template<typename Point>
class SharedPtr {
 public:
  SharedPtr() = default;
  explicit SharedPtr(Point *p) noexcept: _p(p),_count(new size_t(1)) {}
  explicit SharedPtr(shared_ptr<Point> ptr) : _p(ptr.get()),_count(new size_t(ptr.use_count())) {}
  SharedPtr(SharedPtr &ptr){
    this->_p = ptr._p;
    (*ptr._count)++;
    this->_count = ptr._count;
  };
  Point &operator*() { return *_p; }
  Point *operator->() { return _p; }
  SharedPtr &operator=(SharedPtr &ptr) {
    if (ptr != this) {
      this->_p = ptr.get();
      (*ptr._count)++;
      this->_count = ptr._count;
    }
  };
  operator bool() const noexcept {return get();}
  void reset() { _p = nullptr; }
  void reset(Point *ptr) { _p = ptr; }
  Point *get() const { return _p; }
  size_t use_count() {return _count ? *_count : 0;}
  ~SharedPtr(){
    if (_count) {
      cout << "~SharedPtr\t" << (*_count) <<endl;
      (*_count)--;
      if ((*_count) == 0) {
        delete _p;
        _p = nullptr;
        delete _count;
        _count = nullptr;
      }
    }
  }
 private:
  Point *_p = nullptr;
  size_t* _count = nullptr;
};
#endif //SHARED_PTR