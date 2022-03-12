#pragma once
#include <vector>
#include <type_traits>
#include <algorithm>
#include <cassert>
#include <core/subsystem.h>

// todo: It might be beneficial to use type_info hashing for lookup of runtime modules, it also will allow implementing this all without templating

class ServiceHandler
{
public:
	static ServiceHandler& Instance() // Ensures that only one instance could be retrieved
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
		auto result = std::find_if(systems.cbegin(), systems.cend(), [] (SubSystem* system) {
			return dynamic_cast<System*>(system) != nullptr;
		});

		return result != systems.cend();
	}

	template <typename System>
	System& GetModule() noexcept // All references to engine subsystems within components should be received from this function
	{
		auto result = std::find_if(systems.cbegin(), systems.cend(), [] (SubSystem* system) {
			return dynamic_cast<System*>(system) != nullptr;
		});

		assert(result != systems.cend());

		return dynamic_cast<System&>(**result);
	}

private:
	ServiceHandler() {}
	~ServiceHandler() {};

	std::vector<SubSystem*> systems;

	template <typename System, typename... Args>
	System& AddModule(Args&&... args)
	{
		static_assert(std::is_base_of<SubSystem, System>::value);
		assert(!ServiceHandler::Instance().HasModule<System>());

		System* sys = new System(args...);
		sys->Start();
		systems.push_back(sys);
		return *sys;
	}
};