package dev.hofes.Recursion;

import org.jetbrains.annotations.NotNull;

public class CountX {
    public static int main(@NotNull String s) {
        if (s.isEmpty()) return 0;
        return main(s.substring(0, s.length() - 1)) + (s.endsWith("x") ? 1 : 0);
    }
}