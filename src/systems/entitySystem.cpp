#include <iostream>
#include <algorithm>
#include <ranges>
#include <cassert>
#include <systems/entitySystem.h>

Entity& EntitySystem::CreateEntity()
{
	Entity* ent = new Entity; // Handled
	entityList.push_back(ent);
	ent->Start(nextID);
	nextID += 1; // ID for the next entity spawned starts at 1 and increments by 1 each time
	assert(nextID != 0); // Assert for unsigned overflow
	return *ent;
}

Entity& EntitySystem::GetEntity(unsigned int ID)
{
	// todo: Searching in vector might be quite painful, we might use vector that has indexes of entities correlated to their IDs

	// Lower bound returns the entity with the ID passed in or an entity above that. The lambda is necessary to compare an entity with an ID
	auto it = std::lower_bound(entityList.begin(), entityList.end(), ID, [](Entity* ent, unsigned int id) { return ent->transform.ID < id; });
	if (it != entityList.cend() && (*it)->transform.ID == ID) // Return entity if the index is not out of bounds and the IDs match
	{
		return **it;
	}
	throw "Invalid entity ID";
}

std::vector<Entity*> const& EntitySystem::GetAllEntities()
{
	return entityList;
}

void EntitySystem::Update()
{
	for (auto entity : entityList)
	{
		entity->Update();
	}
}

void EntitySystem::DestroyEntity(unsigned int ID)
{
	auto ent = GetEntity(ID);
	entityList.erase(std::find(entityList.begin(), entityList.end(), &ent));
	delete &ent;
}
