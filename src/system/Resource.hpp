#ifndef _H_LUX_SYSTEM_RESOURCE_
#define _H_LUX_SYSTEM_RESOURCE_
#include <SDL_image.h>
#include <map>
#include <cjson/cJSON.h>
#include <fstream>
#include <cstdio>
#include "core/EventEmitter.hpp"
#include "Native.hpp"
#include "resource/Buffer.hpp"
#include "Script.hpp"
#define ADD_FUNC(obj,name) _ADD_FUNC(obj,name,Resource)
namespace lux::system {
	class Resource :public core::EventEmitter {
	private:
		std::map<std::string,std::string> _manifest;
		std::map<std::string,core::Pointer<resource::Buffer>> _cache;

		static duk_idx_t asset(duk_context *ctx){
			auto R = INJECT(Resource);
			CHECK_ARG_LEN(2,"asset need 2 argument");
			CHECK_ARG_STRING(0,"asset need 2 string argument");
			CHECK_ARG_STRING(1,"asset need 2 string argument");
			auto token = duk_get_string(ctx,0);
			std::string type = duk_get_string(ctx,1);
			try{
				auto buf = R->load(token);
				if(type=="string"){
					char *str = new char[buf->getBufferSize()+1];
					str[buf->getBufferSize()] = 0;
					buf->read(str);
					duk_push_string(ctx,str);
					delete[] str;
				}else if(type=="buffer"){
					auto target = duk_push_buffer(ctx,buf->getBufferSize(),0);
					buf->read(target);
				}else{
					duk_reference_error(ctx,"unknown resource Type");
				}
			}catch(std::exception& exp){
				std::cout<<exp.what()<<std::endl;
				duk_push_undefined(ctx);
			}
			return 1;
		}

		void onInit() {
			IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF );
		}
		void onQuit() {
			IMG_Quit();
		}
		void resolveObject(cJSON* obj){
			cJSON *child = obj->child;
			while(child){
				if(cJSON_IsObject(child)){
					resolveObject(child,child->string);
				}else{
					if(cJSON_IsString(child)){
						_manifest[child->string] = child->valuestring;
					}
				}
				child = child->next;
			}
		}
		void resolveObject(cJSON* obj,const std::string& current){
			
			cJSON *child = obj->child;
			while(child){
				if(cJSON_IsObject(child)){
					resolveObject(child,current+"::"+child->string);
				}else{
					if(cJSON_IsString(child)){
						_manifest[current+"::"+child->string] = child->valuestring;
					}
				}
				child = child->next;
			}
		}
	protected:
		void on(core::EventEmitter* emitter, const std::string& event) override {
			if (event == Native::EVENT_INIT) {
				onInit();
			}
			else if (event == Native::EVENT_QUIT) {
				onQuit();
			}
		}
	public:
		DEFINE_TOKEN(lux::system::Resource);
		Resource() {
			auto native = INJECT(Native);
			native->addEventListener(Native::EVENT_INIT, this);
			native->addEventListener(Native::EVENT_QUIT, this);
			std::ifstream file;
			file.open("assets/manifest.json");
			if(file.is_open()){
				std::string source;
				file>>std::noskipws;
				while(!file.eof()){
					char c;
					file>>c;
					if(!file.eof()){
						source+=c;
					}
				}
				file.close();
				cJSON *root = cJSON_Parse(source.c_str());
				resolveObject(root);
				cJSON_Delete(root);
			}
			auto script = INJECT(Script);
			script::Object resource;
			ADD_FUNC(resource,asset);
			script->getEngine()->setValue("resource",&resource);
		}
		core::Pointer<resource::Buffer> load(const std::string& token){
			auto pair = _cache.find(token);
			if(pair!=_cache.end()){
				return pair->second;
			}
			auto manifestPair = _manifest.find(token);
			if(manifestPair != _manifest.end()){
				auto filename = "assets/"+manifestPair->second;
				std::ifstream file(filename, std::ios::in|std::ios::binary);
				if(!file.is_open()){
					throw RUNTIME_ERROR(fmt::format("cannot open resource file: {}",filename));
				}
				auto size = std::filesystem::file_size(filename);
				auto buf = resource::Buffer::create(size);
				file.read((char *)buf->getBufferData(),size);
				file.close();
				_cache[token] = buf;
				return buf;
			}else{
				throw RUNTIME_ERROR(fmt::format("unregister resource: {}"+token));
			}
		}
	};
}
#endif