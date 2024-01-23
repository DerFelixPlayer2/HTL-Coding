package dev.hofes.FSST.generics;

import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.util.Objects;

public class mHashMap<S, V> {
    private final int tabSize;
    private final Entry<S, V>[] tab;

    public mHashMap(int tabSize) {
        this.tabSize = tabSize;
        tab = (Entry<S, V>[]) new Object[tabSize];
    }

    public mHashMap() {
        this(7);
    }

    public void put(@NotNull S key, @NotNull V data) {
        int hash = key.hashCode() % tabSize;
        int d = -tabSize;
        while (tab[hash] != null) {
            d += 2;
            hash = (hash + Math.abs(d)) % tabSize;
        }
        tab[hash] = new Entry<S, V>(key, data);
    }

    @Nullable
    public Object get(@NotNull S key) {
        int hash = key.hashCode() % tabSize;
        int d = -tabSize;
        while (!tab[hash].key.equals(key)) {
            d += 2;
            hash = (hash + Math.abs(d)) % tabSize;
        }
        return tab[hash].data;
    }

    private static class Entry<S, V> {
        S key;
        V data;

        public Entry(@NotNull S key, @NotNull V data) {
            this.key = key;
            this.data = data;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            Entry<S, V> entry = (Entry<S, V>) o;
            return Objects.equals(key, entry.key) && Objects.equals(data, entry.data);
        }

        @Override
        public int hashCode() {
            return Objects.hash(key, data);
        }
    }
}