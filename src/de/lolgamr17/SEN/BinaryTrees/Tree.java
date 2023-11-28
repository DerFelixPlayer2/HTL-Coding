package de.lolgamr17.SEN.BinaryTrees;

import org.jetbrains.annotations.NotNull;

import java.util.Iterator;
import java.util.Stack;

public class Tree<T extends Comparable<T>> implements Iterable<T> {

    private Node<T> root;

    public Node<T> search(T value) {
        Node<T> p = root;
        while (p != null) {
            if (p.value == value) return p;
            if (p.value.compareTo(value) < 0) p = p.left;
            else p = p.right;
        }
        return null;
    }

    public Node<T> search_recursive(T value) {
        return search_recursive(root, value);
    }

    public Node<T> search_recursive(Node<T> p, T value) {
        if (p == null || p.value == value) return p;
        else if (value.compareTo(p.value) < 0) return search_recursive(p.left, value);
        return search_recursive(p.right, value);
    }

    public void insert(T value) {
        Node<T> p = root;
        Node<T> father = null;
        while (p != null) {
            father = p;
            if (value.compareTo(p.value) < 0) p = p.left;
            else p = p.right;
        }
        Node<T> n = new Node<T>(value);
        if (father == null) root = n;
        else if (value.compareTo(father.value) < 0) father.left = n;
        else father.right = n;
    }

    public void insert_recursive(T value) {
        root = insert_recursive(root, value);
    }

    public @NotNull Node<T> insert_recursive(Node<T> p, T value) {
        if (p == null) p = new Node<T>(value);
        else if (value.compareTo(p.value) < 0) p.left = insert_recursive(p.left, value);
        else p.right = insert_recursive(p.right, value);
        return p;
    }

    public int treeToVine(Node<T> root) {
        Node<T> tail = root;
        Node<T> rest = tail.right;
        int n = 0;

        while (rest != null) {
            if (rest.left == null) {
                tail = rest;
                rest = rest.right;
                n++;
            } else {
                Node<T> p = rest.left;
                rest.left = p.right;
                p.right = rest;
                rest = p;
                tail.right = p;
            }
        }

        return n;
    }

    @NotNull
    @Override
    public Iterator<T> iterator() {
        final Stack<Node<T>> traversal = new Stack<>();
        traversal.push(root);

        return new Iterator<T>() {
            @Override
            public boolean hasNext() {
                return !traversal.isEmpty();
            }

            @Override
            public T next() {
                Node<T> n = traversal.pop();
                if (n.right != null) traversal.push(n.right);
                if (n.left != null) traversal.push(n.left);
                return n.value;
            }
        };
    }
}