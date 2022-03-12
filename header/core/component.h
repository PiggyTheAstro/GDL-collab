#pragma once
#include <core/transform.h>
class Component // Important note: Component is an abstract class, all custom components have to inherit from it
{
public:
	virtual void Start(Transform* parent) {};
	virtual void Update() {};
	virtual ~Component() {}; // Pure virtual destructor has to provide a function body
};