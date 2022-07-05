#ifndef _H_LUX_CORE_OBJECT_
#define _H_LUX_CORE_OBJECT_

#include<string>
#include<fmt/format.h>
#include<exception>

#define RUNTIME_ERROR(msg) std::runtime_error(fmt::format("{} :\n\t at {}:{}",msg,__FILE__,__LINE__))

#define DEFINE_TOKEN(token) constexpr static const char* TOKEN = #token;

namespace lux::core {
    class Object {
    private:
        unsigned _nRef;
        std::string _szType;

        friend class Container;

    protected:
        Object() : _nRef(0) {}

    public:
        std::string& getClassName() {
            return _szType;
        }

        virtual std::string toString() {
            return fmt::format("[object {}]", getClassName());
        }

        template<class T>
        class Pointer {
        private:
            Object* _pObject;

            void _addRef() {
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
        public:
            explicit Pointer(T* pObject = nullptr) :_pObject(pObject) {
                _addRef();
            }

            Pointer(const Pointer<T>& another) :_pObject(another._pObject) {
                _addRef();
            }

            virtual ~Pointer() {
                _release();
            }

            T* operator ->() {
                return (T*)_pObject;
            }

            T& operator*() {
                return *(T*)_pObject;
            }

            T* week() {
                return (T*)_pObject;
            }

            Pointer<T>& operator = (T* pObject) {
                _release();
                _pObject = pObject;
                _addRef();
                return *this;
            }

            Pointer<T>& operator = (const Pointer<T>& another) {
                if (this != &another) {
                    _release();
                    _pObject = another._pObject;
                    _addRef();
                }
                return *this;
            }

            bool operator == (T* pObject) {
                return _pObject == pObject;
            }

            bool operator == (const Pointer<T>& another) {
                return _pObject == another._pObject;
            }

            bool operator != (T* pObject) {
                return _pObject != pObject;
            }

            bool operator != (const Pointer<T>& another) {
                return _pObject != another._pObject;
            }

            template<class K>
            Pointer<K> cast() {
                Pointer<K> result((K*)_pObject);
                return result;
            }
        };

        virtual ~Object() = default;
    };

    template<class T> using Pointer = Object::Pointer<T>;
} // namespace lux::core
#endif