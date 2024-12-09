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
    template <typename T, typename... Args>
    T* add(Args&&... args) {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
        auto component = std::make_unique<T>(*this, std::forward<Args>(args)...);
        T* rawPtr = component.get();
        components[getID<T>()] = std::move(component);
        return rawPtr;
    }

    void markForDeletion() { markedForDeletion = true; }
    bool isMarkedForDeletion() const { return markedForDeletion; }

    template <typename T>
    T* get() {
        auto it = components.find(getID<T>());
        if (it != components.end()) {
            return dynamic_cast<T*>(it->second.get());
        }
        return nullptr;
    }

    void setPosition(float x, float y) {
        _x = x;
        _y = y;
    }

    void getPosition(float& x, float& y) const {
        x = _x;
        y = _y;
    }

    void destroy() { _isDestroyed = true; }
    bool isDestroyed() const { return _isDestroyed; }

    void update() {
        for (auto& pair : components) {
            pair.second->update();
        }
    }

    void draw() {
        for (auto& pair : components) {
            pair.second->draw();
        }
    }

private:
    bool _isDestroyed = false;
    float _x = 0.0f; 
    float _y = 0.0f; 
    std::unordered_map<int, std::unique_ptr<Component>> components;
    bool markedForDeletion = false; 
};
