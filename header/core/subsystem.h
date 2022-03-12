#pragma once
#include <vector>
class SubSystem
{
public:
	virtual ~SubSystem() = default;

	virtual void Start();
	virtual void Update();
};