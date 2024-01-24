package dev.hofes.ComplexDatastructures.Trees;

import dev.hofes.ComplexDatastructures.ComparableNode;
import dev.hofes.DesignPatterns.VisitorPattern.Tree.TreeVisitor;
import org.jetbrains.annotations.NotNull;

import java.util.Iterator;
import java.util.Stack;

public class BinaryTree<T extends Comparable<T>> implements Iterable<T> {

    private ComparableNode<T> root;

    public ComparableNode<T> search(@NotNull T value) {
        ComparableNode<T> p = root;
        while (p != null) {
            if (p.value == value) return p;
            if (p.value.compareTo(value) < 0) p = p.left;
            else p = p.right;
        }
        return null;
    }

    public ComparableNode<T> search_recursive(@NotNull T value) {
        return search_recursive(root, value);
    }

    public ComparableNode<T> search_recursive(ComparableNode<T> p, @NotNull T value) {
        if (p == null || p.value == value) return p;
        else if (value.compareTo(p.value) < 0) return search_recursive(p.left, value);
        return search_recursive(p.right, value);
    }

    public void insert(@NotNull T value) {
        ComparableNode<T> p = root;
        ComparableNode<T> father = null;
        while (p != null) {
            father = p;
            if (value.compareTo(p.value) < 0) p = p.left;
            else p = p.right;
        }
        ComparableNode<T> n = new ComparableNode<>(value);
        if (father == null) root = n;
        else if (value.compareTo(father.value) < 0) father.left = n;
        else father.right = n;
    }

    public void insert_recursive(@NotNull T value) {
        root = insert_recursive(root, value);
    }

    public @NotNull ComparableNode<T> insert_recursive(ComparableNode<T> p, @NotNull T value) {
        if (p == null) p = new ComparableNode<>(value);
        else if (value.compareTo(p.value) < 0) p.left = insert_recursive(p.left, value);
        else p.right = insert_recursive(p.right, value);
        return p;
    }

    public int treeToVine(@NotNull ComparableNode<T> root) {
        ComparableNode<T> tail = root;
        ComparableNode<T> rest = tail.right;
        int n = 0;

        while (rest != null) {
            if (rest.left == null) {
                tail = rest;
                rest = rest.right;
                n++;
            } else {
                ComparableNode<T> p = rest.left;
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
        final Stack<ComparableNode<T>> traversal = new Stack<>();
        traversal.push(root);

        return new Iterator<>() {
            @Override
            public boolean hasNext() {
                return !traversal.isEmpty();
            }

            @Override
            public T next() {
                ComparableNode<T> n = traversal.pop();
                if (n.right != null) traversal.push(n.right);
                if (n.left != null) traversal.push(n.left);
                return n.value;
            }
        };
    }

    public void accept(@NotNull TreeVisitor<T> visitor) {
        visitor.visit(root);
    }
}