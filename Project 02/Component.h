#pragma once
#include <typeindex>

class GameObject;

class Component {
public:
    Component(GameObject& parent) : _parent(parent) {}

    virtual void update()=0;
    virtual void draw() =0;

    virtual ~Component() = default;

protected:
    GameObject& parent() const { return _parent; }

private:
    GameObject& _parent;
};
