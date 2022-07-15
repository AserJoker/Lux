#ifndef _H_LUX_SYSTEM_ICOMPONENT_
#define _H_LUX_SYSTEM_ICOMPONENT_
namespace lux::system {
class IComponent : public core::Object {
public:
  virtual void onPreInitialize() = 0;
  virtual void onInitialize() = 0;
  virtual void onPostInitialize() = 0;
};
} // namespace lux::system

#endif