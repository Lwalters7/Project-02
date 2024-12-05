#pragma once
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <stdexcept>
#include <iostream>
#include "Component.h"

template <typename T>
int getID() {
    return std::hash<std::type_index>()(std::type_index(typeid(T)));
}

class GameObject {
public:
    // Add a component to the GameObject
    template <typename T, typename... Args>
    T* add(Args&&... args) {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
        auto component = std::make_unique<T>(*this, std::forward<Args>(args)...);
        T* rawPtr = component.get(); // Get raw pointer before transferring ownership
        components[getID<T>()] = std::move(component);
        return rawPtr;
    }

    void markForDeletion() { markedForDeletion = true; }

    bool isMarkedForDeletion() const { return markedForDeletion; }


    // Get a component by type as a raw pointer
    template <typename T>
    T* get() {
        auto it = components.find(getID<T>());
        if (it != components.end()) {
            return dynamic_cast<T*>(it->second.get());
        }
        return nullptr;
    }

    // Position handling
    void setPosition(float x, float y) {
        _x = x;
        _y = y;
    }

    void getPosition(float& x, float& y) const {
        x = _x;
        y = _y;
    }

    // Marks the object for deletion
    void destroy() { _isDestroyed = true; }

    // Checks if the object is marked for deletion
    bool isDestroyed() const { return _isDestroyed; }

    // Update all components
    void update() {
        for (auto& pair : components) {
            pair.second->update();
        }
    }

    // Draw all components
    void draw() {
        for (auto& pair : components) {
            pair.second->draw();
        }
    }

private:
    bool _isDestroyed = false;
    float _x = 0.0f; // X-coordinate of the GameObject
    float _y = 0.0f; // Y-coordinate of the GameObject
    std::unordered_map<int, std::unique_ptr<Component>> components;
    bool markedForDeletion = false; // Indicates whether the object should be removed
};
