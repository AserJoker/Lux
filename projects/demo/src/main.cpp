#include "../include/Application.hpp"
namespace Lux {
static Demo::Application g_Application;
Core::IApplication *g_theApp = &g_Application;
} // namespace Lux