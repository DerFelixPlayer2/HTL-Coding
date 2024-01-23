package dev.hofes.Strings;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

public class Snippets {
    @NotNull
    @Contract(pure = true)
    public static String toUpper(@NotNull String str, @NotNull String substr) {
        return String.join(substr.toUpperCase(), str.split(substr));
    }

    @Contract(pure = true)
    public static int count(@NotNull String str, @NotNull String substr) {
        return str.split(substr).length - 1;
    }

    @NotNull
    @Contract(pure = true)
    public static String killWord(@NotNull String str, @NotNull String substr) {
        return str.replaceFirst(substr, "");
    }

    @NotNull
    @Contract(pure = true)
    public static String killWords(@NotNull String str, @NotNull String substr) {
        return str.replace(substr, "");
    }
}