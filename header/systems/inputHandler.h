#pragma once
#include <core/subsystem.h>

class InputHandler : public SubSystem
{
public:
	void CheckEvent();
	void PushEvent(int eventValue);
	void PopEvent(int eventValue);
	bool GetKey(int key);
private:
	std::vector<int> keys;
};