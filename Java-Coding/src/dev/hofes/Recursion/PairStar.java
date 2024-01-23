package dev.hofes.Recursion;

import org.jetbrains.annotations.NotNull;

public class PairStar {
    public static @NotNull String main(@NotNull String s, int i) {
        if (s.length() - 1 <= i) return s;
        if (s.charAt(i) == s.charAt(i + 1)) s = s.substring(0, i + 1) + '*' + s.substring(i + 1);
        return main(s, i + 1);
    }

    public static @NotNull String main(@NotNull String s) {
        return main(s, 0);
    }
}