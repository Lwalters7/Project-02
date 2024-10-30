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
    // Add a component to the GameObject.
    template <typename T, typename... Args>
    void add(Args&&... args) {
        static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
        components[getID<T>()] = std::make_unique<T>(*this, std::forward<Args>(args)...);
    }

    // Get a component by type as a raw pointer.
    template <typename T>
    T* get() {

        auto it = components.find(getID<T>());
        if (it != components.end()) {
            return dynamic_cast<T*>(it->second.get());
        }
        return nullptr;
    }

    // Marks the object for deletion
    void destroy() { _isDestroyed = true; }

    // Checks if the object is marked for deletion
    bool isDestroyed() const { return _isDestroyed; }

    // Update all components.
    void update() {
        for (auto& pair : components) {
            pair.second->update();
        }
    }

    // Draw all components.
    void draw() {
        for (auto& pair : components) {
            pair.second->draw();
        }
    }

private:
    bool _isDestroyed = false;
    std::unordered_map<int, std::unique_ptr<Component>> components;
};
