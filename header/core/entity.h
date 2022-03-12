#pragma once
#include <vector>
#include <cassert>
#include <algorithm>
#include <Math/vectors.h>
#include <core/component.h>
#include <core/transform.h>

class Entity
{
public:
	Transform transform = Transform(ID); // todo: Do entity need to inherit Transform all the time?

	~Entity();

	void Start(unsigned int identifier); // Entities take in an ID in their start functions, hence why all entity creation must be done through EntitySystem's interface
	void Update(); // Update runs every frame

	template <typename Comp>
	bool HasComponent() noexcept
	{
		auto result = std::find_if(components.cbegin(), components.cend(), [] (Component* comp) {
			return dynamic_cast<Comp*>(comp) != nullptr;
		});

		return result != components.cend();
	}

	template <typename Comp>
	Comp& GetComponent() noexcept
	{
		auto result = std::find_if(components.cbegin(), components.cend(), [] (Component* comp) {
			return dynamic_cast<Comp*>(comp) != nullptr;
		});

		assert(result != components.cend());

		return dynamic_cast<Comp&>(**result);
	}

	template <typename Comp, typename... Args>
	Comp& AddComponent(Args&&... args)
	{
		static_assert(std::is_base_of<Component, Comp>::value);
		assert(!this->HasComponent<Comp>());

		Comp* comp = new Comp(args...);
		comp->Start(&this->transform);
		components.push_back(comp);
		return *comp;
	}

	template <typename Comp>
	void RemoveComponent() noexcept
	{
		assert(this->HasComponent<Comp>());

		auto result = std::find_if(components.cbegin(), components.cend(), [] (Component* comp) {
			return dynamic_cast<Comp*>(comp) != nullptr;
		});

		delete *result;
		components.erase(result);
	}

private:
	std::vector<Component*> components;
	unsigned int ID = 0;
};