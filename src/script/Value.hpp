#ifndef _H_LUX_VALUE_
#define _H_LUX_VALUE_
namespace lux::script {
    class Value {
    public:
        enum TYPE {
            UNDEFINED, NUMBER, STRING, BOOLEAN, FUNCTION, ARRAY, OBJECT
        };
    private:
        TYPE _type = UNDEFINED;
    public:
        void setType(TYPE type) {
            _type = type;
        }
        TYPE getType() {
            return _type;
        }
    };
} // namespace lux::script

#endif