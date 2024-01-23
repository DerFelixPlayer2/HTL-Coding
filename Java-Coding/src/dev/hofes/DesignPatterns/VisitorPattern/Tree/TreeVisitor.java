package dev.hofes.DesignPatterns.VisitorPattern.Tree;

import dev.hofes.ComplexDatastructures.Trees.BinaryTree.Node;

public interface TreeVisitor<T extends Comparable<T>> {
    void visit(Node<T> node);
}