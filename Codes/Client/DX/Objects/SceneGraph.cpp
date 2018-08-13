#include "SceneGraph.h"

void GetAllEntities(Node3D* node, std::vector< Entity3D* >& set)
{
    set.reserve(set.size() + node->Leafs().size());
    set.insert(set.end(), node->Leafs().begin(), node->Leafs().end());

    // Get all of the leafs from this node, then decend to its children
    for (auto n : node->Nodes()) {
        GetAllEntities(n, set);
    }
}

bool EntityInSubTree(Node3D* node, Entity3D* entity)
{
    for (const auto& e : node->Leafs())
    {
        if (e == entity) {
            return true;
        }
    }

    for (const auto& n : node->Nodes())
    {
        if (EntityInSubTree(n, entity)) {
            return true;
        }
    }

    return false;
}