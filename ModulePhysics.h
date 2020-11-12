#pragma once
#include "Module.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"
#include "ModulePlayer.h"
#define GRAVITY_X 0.0f
#define GRAVITY_Y -7.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	PhysBody() : listener(NULL), body(NULL)
	{}

	void GetPosition(int& x, int &y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;

public:
	int width, height;
	b2Body* body;
	Module* listener;
};

// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener // TODO
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();
	b2RevoluteJoint* CreateFliper(int x, int y, int _x, int _y, int w, int h, b2RevoluteJointDef def, b2RevoluteJoint* join, b2Body* sticer);
	PhysBody* CreateCircle(int x, int y, int radius);
	PhysBody* CreateStaticCircle(int x, int y, int radius);
	PhysBody* CreateRectangle(int x, int y, int width, int height);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height);
	PhysBody* CreateChain(int x, int y, int* points, int size);

	// b2ContactListener ---
	void BeginContact(b2Contact* contact);
	b2RevoluteJointDef grandederecha;
	b2RevoluteJointDef grandeizquierda;
	b2RevoluteJointDef pequenoderecha;
	b2RevoluteJointDef pequenoizquierda;
	b2RevoluteJoint* gd=nullptr;
	b2RevoluteJoint* gi = nullptr;
	b2RevoluteJoint* pd = nullptr;
	b2RevoluteJoint* pi = nullptr;
	bool isDrawable = false;
	b2World* world;
private:

	bool isClicked = false;
	bool debug;
	bool ballActivated = true;
	
	b2MouseJoint* mouse_joint;
	b2Body* ground;
	PhysBody* ClickedBody;
	b2MouseJointDef def;
};