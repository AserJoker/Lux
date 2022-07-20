#ifndef _H_LUX_RESOURCE_BUFFER_
#define _H_LUX_RESOURCE_BUFFER_

#include "core/Object.hpp"

namespace lux::resource {
    class Buffer : public core::Object {
    private:
        void *_pBuffer;
        size_t _nSize;
    public:
        DEFINE_TOKEN(lux::system::Resource::Buffer);

        ~Buffer() override {
            if (_pBuffer) {
                ::operator delete(_pBuffer);
                _pBuffer = nullptr;
            }
        }

        size_t getSize() {
            return _nSize;
        }

        template<class T = void>
        T *getBuffer() {
            return (T *) _pBuffer;
        }

        std::string toString() {
            std::string result(this->getBuffer<char>(), _nSize);
            return result;
        }

        static core::Pointer <Buffer> create(size_t nSize) {
            auto buf = INJECT(Buffer);
            buf->_pBuffer = malloc(nSize); //::operator new(nSize+1);
            buf->_nSize = nSize;
            return buf;
        }
    };
} // namespace lux::resource

#endif