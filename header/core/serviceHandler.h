#pragma once
#include <vector>
#include <initializer_list>
#include <core/subsystem.h>

// todo: It might be beneficial to use type_info hashing for lookup of runtime modules, it also will allow implementing this all without templating

class ServiceHandler
{
public:
	static ServiceHandler& Instance() // Ensures that only one instance could be created
	{
		static ServiceHandler instance;
		return instance;
	}

	bool isRunning = true;

	ServiceHandler(ServiceHandler const&) = delete;
	void operator=(ServiceHandler const&) = delete;

	void Update();
	void Cleanup();
	void Init(); // Should be defined for game itself, only place where AddModule is possible

	template <typename System>
	bool HasModule() noexcept
	{
		for (auto system : systems)
		{
			if (dynamic_cast<System*>(system) != nullptr)
			{
				return true;
			}
		}
		return false;
	}

	template <typename System>
	System* GetModule() // All references to engine subsystems within components should be received from this function
	{
		for (SubSystem* system : systems)
		{
			System* subsystem = dynamic_cast<System*>(system);
			if (subsystem != nullptr)
			{
				return subsystem;
			}
		}
		throw "No given module";
	}

private:
	ServiceHandler() {}

	std::vector<SubSystem*> systems;

	template <typename System, typename... Args>
	System* AddModule(Args&&... args)
	{
		if (ServiceHandler::Instance().HasModule<System>())
		{
			return ServiceHandler::Instance().GetModule<System>();
		}

		if (std::is_base_of<SubSystem, System>::value)
		{
			System* sys = new System(args...);
			systems.push_back(sys);
			return sys;
		}
		throw "Templated module isn't subclass of SubSystem";
	}
};