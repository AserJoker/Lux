#ifndef _H_LUX_SYSTEM_RESOURCE_
#define _H_LUX_SYSTEM_RESOURCE_
#include <SDL_image.h>
#include <map>
#include <cjson/cJSON.h>
#include <fstream>
#include <filesystem>
#include "core/EventEmitter.hpp"
#include "Native.hpp"
#include "resource/Buffer.hpp"
namespace lux::system {
	class Resource :public core::EventEmitter {
	private:
		std::map<std::string,std::string> _manifest;
		std::map<std::string,core::Pointer<resource::Buffer>> _cache;

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