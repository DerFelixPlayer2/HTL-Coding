package dev.hofes;

import dev.hofes.ComplexDatastructures.Graph.WeightedGraph;
import dev.hofes.ComplexDatastructures.Trees.BinaryTree;
import dev.hofes.ComplexDatastructures.Trees.TraversalOrder;
import dev.hofes.ComplexDatastructures.WeightedGraphNode;

import java.util.List;

public class Main {
    public static void main(String[] args) {

        BinaryTree<Integer> tree = new BinaryTree<>();
        tree.insert(5);
        tree.insert(4);
        tree.insert(3);
        tree.insert(2);
        tree.insert(1);

        System.out.println("------ Tree ------");
        System.out.println("--- PostOrder before balancing ---");

        tree.setIteratorTraversalOrder(TraversalOrder.POSTORDER);
        tree.forEach(System.out::println);

        tree.balance();

        System.out.println("--- PostOrder after balancing ---");

        tree.forEach(System.out::println);


        WeightedGraphNode<Character> A = new WeightedGraphNode<>('A');
        WeightedGraphNode<Character> B = new WeightedGraphNode<>('B');
        WeightedGraphNode<Character> C = new WeightedGraphNode<>('C');
        WeightedGraphNode<Character> D = new WeightedGraphNode<>('D');
        WeightedGraphNode<Character> E = new WeightedGraphNode<>('E');
        WeightedGraphNode<Character> F = new WeightedGraphNode<>('F');
        WeightedGraphNode<Character> G = new WeightedGraphNode<>('G');

        WeightedGraph.addEdge(A, F, 2);
        WeightedGraph.addEdge(A, B, 1);
        WeightedGraph.addEdge(A, G, 6);
        WeightedGraph.addEdge(B, D, 2);
        WeightedGraph.addEdge(B, C, 1);
        WeightedGraph.addEdge(B, E, 4);
        WeightedGraph.addEdge(D, E, 2);
        WeightedGraph.addEdge(G, E, 1);
        WeightedGraph.addEdge(C, E, 4);
        WeightedGraph.addEdge(D, F, 1);
        WeightedGraph.addEdge(F, E, 2);

        System.out.println("------ Graph ------");
        System.out.println("--- MST with BST---");

        WeightedGraphNode<Character> mstRoot = WeightedGraph.getMinimalSpanningTree(A);
        WeightedGraph.traverseBFS(mstRoot, System.out::println);

        System.out.println("--- Shortest Path ---");

        List<WeightedGraphNode<Character>> shortestPath = WeightedGraph.getShortestPath(A, G);
        assert shortestPath != null;
        shortestPath.forEach(System.out::println);

    }
}