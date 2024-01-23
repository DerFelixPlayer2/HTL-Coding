package dev.hofes.FSST.design_patterns.visitor.tree;

import dev.hofes.SEN.BinaryTrees.Node;
import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

public class SumVisitor implements TreeVisitor<Integer> {
    private int sum = 0;

    @Override
    public void visit(@NotNull Node<Integer> node) {
        sum += node.value;
        if (node.right != null) visit(node.right);
        if (node.left != null) visit(node.left);
    }
    @Contract(pure = true)
    public int getSum() {
        return sum;
    }
}