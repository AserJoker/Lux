#ifndef _H_LUX_SCRIPT_ENGINE_
#define _H_LUX_SCRIPT_ENGINE_
#include<duktape.h>
#include<fstream>
#include"Value.hpp"
#include"Undefined.hpp"
#include"SimpleValue.hpp"
#include"Object.hpp"
#include"Array.hpp"
#include <filesystem>
namespace lux::script {
	class Engine {
	private:
		duk_context* _pCtx;
		void pushObject(Object* value) {
			auto keys = value->keys();
			auto object = duk_get_top(_pCtx);
			duk_push_object(_pCtx);
			for (auto& key : keys) {
				pushValue(value->getField(key));
				duk_put_prop_string(_pCtx, object, key.c_str());
			}
		}
		void pushArray(Array* value) {
			auto length = (int)value->getLength();
			duk_uarridx_t array = duk_get_top(_pCtx);
			duk_push_array(_pCtx);
			for (duk_idx_t i = 0;i < length;i++) {
				pushValue(value->get(i));
				duk_put_prop_index(_pCtx, array, i);
			}
		}
	public:
		void pushValue(Value* value) {
			switch (value->getType()) {
			case Value::UNDEFINED:
				duk_push_undefined(_pCtx);
				break;
			case Value::NUMBER:
				duk_push_number(_pCtx, ((Number*)value)->getValue());
				break;
			case Value::STRING:
				duk_push_string(_pCtx, ((String*)value)->getValue().c_str());
				break;
			case Value::BOOLEAN:
				duk_push_boolean(_pCtx, ((Boolean*)value)->getValue());
				break;
			case Value::FUNCTION:
				duk_push_c_function(_pCtx, ((Function*)value)->getValue(), DUK_VARARGS);
				break;
			case Value::OBJECT:
				pushObject((Object*)value);
				break;
			case Value::ARRAY:
				pushArray((Array*)value);
			default:
				return;
			}
		}
		template<class T, class ...Args>
		void pushValue(T value, Args... values) {
			pushValue(value);
			pushValue(values...);
		}
		void error() {
			auto msg = duk_safe_to_stacktrace(_pCtx, -1);
			throw RUNTIME_ERROR(msg);
		}
		Engine() :_pCtx(nullptr) {
			_pCtx = duk_create_heap(nullptr, nullptr, nullptr, this, [](void* pEngine, const char* msg)->void {
				throw RUNTIME_ERROR(msg);
				});
		}
		virtual ~Engine() {
			if (_pCtx) {
				duk_destroy_heap(_pCtx);
				_pCtx = nullptr;
			}
		}
		void execFile(const std::string& filename, const std::string& source = "") {
			if (source.empty()) {
				std::ifstream file;
				file.open(filename);
				if (file.is_open()) {
					file >> std::noskipws;
					std::string src;
					while (!file.eof()) {
						char c;
						file >> c;
						if (!file.eof()) {
							src += c;
						}
					}
					if (src.length() == 0) {
						return;
					}
					execFile(filename, src);
				}
				else {
					throw RUNTIME_ERROR(fmt::format("cannot load file: {}", filename));
				}
			}
			duk_push_string(_pCtx, filename.c_str());
			duk_compile_string_filename(_pCtx, 0, source.c_str());
			if (duk_pcall(_pCtx, 0)) {
				error();
			}
		}
		template<class ...Args>
		void call(const std::string& name, Args... args) {
			auto top = duk_get_top(_pCtx);
			duk_get_global_string(_pCtx, name.c_str());
			pushValue(args...);
			if (duk_pcall(_pCtx, sizeof...(args))) {
				error();
			}
			duk_set_top(_pCtx, top);
		}
		void setValue(const std::string& name, Value* value) {
			pushValue(value);
			duk_put_global_string(_pCtx, name.c_str());
		}
		bool getString(const std::string& name, std::string* value) {
			auto val = duk_get_top(_pCtx);
			if (duk_get_global_string(_pCtx, name.c_str())) {
				*value = duk_to_string(_pCtx, val);
				duk_pop(_pCtx);
				return true;
			}
			return false;
		}
	};
}
#endif //_H_LUX_SCRIPT_ENGINE_