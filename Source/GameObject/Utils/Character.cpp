#include"Character.h"


GameObject::Utils::Character::Character(
	const std::string & name,
	float height,
	float mass,
	BtCollisionShapeSharedPtr shape,
	MME::Object::ModelKaiSharedPtr model)
	:mName(name),
	mHeight(height),
	mMass(mass),
	mShape(shape),
	mModel(model)
{}

GameObject::Utils::Character::~Character() {}
