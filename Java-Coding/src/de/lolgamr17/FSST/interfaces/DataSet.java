package de.lolgamr17.FSST.interfaces;

import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.util.Iterator;

public class DataSet<T> implements Iterable<T> {
    private final T[] data;
    private int count;

    public DataSet(int size) {
        data = (T[]) new Object[size];
        count = 0;
    }

    public void add(T o) {
        if (count < data.length) {
            data[count++] = o;
        }
    }

    @Nullable
    public T get() {
        if (count > 0) {
            return data[--count];
        }
        return null;
    }

    @NotNull
    @Override
    public Iterator<T> iterator() {
        return new Iterator<>() {
            private int index = 0;

            @Override
            public boolean hasNext() {
                return index < count;
            }

            @Override
            public T next() {
                return data[index++];
            }
        };
    }
}