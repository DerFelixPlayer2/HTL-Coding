package dev.hofes.DesignPatterns.VisitorPattern.Tree;

import dev.hofes.ComplexDatastructures.ComparableTreeNode;

public interface TreeVisitor<T extends Comparable<T>> {
    void visit(ComparableTreeNode<T> node);
}