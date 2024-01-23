package dev.hofes.FSST.strings;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

public class Substr {
    @Contract(pure = true)
    public static @NotNull String main(@NotNull String str, int startIndex, int endIndex) {
        if (startIndex > endIndex) return "";

        StringBuilder b = new StringBuilder();
        for (int i = startIndex; i < endIndex; i++)
            b.append(str.charAt(i));
        return b.toString();
    }

    @Contract(pure = true)
    public static @NotNull String main(@NotNull String str, int startIndex) {
        return main(str, startIndex, str.length());
    }
}