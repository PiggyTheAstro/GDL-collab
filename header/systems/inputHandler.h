#pragma once
#include <unordered_set>
#include <core/subsystem.h>

class InputHandler : public SubSystem
{
public:
	void CheckEvent();
	void Update() override;
	void PushEvent(int eventValue);
	void PopEvent(int eventValue);
	bool GetKey(int key);
private:
	std::unordered_set<int> keys;
};