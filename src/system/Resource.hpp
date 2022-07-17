#ifndef _H_LUX_SYSTEM_RESOURCE_
#define _H_LUX_SYSTEM_RESOURCE_
#include <cjson/cJSON.h>
#include <fstream>
#include <filesystem>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "core/Dependence.hpp"
#include "Application.hpp"
#include "interface/IResource.hpp"
namespace lux::system {
    class Resource :public IResource, public core::Dependence<Application> {
    private:
        std::map<std::string, std::string> _assets;
        void resolveAsset(cJSON* object, std::string root) {
            if (cJSON_IsString(object)) {
                _assets[root] = std::string("assets/") + object->valuestring;
            }
            else {
                auto child = object->child;
                while (child) {
                    resolveAsset(child, root.empty() ? child->string : root + "::" + child->string);
                    child = child->next;
                }
            }
        }
    public:
        Resource() {
            if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP) == 0) {
                throw SDL_ERROR;
            }
            if (TTF_Init() != 0) {
                throw SDL_ERROR;
            }
            std::ifstream file;
            file.open("assets/manifest.json");
            if (!file.is_open()) {
                throw RUNTIME_ERROR("cannot open manifest.json");
            }
            file >> std::noskipws;
            std::string source;
            while (true) {
                char c;
                file >> c;
                if (file.eof()) {
                    break;
                }
                source += c;
            }
            file.close();
            cJSON* root = cJSON_Parse(source.c_str());
            if (!root) {
                throw RUNTIME_ERROR("failed to resolve manifest.json");
            }
            resolveAsset(root, "");
            cJSON_Delete(root);
        }
        ~Resource() override {
            TTF_Quit();
            IMG_Quit();
        }
        core::Pointer<resource::Buffer> load(const std::string& token) override {
            auto path = _assets[token];
            if (path.empty()) {
                throw RUNTIME_ERROR(fmt::format("unknown asset token: {}", token));
            }
            std::ifstream file;
            file.open(path, std::ios::binary);
            if (!file.is_open()) {
                throw RUNTIME_ERROR(fmt::format("cannot open load file: {}", path));
            }
            file.seekg(0, std::ios::end);
            auto len = file.tellg();
            file.seekg(0, std::ios::beg);
            auto buf = resource::Buffer::create((size_t)len);
            file.read(buf->getBuffer<char>(), len);
            file.close();
            return buf;
        }
    };
} // namespace lux::system

#endif