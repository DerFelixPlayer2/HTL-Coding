package de.lolgamr17.FSST.interfaces;

import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.util.Iterator;

public class DataSet implements Iterable<Object> {
    private final Object[] data;
    private int count;

    public DataSet(int size) {
        data = new Object[size];
        count = 0;
    }

    public void add(Object o) {
        if (count < data.length) {
            data[count++] = o;
        }
    }

    @Nullable
    public Object get() {
        if (count > 0) {
            return data[--count];
        }
        return null;
    }

    @NotNull
    @Override
    public Iterator<Object> iterator() {
        return new Iterator<>() {
            private int index = 0;

            @Override
            public boolean hasNext() {
                return index < count;
            }

            @Override
            public Object next() {
                return data[index++];
            }

            @Override
            public void remove() {
                throw new UnsupportedOperationException();
            }
        };
    }
}