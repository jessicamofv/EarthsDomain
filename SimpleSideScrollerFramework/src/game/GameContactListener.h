#pragma once
#include "stdafx.h"
// box2d include
#include <Box2D/Box2D.h>;

struct ContactInfo {
	// for keeping track of the relevant info
	// of a contact when it's copied out from
	// the recycle b2Contact argument
    b2Fixture *fixtureA;
    b2Fixture *fixtureB;

	// need to redefine the == operator for this
	// struct type (it otherwise results an error)
	bool operator==(const ContactInfo& other) const
    {
        return (fixtureA == other.fixtureA) && (fixtureB == other.fixtureB);
    }
};

class GameContactListener : public b2ContactListener
{
public:
	list<ContactInfo> contacts;

	GameContactListener()	{}
	~GameContactListener()	{}
	
	virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);    
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};