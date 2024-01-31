package dev.hofes.DesignPatterns.VisitorPattern.Tree;

import dev.hofes.ComplexDatastructures.ComparableTreeNode;
import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

public class SumVisitor implements TreeVisitor<Integer> {
    private int sum = 0;

    @Override
    public void visit(@NotNull ComparableTreeNode<Integer> node) {
        sum += node.value;
        if (node.right != null) visit(node.right);
        if (node.left != null) visit(node.left);
    }
    @Contract(pure = true)
    public int getSum() {
        return sum;
    }
}