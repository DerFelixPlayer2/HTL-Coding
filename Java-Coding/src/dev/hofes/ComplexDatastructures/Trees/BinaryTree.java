package dev.hofes.ComplexDatastructures.Trees;

import dev.hofes.DesignPatterns.VisitorPattern.Tree.TreeVisitor;
import dev.hofes.ComplexDatastructures.ComparableTreeNode;
import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.Nullable;
import org.jetbrains.annotations.NotNull;

import java.util.concurrent.LinkedBlockingQueue;
import java.util.function.Consumer;
import java.util.Iterator;
import java.util.Queue;

/**
 * A binary tree.
 *
 * @param <T> The type of the values in the tree. Must implement Comparable.
 */
public class BinaryTree<T extends Comparable<T>> implements Iterable<T> {

    private ComparableTreeNode<T> root;

    private TraversalOrder traversalOrder = TraversalOrder.INORDER;

    /**
     * Searches for a value in the tree. Iterative implementation.
     *
     * @param value The value to search for.
     * @return The node containing the value or null if the value is not in the tree.
     */
    public ComparableTreeNode<T> search(@NotNull T value) {
        ComparableTreeNode<T> p = root;
        while (p != null) {
            if (p.value == value) return p;
            if (p.value.compareTo(value) < 0) p = p.left;
            else p = p.right;
        }
        return null;
    }

    /**
     * Searches for a value in the tree. Recursive implementation.
     *
     * @param value The value to search for.
     * @return The node containing the value or null if the value is not in the tree.
     */
    public ComparableTreeNode<T> search_recursive(@NotNull T value) {
        return search_recursive(root, value);
    }

    @Contract("null, _ -> null")
    private ComparableTreeNode<T> search_recursive(@Nullable ComparableTreeNode<T> p, @NotNull T value) {
        if (p == null || p.value == value) return p;
        else if (value.compareTo(p.value) < 0) return search_recursive(p.left, value);
        return search_recursive(p.right, value);
    }

    /**
     * Inserts a value into the tree. Iterative implementation.
     *
     * @param value The value to insert.
     */
    public void insert(@NotNull T value) {
        ComparableTreeNode<T> p = root;
        ComparableTreeNode<T> father = null;
        while (p != null) {
            father = p;
            if (value.compareTo(p.value) < 0) p = p.left;
            else p = p.right;
        }
        ComparableTreeNode<T> n = new ComparableTreeNode<>(value);
        if (father == null) root = n;
        else if (value.compareTo(father.value) < 0) father.left = n;
        else father.right = n;
    }

    /**
     * Inserts a value into the tree. Recursive implementation.
     *
     * @param value The value to insert.
     */
    public void insert_recursive(@NotNull T value) {
        root = insert_recursive(root, value);
    }

    @NotNull
    private ComparableTreeNode<T> insert_recursive(@Nullable ComparableTreeNode<T> p, @NotNull T value) {
        if (p == null) p = new ComparableTreeNode<>(value);
        else if (value.compareTo(p.value) < 0) p.left = insert_recursive(p.left, value);
        else p.right = insert_recursive(p.right, value);
        return p;
    }

    /**
     * Deletes a value from the tree. Iterative implementation.
     *
     * @param value The value to delete.
     */
    public void delete(@NotNull T value) {
        ComparableTreeNode<T> p = root;
        ComparableTreeNode<T> father = null;
        while (p != null && p.value != value) {
            father = p;
            if (value.compareTo(p.value) < 0) p = p.left;
            else p = p.right;
        }
        if (p == null) return;
        if (p.left != null && p.right != null) {
            ComparableTreeNode<T> min = p.right;
            ComparableTreeNode<T> minFather = p;
            while (min.left != null) {
                minFather = min;
                min = min.left;
            }
            p.value = min.value;
            p = min;
            father = minFather;
        }
        ComparableTreeNode<T> subTree = p.left;
        if (subTree == null) subTree = p.right;
        if (father == null) root = subTree;
        else if (father.left == p) father.left = subTree;
        else father.right = subTree;
    }

    /**
     * Traverses the tree.
     *
     * @param p The root of the tree.
     * @param order The traversal order.
     * @param consumer The consumer to apply to each node.
     */
    private void traverse(@NotNull ComparableTreeNode<T> p, @NotNull TraversalOrder order,
                          @NotNull Consumer<? super T> consumer) {
        switch (order) {
            case PREORDER:
                consumer.accept(p.value);
                if (p.left != null) traverse(p.left, order, consumer);
                if (p.right != null) traverse(p.right, order, consumer);
                break;
            case INORDER:
                if (p.left != null) traverse(p.left, order, consumer);
                consumer.accept(p.value);
                if (p.right != null) traverse(p.right, order, consumer);
                break;
            case POSTORDER:
                if (p.left != null) traverse(p.left, order, consumer);
                if (p.right != null) traverse(p.right, order, consumer);
                consumer.accept(p.value);
                break;
        }
    }

    /**
     * Converts a tree to a vine.
     *
     * @param root The root of the tree.
     * @return The number of nodes in the tree.
     */
    private int treeToVine(@NotNull ComparableTreeNode<T> root) {
        ComparableTreeNode<T> tail = root;
        ComparableTreeNode<T> rest = tail.right;
        int numberOfNodes = 0;

        while (rest != null) {
            if (rest.left == null) {
                tail = rest;
                rest = rest.right;
                numberOfNodes++;
            } else {
                ComparableTreeNode<T> p = rest.left;
                rest.left = p.right;
                p.right = rest;
                rest = p;
                tail.right = p;
            }
        }

        return numberOfNodes;
    }

    /**
     * Converts a vine to a tree.
     *
     * @param root The root of the tree.
     * @param size The size (number of nodes) of the tree.
     */
    private void vineToTree(@NotNull ComparableTreeNode<T> root, int size) {
        int fullCount = (int) (Math.log(size + 1) / Math.log(2));
        ComparableTreeNode<T> rest = root;
        ComparableTreeNode<T> tail = root.right;
        for (int i = 0; i < fullCount; i++) {
            ComparableTreeNode<T> restNext = tail.right;
            ComparableTreeNode<T> tailNext = restNext.right;
            rest.right = tailNext;
            restNext.right = tailNext.left;
            tailNext.left = restNext;
            rest = restNext;
            tail = tailNext;
        }
        rest.right = null;
    }

    /**
     * Balances the tree.
     */
    public void balance() {
        int size = treeToVine(root);
        vineToTree(root, size);
    }

    public void accept(@NotNull TreeVisitor<T> visitor) {
        visitor.visit(root);
    }

    /**
     * Sets the traversal order for the iterator.
     *
     * @param order The traversal order.
     */
    public void setIteratorTraversalOrder(@NotNull TraversalOrder order) {
        traversalOrder = order;
    }

    @Override
    public void forEach(Consumer<? super T> action) {
        traverse(root, traversalOrder, action);
    }

    @NotNull
    @Override
    public Iterator<T> iterator() {
        return new Iterator<T>() {
            private final Queue<T> q = new LinkedBlockingQueue<>();
            private T lastElement = null;

            {
                forEach(q::add);
            }

            @Override
            public boolean hasNext() {
                return !q.isEmpty();
            }

            @Override
            public T next() {
                lastElement = q.poll();
                return lastElement;
            }

            @Override
            public void remove() {
                if (lastElement == null) throw new IllegalStateException();
                delete(lastElement);
                lastElement = null;
            }

            @Override
            public void forEachRemaining(Consumer<? super T> action) {
                lastElement = null;
                Iterator.super.forEachRemaining(action);
            }
        };
    }

}