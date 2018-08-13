#pragma once

#include "PCH.h"
#include "Entity3D.h"
#include "Node3D.h"

template<typename T>
Node3D* GetParent(T* element) {
    assert(element != nullptr);

    return element->GetParent();
}

template <typename T>
Node3D* GetRoot(T* element) {

    assert(element != nullptr);

    Node3D* parent = GetParent(element);

    while (parent != nullptr) {
        element = parent;
        parent = GetParent(element);
    }

    return element;
}

template <typename T>
int GraphDepth(T* element) {

    assert(element != nullptr);

    Node3D* parent = GetParent(element);

    if (parent == nullptr)
        return(0);
    else
        return(GraphDepth(parent) + 1);
}

void GetAllEntities(Node3D* node, std::vector< Entity3D* >& set);

bool EntityInSubTree(Node3D* node, Entity3D* entity);