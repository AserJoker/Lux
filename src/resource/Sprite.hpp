#ifndef _H_LUX_RESOURCE_SPRITE_
#define _H_LUX_RESOURCE_SPRITE_
#include <stack>
#include <list>
#include "system/Resource.hpp"
#include "system/Graphic.hpp"
namespace lux::resource
{
    class Sprite : public core::EventEmitter
    {
    private:
        int _width;
        int _height;
        SDL_Rect _target;
        SDL_Rect _source;
        SDL_Point _center;
        double _angle;
        SDL_RendererFlip _flip;
        bool _visible;
        SDL_Texture *_pTexture;
        struct RenderTask
        {
            core::Pointer<Sprite> _sprite;
            SDL_Rect _target;
            SDL_Rect _source;
            SDL_Point _center;
            double _angle;
            SDL_RendererFlip _flip;
        };
        struct RenderList
        {
            std::list<RenderTask> _list;
            core::Pointer<Sprite> _target;
        };

        static std::stack<RenderList> _renderList;

    protected:
        void on(core::EventEmitter *emitter, const std::string &event)
        {
            if (event == system::Graphic::EVENT_QUIT)
            {
                dispose();
            }
        }

    public:
        DEFINE_TOKEN(lux::resource::Sprite);
        Sprite() : _width(2), _height(2), _target({0, 0, 2, 2}), _source({0, 0, 2, 2}), _center({1, 1}), _angle(0), _flip(SDL_FLIP_NONE), _visible(false), _pTexture(nullptr)
        {
            auto g = INJECT(system::Graphic);
            g->addEventListener(system::Graphic::EVENT_QUIT, this);
        }
        ~Sprite() override
        {
            dispose();
        }
        void dispose()
        {
            if (_pTexture)
            {
                SDL_DestroyTexture(_pTexture);
                _pTexture = nullptr;
            }
        }
        void draw()
        {
            if (Sprite::_renderList.size() < 1)
            {
                throw RUNTIME_ERROR("Render Stack is Empty");
            }
            auto top = Sprite::_renderList.top();
            // top._list.push_back(core::Pointer<Sprite>(this));
            if (!top._list.size())
            {
                top._list.push_back({core::Pointer<Sprite>(this),_target,_source,_center,_angle,_flip});
            }
            else
            {
                auto next = top._list.begin();
                auto it = next;
                next++;
                for (; next != top._list.end(); it++)
                {
                    if ((*next)._target.y > this->_target.y || ((*next)._target.y == this->_target.y && (*next)._target.x > this->_target.x))
                    {
                        break;
                    }
                    next++;
                }
                if (next != top._list.end())
                {
                    top._list.push_back({core::Pointer<Sprite>(this),_target,_source,_center,_angle,_flip});
                }
                else
                {
                    top._list.insert(it, {core::Pointer<Sprite>(this),_target,_source,_center,_angle,_flip});
                }
            }
            Sprite::_renderList.pop();
            Sprite::_renderList.push(top);
        }
        void setVisible(bool visible)
        {
            _visible = visible;
        }
        void setSourceRect(int x, int y, int w, int h)
        {
            _source.x = x;
            _source.y = y;
            _source.w = w;
            _source.h = h;
        }

        void setTargetRect(int x, int y, int w, int h)
        {
            _target.x = x;
            _target.y = y;
            _target.w = w;
            _target.h = h;
        }
        void setRotation(int x, int y, double angle)
        {
            _center.x = x;
            _center.y = y;
            _angle = angle;
        }
        void setOpacity(Uint8 opacity)
        {
            if (SDL_SetTextureAlphaMod(_pTexture, opacity) != 0)
            {
                throw RUNTIME_ERROR(SDL_GetError());
            }
        }
        void getOpacity(Uint8 *opacity)
        {
            if (SDL_GetTextureAlphaMod(_pTexture, opacity) != 0)
            {
                throw RUNTIME_ERROR(SDL_GetError());
            }
        }
        void getVisible(bool *visible)
        {
            *visible = _visible;
        }
        void getSourceRect(int *x, int *y, int *w, int *h)
        {
            *x = _source.x;
            *y = _source.y;
            *w = _source.w;
            *h = _source.h;
        }

        void getTargetRect(int *x, int *y, int *w, int *h)
        {
            *x = _target.x;
            *y = _target.y;
            *w = _target.w;
            *h = _target.h;
        }

        void getRotation(int *x, int *y, double *angle)
        {
            *x = _center.x;
            *y = _center.y;
            *angle = _angle;
        }

        void getSize(int *width, int *height)
        {
            *width = _width;
            *height = _height;
        }
        void update(SDL_Rect *rc, const void *pixels, int pitch)
        {
            if (SDL_UpdateTexture(_pTexture, rc, pixels, pitch) != 0)
            {
                throw RUNTIME_ERROR(SDL_GetError());
            }
        }

        static void begin(core::Pointer<Sprite> sprite = nullptr)
        {
            RenderList list = {
                {}, sprite};
            Sprite::_renderList.push(list);
        }
        static void end()
        {
            auto list = Sprite::_renderList.top();
            Sprite::setTarget(list._target);
            auto g = INJECT(system::Graphic);
            for (auto &item : list._list)
            {

                if (item._sprite->_visible && item._sprite->_pTexture)
                {
                    if (SDL_RenderCopyEx(g->getRenderer(), item._sprite->_pTexture, &item._source, &item._target, item._angle, &item._center, item._flip) != 0)
                    {
                        throw RUNTIME_ERROR(SDL_GetError());
                    }
                }
            }
            Sprite::_renderList.pop();
            setTarget(nullptr);
        }

        static void setTarget(core::Pointer<Sprite> sprite = nullptr)
        {
            auto g = INJECT(system::Graphic);
            SDL_SetRenderTarget(g->getRenderer(), sprite != nullptr ? sprite->_pTexture : nullptr);
        }

        static core::Pointer<Sprite> create(int width, int height, int access)
        {
            auto sprite = INJECT(Sprite);
            auto g = INJECT(system::Graphic);
            sprite->_pTexture = SDL_CreateTexture(g->getRenderer(), SDL_PIXELFORMAT_ARGB8888, (SDL_TextureAccess)access, width, height);
            if (!sprite->_pTexture)
            {
                throw RUNTIME_ERROR(SDL_GetError());
            }
            sprite->_source.w = width;
            sprite->_source.h = height;
            sprite->_target.w = width;
            sprite->_target.h = height;
            sprite->_center.x = width / 2;
            sprite->_center.y = height / 2;
            sprite->_width = width;
            sprite->_height = height;
            SDL_SetTextureBlendMode(sprite->_pTexture, SDL_BLENDMODE_BLEND);
            return sprite;
        }

        static core::Pointer<Sprite> create(SDL_Surface *sur)
        {
            auto sprite = INJECT(Sprite);
            auto g = INJECT(system::Graphic);
            sprite->_pTexture = SDL_CreateTextureFromSurface(g->getRenderer(), sur);
            if (!sprite->_pTexture)
            {
                throw RUNTIME_ERROR(SDL_GetError());
            }
            int width = sur->w;
            int height = sur->h;
            sprite->_source.w = width;
            sprite->_source.h = height;
            sprite->_target.w = width;
            sprite->_target.h = height;
            sprite->_center.x = width / 2;
            sprite->_center.y = height / 2;
            sprite->_width = width;
            sprite->_height = height;
            SDL_SetTextureBlendMode(sprite->_pTexture, SDL_BLENDMODE_BLEND);
            return sprite;
        }

        static core::Pointer<Sprite> load(core::Pointer<Buffer> buf)
        {
            auto sprite = INJECT(Sprite);
            auto g = INJECT(system::Graphic);
            auto surface = IMG_Load_RW(SDL_RWFromConstMem(buf->getBufferData(), (int)buf->getBufferSize()), 0);
            sprite->_pTexture = SDL_CreateTextureFromSurface(g->getRenderer(), surface);
            auto width = surface->w;
            auto height = surface->h;
            sprite->_source.w = width;
            sprite->_source.h = height;
            sprite->_target.w = width;
            sprite->_target.h = height;
            sprite->_center.x = width / 2;
            sprite->_center.y = height / 2;
            sprite->_width = width;
            sprite->_height = height;
            SDL_FreeSurface(surface);
            if (!sprite->_pTexture)
            {
                throw RUNTIME_ERROR(SDL_GetError());
            }
            return sprite;
        }
    };
    std::stack<Sprite::RenderList> Sprite::_renderList;
} // namespace lux::resource

#endif