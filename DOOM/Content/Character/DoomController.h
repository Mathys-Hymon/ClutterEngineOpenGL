#pragma once
#include <Core/All.h>

class DoomController : public clt::PlayerController
{
public:

	DoomController();
	~DoomController() = default;

	void RotateCamera(Vector2 movement);
	void Move(Vector2 movement);

	virtual void OnCollisionEnter(const clt::hitResult& result) override {};
	virtual void OnCollisionStay(const clt::hitResult& result)  override {};
	virtual void OnCollisionExit(const clt::hitResult& result)  override {};

	virtual void OnTriggerEnter(const clt::hitResult& result) override {};
	virtual void OnTriggerStay(const clt::hitResult& result)  override {};
	virtual void OnTriggerExit(const clt::hitResult& result)  override {};
};