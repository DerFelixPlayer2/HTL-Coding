package dev.hofes.ComplexDatastructures.Graph;

import dev.hofes.ComplexDatastructures.WeightedGraphNode;
import kotlin.Pair;
import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.util.*;
import java.util.function.Consumer;

public class WeightedGraph {

    public WeightedGraph() {
    }

    public static <T> void addEdge(@NotNull WeightedGraphNode<T> from, @NotNull WeightedGraphNode<T> to, int weight) {
        from.addEdge(to, weight);
        to.addEdge(from, weight);
    }

    public static <T> void traverseBFS(@NotNull WeightedGraphNode<T> node, @NotNull Consumer<WeightedGraphNode<T>> consumer) {
        Queue<WeightedGraphNode<T>> q = new ArrayDeque<>();
        node.marked = !node.marked;

        do {
            consumer.accept(node);

            for (Pair<WeightedGraphNode<T>, Integer> n : node.adj) {
                if (node.marked != n.getFirst().marked) {
                    q.add(n.getFirst());
                    n.getFirst().marked = node.marked;
                }
            }

            node = q.poll();
        } while (node != null);

    }

    public static <T> void traverseDFS(@NotNull WeightedGraphNode<T> node, @NotNull Consumer<WeightedGraphNode<T>> consumer) {
        node.marked = !node.marked;
        consumer.accept(node);

        for (Pair<WeightedGraphNode<T>, Integer> n : node.adj) {
            if (node.marked != n.getFirst().marked) {
                traverseDFS(n.getFirst(), consumer);
            }
        }
    }

    @NotNull
    @Contract(pure = true)
    public static <T> WeightedGraphNode<T> getMinimalSpanningTree(WeightedGraphNode<T> root) {
        HashMap<T, WeightedGraphNode<T>> nodes = new HashMap<>();
        traverseBFS(root, n -> nodes.put(n.getValue(), new WeightedGraphNode<>(n.getValue())));

        PriorityQueue<Pair<Pair<WeightedGraphNode<T>, WeightedGraphNode<T>>, Integer>> pq = new PriorityQueue<>(
                Comparator.comparingInt(Pair::getSecond));
        Set<WeightedGraphNode<T>> visited = new HashSet<>();

        visited.add(root);
        for (Pair<WeightedGraphNode<T>, Integer> adjPair : root.adj) {
            pq.add(new Pair<>(new Pair<>(root, adjPair.getFirst()), adjPair.getSecond()));
        }

        while (!pq.isEmpty()) {
            Pair<Pair<WeightedGraphNode<T>, WeightedGraphNode<T>>, Integer> pair = pq.poll();
            WeightedGraphNode<T> from = pair.getFirst().getFirst();
            WeightedGraphNode<T> to = pair.getFirst().getSecond();

            if (!visited.contains(to)) {
                addEdge(nodes.get(from.getValue()), nodes.get(to.getValue()), pair.getSecond());
                visited.add(to);

                for (Pair<WeightedGraphNode<T>, Integer> adjPair : to.adj) {
                    pq.add(new Pair<>(new Pair<>(to, adjPair.getFirst()), adjPair.getSecond()));
                }
            }
        }

        return nodes.get(root.getValue());
    }

    @Nullable
    @Contract(pure = true)
    public static <T> List<WeightedGraphNode<T>> getShortestPath(@NotNull WeightedGraphNode<T> start,
                                                                 @NotNull WeightedGraphNode<T> end) {
        Map<WeightedGraphNode<T>, WeightedGraphNode<T>> predecessors = new HashMap<>();
        PriorityQueue<Pair<Pair<WeightedGraphNode<T>, WeightedGraphNode<T>>, Integer>> queue =
                new PriorityQueue<>(Comparator.comparingInt(Pair::getSecond));

        predecessors.put(start, null);
        for (Pair<WeightedGraphNode<T>, Integer> adjPair : start.adj) {
            queue.add(new Pair<>(new Pair<>(adjPair.getFirst(), start), adjPair.getSecond()));
        }

        while (!predecessors.containsKey(end)) {
            if (queue.isEmpty()) {
                System.out.println("No path found.");
                return null;
            }

            Pair<Pair<WeightedGraphNode<T>, WeightedGraphNode<T>>, Integer> current = queue.poll();
            if (predecessors.containsKey(current.getFirst().getFirst())) {
                continue;
            }

            predecessors.put(current.getFirst().getFirst(), current.getFirst().getSecond());

            for (Pair<WeightedGraphNode<T>, Integer> adjPair : current.getFirst().getFirst().adj) {
                if (!predecessors.containsKey(adjPair.getFirst())) {
                    queue.add(new Pair<>(new Pair<>(adjPair.getFirst(), current.getFirst().getFirst()), adjPair.getSecond() + current.getSecond()));
                }
            }
        }

        List<WeightedGraphNode<T>> path = new ArrayList<>();
        for (WeightedGraphNode<T> node = end; node != null; node = predecessors.get(node)) {
            path.add(0, node);
        }

        return path;
    }

}