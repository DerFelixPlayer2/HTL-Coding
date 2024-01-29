package dev.hofes.ComplexDatastructures;

import org.jetbrains.annotations.Contract;

public class LinkedBiNode<K, V> {

    private final K key;
    private V value;

    private LinkedBiNode<K, V> next;

    @Contract(pure = true)
    public LinkedBiNode(K key, V value, LinkedBiNode<K, V> next) {
        this.key = key;
        this.value = value;
        this.next = next;
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

    public LinkedBiNode<K, V> getNext() {
        return next;
    }

    public void setNext(LinkedBiNode<K, V> next) {
        this.next = next;
    }

}