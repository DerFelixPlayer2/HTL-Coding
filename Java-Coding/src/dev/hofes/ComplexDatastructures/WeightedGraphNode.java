package dev.hofes.ComplexDatastructures;

import dev.hofes.ComplexDatastructures.Graph.WeightedGraph;
import kotlin.Pair;
import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;

public class WeightedGraphNode<T> {

    private final T value;
    public final List<Pair<WeightedGraphNode<T>, Integer>> adj = new ArrayList<>();
//    private Pair<WeightedGraphNode<T>, Integer> father; // nächster Baumknoten
    public boolean marked = false;
//    private int pos; // Position in priority Queue

    @Contract(pure = true)
    public WeightedGraphNode(@NotNull T value) {
        this.value = value;
    }

    public void addEdge(WeightedGraphNode<T> node, int weight) {
        adj.add(new Pair<>(node, weight));
    }

    @NotNull
    public T getValue() {
        return value;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (Pair<WeightedGraphNode<T>, Integer> p : adj) {
            sb.append("{").append(p.getFirst().getValue()).append(", ").append(p.getSecond()).append("}, ");
        }

        return "WeightedGraphNode{" +
                "value=" + value +
                ", adj={" + sb.toString() + "}}";
    }

    //    @Override
//    public boolean equals(Object o) {
//        if (this == o) return true;
//        if (o == null || getClass() != o.getClass()) return false;
//        WeightedGraphNode<?> that = (WeightedGraphNode<?>) o;
//        return Objects.equals(value, that.value);
//    }
//
//    @Override
//    public int hashCode() {
//        return Objects.hash(value);
//    }
}