#ifndef _H_LUX_CORE_OBJECT_
#define _H_LUX_CORE_OBJECT_

#include <string>
#include <fmt/format.h>
#include <exception>
#include <map>

#define RUNTIME_ERROR(msg) std::runtime_error(fmt::format("{} :\n\t at {}:{}", msg, __FILE__, __LINE__))

#define DEFINE_TOKEN(token) constexpr static const char *TOKEN = #token;

namespace lux::core
{
    class Object
    {
    private:
        unsigned _nRef;
        unsigned _nId;
        std::string _szType;

        static std::map<unsigned, Object *> _runtime;
        static unsigned createId()
        {
            static unsigned nCounter = 0;
            return ++nCounter;
        }

        friend class Container;

    protected:
        Object() : _nRef(0), _nId(Object::createId())
        {
            Object::_runtime[_nId] = this;
        }

    public:
        template <class T>
        using RELEASE = void (*)(T *obj);
        template <class T, RELEASE<T> autorelease = nullptr>
        class Pointer
        {
        private:
            Object *_pObject;

        public:
            void _addRef()
            {
                if (_pObject)
                {
                    _pObject->_nRef++;
                }
            }

            void _release()
            {
                if (_pObject)
                {
                    if (!--_pObject->_nRef)
                    {
                        if (autorelease)
                        {
                            autorelease((T *)_pObject);
                        }
                        else
                        {
                            delete _pObject;
                        }
                        _pObject = nullptr;
                    }
                }
            }
            Pointer(T *pObject = nullptr) : _pObject(pObject)
            {
                _addRef();
            }

            Pointer(const Pointer<T> &another) : _pObject(another._pObject)
            {
                _addRef();
            }

            virtual ~Pointer()
            {
                _release();
            }

            T *operator->()
            {
                return (T *)_pObject;
            }

            T &operator*()
            {
                return *(T *)_pObject;
            }

            T *week()
            {
                return (T *)_pObject;
            }

            Pointer<T> &operator=(T *pObject)
            {
                _release();
                _pObject = pObject;
                _addRef();
                return *this;
            }

            Pointer<T> &operator=(const Pointer<T> &another)
            {
                if (this != &another)
                {
                    _release();
                    _pObject = another._pObject;
                    _addRef();
                }
                return *this;
            }

            bool operator==(T *pObject)
            {
                return _pObject == pObject;
            }

            bool operator==(const Pointer<T> &another)
            {
                return _pObject == another._pObject;
            }

            bool operator!=(T *pObject)
            {
                return _pObject != pObject;
            }

            bool operator!=(const Pointer<T> &another)
            {
                return _pObject != another._pObject;
            }

            template <class K>
            Pointer<K> cast()
            {
                Pointer<K> result((K *)_pObject);
                return result;
            }
        };

        std::string &getClassName()
        {
            return _szType;
        }

        virtual std::string toString()
        {
            return fmt::format("[object {}]", getClassName());
        }

        unsigned getId()
        {
            return _nId;
        }

        virtual ~Object()
        {
            Object::_runtime.erase(_nId);
        };

        template <class T>
        static Pointer<T> select(unsigned id)
        {
            auto pair = Object::_runtime.find(id);
            if (pair != Object::_runtime.end())
            {
                return core::Pointer<T>((T *)pair->second);
            }
            return core::Pointer<T>(nullptr);
        }
    };
    template <class T, Object::RELEASE<T> release>
    class Ref : public Object
    {
    private:
        T *_value;

    public:
        Ref(T* value) : _value(value){};
        T *getValue()
        {
            return _value;
        }
        ~Ref() override{
            if(_value){
                release(_value);
            }
        }
        static core::Object::Pointer<Ref<T,release>> ref(T *value){
            return new Ref(value);
        }
    };
    std::map<unsigned, Object *> Object::_runtime;
    template <class T, Object::RELEASE<T> release = nullptr>
    using Pointer = Object::Pointer<T, release>;
} // namespace lux::core
#endif