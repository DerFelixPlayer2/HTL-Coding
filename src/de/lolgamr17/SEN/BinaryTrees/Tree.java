package de.lolgamr17.BinaryTrees;

import org.jetbrains.annotations.NotNull;

class Tree {
    private static class Node {
        int value;
        Node left;
        Node right;

        public Node(int value) {
            this.value = value;
        }
    }

    Node root;

    Node search(int value) {
        Node p = root;
        while (p != null) {
            if (p.value == value) return p;
            if (p.value < value) p = p.left;
            else p = p.right;
        }
        return null;
    }

    Node search_recursive(int value) {
        return search_recursive(root, value);
    }

    static Node search_recursive(Node p, int value) {
        if (p == null || p.value == value) return p;
        else if (value < p.value) return search_recursive(p.left, value);
        return search_recursive(p.right, value);
    }

    void insert(int value) {
        Node p = root;
        Node father = null;
        while (p != null) {
            father = p;
            if (value < p.value) p = p.left;
            else p = p.right;
        }
        Node n = new Node(value);
        if (father == null) root = n;
        else if (value < father.value) father.left = n;
        else father.right = n;
    }

    void insert_recursive(int value) {
        root = insert_recursive(root, value);
    }

    static @NotNull Node insert_recursive(Node p, int value) {
        if (p == null) p = new Node(value);
        else if (value < p.value) p.left = insert_recursive(p.left, value);
        else p.right = insert_recursive(p.right, value);
        return p;
    }

    int treeToVine(Node root) {
        Node tail = root;
        Node rest = tail.right;
        int n = 0;

        while (rest != null) {
            if (rest.left == null) {
                tail = rest;
                rest = rest.right;
                n++;
            } else {
                Node p = rest.left;
                rest.left = p.right;
                p.right = rest;
                rest = p;
                tail.right = p;
            }
        }

        return n;
    }
}