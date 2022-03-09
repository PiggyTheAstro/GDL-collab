#include <components/rectCollider.h>
#include <core/serviceHandler.h>
#include <systems/collisionSystem.h>

void RectCollider::Start(Transform* parent)
{
	transform = parent;
	rect = SDL_FRect();
	ServiceHandler::instance->GetModule<CollisionSystem>()->AddCollider(this);
}

void RectCollider::Update()
{
	rect.x = transform->position.x;
	rect.y = transform->position.y;
	rect.w = transform->scale.x;
	rect.h = transform->scale.y;
}

void RectCollider::AddListener(std::function<void()> enterFunc, std::function<void()> exitFunc)
{
	if (enterFunc != nullptr)
	{
		enterListeners.push_back(enterFunc);
	}
	if (exitFunc != nullptr)
	{
		exitListeners.push_back(exitFunc);
	}
}

void RectCollider::OnCollisionEnter(Transform* other)
{
	for (int id : collided)
	{
		if (other->ID == id)
		{
			return;
		}
	}
	collided.push_back(other->ID);
	col = other;
	for (std::function<void()> func : enterListeners)
	{
		func();
	}
}

void RectCollider::OnCollisionExit(Transform* other)
{
	for (int i = collided.size() - 1; i > -1; i--)
	{
		if (other->ID == collided[i])
		{
			collided.erase(collided.begin() + i);
			for (std::function<void()> func : exitListeners)
			{
				func();
			}
		}
	}
}

RectCollider::~RectCollider()
{
	ServiceHandler::instance->GetModule<CollisionSystem>()->RemoveCollider(this);
}

SDL_FRect RectCollider::GetRect()
{
	return rect;
}