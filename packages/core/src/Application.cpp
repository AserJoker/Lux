#include "../include/Application.hpp"
using namespace Lux::Core;
Application::Application() : m_isRunning(false) {}
Application::~Application() {}
int Application::Initialize(int argc, char **argv) {
  m_isRunning = true;
  return 0;
}
void Application::Tick() {}
bool Application::isRunning() { return m_isRunning; }
void Application::Finalize() {}
