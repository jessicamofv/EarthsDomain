#pragma once
#include "stdafx.h"
#include <Box2D/Box2D.h>;
#include "GameContactListener.h"

void GameContactListener::BeginContact(b2Contact* contact) {
    // need to copy out the info from the contact and 
	// add it to a list of copies because the b2Contact 
	// argument gets recycled and we will want to make
	// use of the contact later
    ContactInfo contactInfo = { contact->GetFixtureA(), contact->GetFixtureB() };
    contacts.push_back(contactInfo);
}
 
void GameContactListener::EndContact(b2Contact* contact) {
    ContactInfo contactInfo = { contact->GetFixtureA(), contact->GetFixtureB() };
    list<ContactInfo>::iterator contactToCheck;
	// check if the contact is already in the list
    contactToCheck = std::find(contacts.begin(), contacts.end(), contactInfo);
	// and if it is
    if (contactToCheck != contacts.end()) {
		// get rid of it
        contacts.erase(contactToCheck);
    }
}

// need to override these methods too, but they
// aren't being used
void GameContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
}
 
void GameContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
}