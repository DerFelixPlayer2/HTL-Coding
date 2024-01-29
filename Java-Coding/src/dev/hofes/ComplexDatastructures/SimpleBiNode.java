package dev.hofes.ComplexDatastructures;

import org.jetbrains.annotations.Contract;

public class SimpleBiNode<K, V> {

    private final K key;
    private V value;

    @Contract(pure = true)
    public SimpleBiNode(K key, V value) {
        this.key = key;
        this.value = value;
    }

    public K getKey() {
        return key;
    }

    public V getValue() {
        return value;
    }

    public void setValue(V value) {
        this.value = value;
    }

}