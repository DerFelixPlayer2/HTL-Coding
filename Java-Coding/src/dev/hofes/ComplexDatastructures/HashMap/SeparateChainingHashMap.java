package dev.hofes.ComplexDatastructures.HashMap;

import dev.hofes.ComplexDatastructures.LinkedBiNode;
import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

/**
 * A HashMap implementation using separate chaining.
 *
 * @param <K> The key type
 * @param <V> The value type
 */
public class SeparateChainingHashMap<K, V> {

    private final int TAB_SIZE;

    private final LinkedBiNode<K, V>[] table;

    /**
     * Creates a new HashMap with the specified size.
     *
     * @param tab_size The size
     */
    @Contract(pure = true)
    public SeparateChainingHashMap(int tab_size) {
        TAB_SIZE = tab_size;
        table = new LinkedBiNode[TAB_SIZE];
    }

    /**
     * Creates a new HashMap with the default size of 32.
     */
    @Contract(pure = true)
    public SeparateChainingHashMap() {
        this(32);
    }

    /**
     * Puts a key-value pair into the HashMap.
     *
     * @param key   The key
     * @param value The value
     */
    public void put(@NotNull K key, V value) {
        int hash = key.hashCode() % TAB_SIZE;
        if (table[hash] == null) {
            table[hash] = new LinkedBiNode<>(key, value, null);
        } else {
            LinkedBiNode<K, V> node = table[hash];
            for (; node.getNext() != null && node.getKey() != key; node = node.getNext()) ;
            if (node.getKey() == key) {
                node.setValue(value);
            } else {
                node.setNext(new LinkedBiNode<>(key, value, null));
            }
        }
    }

    /**
     * Checks if the HashMap contains a key.
     *
     * @param key The key
     * @return True if the HashMap contains the key, false otherwise
     */
    public boolean contains(@NotNull K key) {
        int hash = key.hashCode() % TAB_SIZE;
        if (table[hash] == null) {
            return false;
        } else {
            LinkedBiNode<K, V> node = table[hash];
            for (; node.getNext() != null && node.getKey() != key; node = node.getNext()) ;
            return node.getKey() == key;
        }
    }

    /**
     * Retrieves a value from the HashMap.
     *
     * @param key The key
     * @return The value or null if the key is not present
     */
    @Nullable
    public V get(@NotNull K key) {
        int hash = key.hashCode() % TAB_SIZE;
        if (table[hash] == null) {
            return null;
        } else {
            LinkedBiNode<K, V> node = table[hash];
            for (; node.getNext() != null && node.getKey() != key; node = node.getNext()) ;
            return node.getKey() == key ? node.getValue() : null;
        }
    }

    /**
     * Removes a key-value pair from the HashMap.
     *
     * @param key The key
     * @throws IllegalStateException When the key is not present
     */
    public void remove(@NotNull K key) throws IllegalStateException {
        int hash = key.hashCode() % TAB_SIZE;
        if (table[hash] != null) {
            LinkedBiNode<K, V> prev = null;
            LinkedBiNode<K, V> node = table[hash];
            while (node.getNext() != null && node.getKey() != key) {
                prev = node;
                node = node.getNext();
            }
            if (node.getKey() == key) {
                if (prev == null) {
                    table[hash] = node.getNext();
                } else {
                    prev.setNext(node.getNext());
                }
            } else throw new IllegalStateException("Key not found!");
        }
    }

}