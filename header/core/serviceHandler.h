#pragma once
#include <vector>
#include <initializer_list>
#include <core/game.h>
#include <core/subsystem.h>

// todo: It might be beneficial to use type_info hashing for lookup of runtime modules, it also will allow implementing this all without templating

class ServiceHandler
{
public:
	static ServiceHandler& instance() // Ensures that only one instance could be created
	{
		static ServiceHandler instance;
		return instance;
	}

	bool isRunning;

	ServiceHandler(ServiceHandler const&) = delete;
	void operator=(ServiceHandler const&) = delete;

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
	friend class Game; // Only Game class has access to internal state

	ServiceHandler()
		: isRunning(true)	{}

	std::vector<SubSystem*> systems;

	template <typename System, typename... Args>
	System* AddModule(Args&&... args)
	{
		if (ServiceHandler::instance().HasModule<System>())
		{
			return ServiceHandler::instance().GetModule<System>();
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