#ifndef _H_LUX_CORE_OBJECT_
#define _H_LUX_CORE_OBJECT_

#include "util.hpp"
#include <exception>
#include <fmt/format.h>
#include <map>
#include <string>

namespace lux::core {
  class Object {
  private:
    unsigned _nRef;
    unsigned _nId;
    std::string _szType;

    static std::map<unsigned, Object*> _runtime;
    static unsigned createId() {
      static unsigned nCounter = 0;
      return ++nCounter;
    }

    friend class Container;

  protected:
    Object() : _nRef(0), _nId(Object::createId()) {
      Object::_runtime[_nId] = this;
    }

  public:
    template <class T> class Pointer {
    private:
      Object* _pObject;

    protected:
      virtual T* get() { return (T*)this->_pObject; }
      virtual void set(Object* obj) { this->_pObject = obj; }

    public:
      void _addRef() {
        auto _pObject = get();
        if (_pObject) {
          _pObject->_nRef++;
        }
      }

      void _release() {
        if (_pObject) {
          if (!--_pObject->_nRef) {

            delete _pObject;
            _pObject = nullptr;
          }
        }
      }
      unsigned _getRef(){
        return _pObject?_pObject->_nRef:0;
      }
      Pointer(T* pObject = nullptr) : _pObject(pObject) { _addRef(); }

      Pointer(const Pointer<T>& another) : _pObject(another._pObject) {
        _addRef();
      }

      virtual ~Pointer() { _release(); }

      T* operator->() { return get(); }

      T& operator*() { return *get(); }

      T* week() { return (T*)get(); }

      Pointer<T>& operator=(T* pObject) {
        _release();
        set(pObject);
        _addRef();
        return *this;
      }

      Pointer<T>& operator=(const Pointer<T>& another) {
        if (this != &another) {
          _release();
          set(another._pObject);
          _addRef();
        }
        return *this;
      }

      bool operator==(T* pObject) { return get() == pObject; }

      bool operator==(const Pointer<T>& another) {
        return get() == another._pObject;
      }

      bool operator!=(T* pObject) { return get() != pObject; }

      bool operator!=(const Pointer<T>& another) {
        return get() != another._pObject;
      }

      template <class K> Pointer<K> cast() {
        Pointer<K> result((K*)_pObject);
        return result;
      }
    };

    std::string& getClassName() { return _szType; }

    virtual std::string toString() {
      return fmt::format("[object {}]", getClassName());
    }

    unsigned getId() { return _nId; }

    virtual ~Object() { Object::_runtime.erase(_nId); };

    template <class T> static Object::Pointer<T> select(unsigned id) {
      auto pair = Object::_runtime.find(id);
      if (pair != Object::_runtime.end()) {
        return core::Object::Pointer<T>((T*)pair->second);
      }
      return core::Object::Pointer<T>(nullptr);
    }
  };
  template <class T> using RELEASE = void (*)(T* obj);
  template <class T, RELEASE<T> release = nullptr> class Ref : public Object {
  private:
    T* _value;

  public:
    Ref(T* value) : _value(value) {};
    T* getValue() { return _value; }
    ~Ref() override {
      if (_value) {
        if (release) {
          release(_value);
        }
        else {
          delete _value;
        }
      }
    }
    static core::Object::Pointer<Ref<T, release>> ref(T* value = new T()) {
      return new Ref(value);
    }
  };
  std::map<unsigned, Object*> Object::_runtime;
  template <class T> using Pointer = Object::Pointer<T>;
} // namespace lux::core
#endif