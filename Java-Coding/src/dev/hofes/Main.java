package dev.hofes;

import dev.hofes.ComplexDatastructures.Trees.BinaryTree.Tree;

public class Main {
    public static void main(String[] args) {

        Tree<Integer> tree = new Tree<>();
        tree.insert(5);
        tree.insert(4);
        tree.insert(3);
        tree.insert(2);
        tree.insert(1);

        for (Integer i : tree) {
            System.out.println(i);
        }

    }
}