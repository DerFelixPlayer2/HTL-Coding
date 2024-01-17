package de.lolgamr17.FSST.classes;

import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.util.HashMap;
import java.util.Map;

public class Dictionary {
    private final Map<String, String> words = new HashMap<>(100);

    void insert(@NotNull String key, String value) {
        if (words.size() > 100) {
            throw new RuntimeException("Dictionary is full");
        }

        words.put(key, value);
    }

    @Nullable
    String lookup(@NotNull String key) {
        return words.get(key);
    }
}