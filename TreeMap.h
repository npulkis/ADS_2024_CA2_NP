#pragma once
#include "binarytree.h"
#include <stdexcept>

template <class K, class V>
class TreeMap
{
private:
    struct NodeData
    {
        K key;
        V value;

        NodeData() {}
        NodeData(const K& key, const V& value) : key(key), value(value) {}

        bool operator<(const NodeData& other) const {
            return key < other.key;
        }

        bool operator>(const NodeData& other) const {
            return key > other.key;
        }

        bool operator==(const NodeData& other) const {
            return key == other.key;
        }
    };

    BinaryTree<NodeData> tree;

    BSTNode<NodeData>* findNode(const K& key) const;

    void traverseAndInsertKeys(BSTNode<NodeData>* node, BinaryTree<K>& keysTree) const;

public:
    TreeMap() {}
    void clear();                                   // Removes all entries from the Map
    bool containsKey(const K& key) const;           // Returns true if this map contains a mapping for the specified key
    V* get(const K& key);                           // Returns the value to which the specified key is mapped, or null if this map contains no mapping for the key.
    BinaryTree<K> keySet() const;                   // Returns a Set view of the keys contained in this map
    void put(const K& key, const V& value);         // Associates the specified value with the specified key in this map
    int size() const;                               // Returns the number of key-value mappings in this map
    bool removeKey(const K& key);                   // Removes the item denoted by the given key
    V& operator[](const K& key);                    // Returns the value to which the specified key is mapped, inserts default if not found
};

template <class K, class V>
void TreeMap<K, V>::clear()
{
    tree.clear();
}

template <class K, class V>
int TreeMap<K, V>::size() const
{
    return tree.count();
}

template <class K, class V>
BSTNode<typename TreeMap<K, V>::NodeData>* TreeMap<K, V>::findNode(const K& key) const
{
    BSTNode<NodeData>* current = tree.root;
    NodeData nd(key, V());
    while (current != nullptr)
    {
        if (current->getItem() == nd)
            return current;
        else if (nd < current->getItem())
            current = current->getLeft();
        else
            current = current->getRight();
    }
    return nullptr;
}

template <class K, class V>
bool TreeMap<K, V>::containsKey(const K& key) const
{
    return findNode(key) != nullptr;
}

template <class K, class V>
V* TreeMap<K, V>::get(const K& key)
{
    BSTNode<NodeData>* node = findNode(key);
    if (node != nullptr)
        return &(node->getItem().value);
    else
        return nullptr;
}

template <class K, class V>
void TreeMap<K, V>::put(const K& key, const V& value)
{
    NodeData nd(key, value);
    BSTNode<NodeData>* node = findNode(key);
    if (node != nullptr)
    {
        node->getItem().value = value;
    }
    else
    {
        tree.add(nd);
    }
}

template <class K, class V>
bool TreeMap<K, V>::removeKey(const K& key)
{
    NodeData nd(key, V());
    return tree.remove(nd);
}

template <class K, class V>
V& TreeMap<K, V>::operator[](const K& key)
{
    BSTNode<NodeData>* node = findNode(key);
    if (node != nullptr)
    {
        return node->getItem().value;
    }
    else
    {
        V defaultValue = V();
        put(key, defaultValue);
        node = findNode(key);
        return node->getItem().value;
    }
}

template <class K, class V>
BinaryTree<K> TreeMap<K, V>::keySet() const
{
    BinaryTree<K> keysTree;
    traverseAndInsertKeys(tree.root, keysTree);
    return keysTree;
}

template <class K, class V>
void TreeMap<K, V>::traverseAndInsertKeys(BSTNode<NodeData>* node, BinaryTree<K>& keysTree) const
{
    if (node == nullptr)
        return;
    traverseAndInsertKeys(node->getLeft(), keysTree);
    keysTree.add(node->getItem().key);
    traverseAndInsertKeys(node->getRight(), keysTree);
}
