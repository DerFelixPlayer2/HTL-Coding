package dev.hofes.ComplexDatastructures.HashMap;

import dev.hofes.ComplexDatastructures.SimpleBiNode;
import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

/**
 * A HashMap implementation using quadratic probing.
 *
 * @param <K> The key type
 * @param <V> The value type
 */
public class QuadraticProbingHashMap<K, V> {

    private final int TAB_SIZE;

    private final SimpleBiNode<K, V>[] table;

    /**
     * Creates a new HashMap with the specified size.
     *
     * @param tab_size The tab-size. Must be greater than 0 and prime.
     * @throws IllegalArgumentException When the tab-size is not greater than 0
     */
    @Contract(pure = true)
    public QuadraticProbingHashMap(int tab_size) throws IllegalArgumentException {
        if (tab_size <= 0) throw new IllegalArgumentException("Tab-size must be greater than 0!");

        TAB_SIZE = 4 * tab_size + 3;
        table = new SimpleBiNode[TAB_SIZE];
    }

    /**
     * Creates a new HashMap with the default tab-size of 123.
     */
    @Contract(pure = true)
    public QuadraticProbingHashMap() {
        this(123);
    }

    /**
     * Puts a key-value pair into the HashMap.
     *
     * @param key   The key
     * @param value The value
     * @throws IllegalStateException When the HashMap is full
     */
    public void put(@NotNull K key, V value) throws IllegalStateException {
        int hash = key.hashCode() % TAB_SIZE;
        for (int d = -TAB_SIZE; table[hash] != null; d += 2) {
            if (d == TAB_SIZE) throw new IllegalStateException("HashMap is full!");
            hash = (hash + Math.abs(d)) % TAB_SIZE;
        }
        table[hash] = new SimpleBiNode<>(key, value);
    }

    /**
     * Checks if the HashMap contains a key.
     *
     * @param key The key
     * @return True if the HashMap contains the key, false otherwise
     */
    public boolean contains(@NotNull K key) {
        int hash = key.hashCode() % TAB_SIZE;
        for (int d = -TAB_SIZE; table[hash] != null; d += 2) {
            if (d == TAB_SIZE) return false;
            if (table[hash].getKey().equals(key)) return true;
            hash = (hash + Math.abs(d)) % TAB_SIZE;
        }
        return false;
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
        for (int d = -TAB_SIZE; table[hash] != null; d += 2) {
            if (d == TAB_SIZE) return null;
            if (table[hash].getKey().equals(key)) return table[hash].getValue();
            hash = (hash + Math.abs(d)) % TAB_SIZE;
        }
        return null;
    }

    /**
     * Removes a key-value pair from the HashMap.
     *
     * @param key The key
     */
    public void remove(@NotNull K key) {
        int hash = key.hashCode() % TAB_SIZE;
        for (int d = -TAB_SIZE; table[hash] != null; d += 2) {
            if (table[hash].getKey().equals(key)) {
                table[hash] = null;
                return;
            }
            hash = (hash + Math.abs(d)) % TAB_SIZE;
        }
    }

}