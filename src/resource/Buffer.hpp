#ifndef _H_LUX_RESOURCE_
#define _H_LUX_RESOURCE_
#include "core/Object.hpp"
namespace lux::resource
{
    class Buffer : public core::Object
    {
    private:
        void *_pBuf;
        size_t _nSize;

    public:
        DEFINE_TOKEN(lux::resource::Buffer);
        size_t getBufferSize(){
            return _nSize;
        }
        void *getBufferData(){
            return _pBuf;
        }
        bool write(void *buf,size_t offset = 0,size_t len = 0){
            auto length = len==0?_nSize-offset:len;
            if(offset+length>_nSize){
                return false;
            }
            uint8_t *target = (uint8_t *)_pBuf + offset;
            uint8_t *source = (uint8_t *)buf;
            while(length>0){
                *target++ = *source++;
                length--;
            }
            return true;
        }
        bool read(void *buf,size_t offset = 0,size_t len = 0){
            auto length = len==0?_nSize-offset:len;
            if(offset+length>_nSize||length<0){
                return false;
            }
            uint8_t *source = (uint8_t *)_pBuf + offset;
            uint8_t *target = (uint8_t *)buf;
            while(length>0){
                *target++ = *source++;
                length--;
            }
            return true;
        }
        ~Buffer() override{
            if(_pBuf){
                ::operator delete(_pBuf);
                _pBuf = nullptr;
            }
        }
        static core::Pointer<Buffer> create(size_t size){
            auto buf = INJECT(Buffer);
            buf->_pBuf = ::operator new(size);
            buf->_nSize = size;
            return buf;
        }
    };
} // namespace lux::resource

#endif