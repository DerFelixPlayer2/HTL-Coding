package de.lolgamr17.strings;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

public class RightAlign {
    @Contract(pure = true)
    public static @NotNull String main(@NotNull String str, int n) {
        if (str.length() > n) throw new IllegalArgumentException("str.length() > n");
        return " ".repeat(n - str.length()) + str;
    }
}