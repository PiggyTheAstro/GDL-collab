#include <core/serviceHandler.h>

void ServiceHandler::Update()
{
  for (SubSystem* sys : ServiceHandler::Instance().systems)
  {
    sys->Update();
  }
}

void ServiceHandler::Cleanup()
{
  for (SubSystem* sys : ServiceHandler::Instance().systems)
  {
    delete sys;
  }
}