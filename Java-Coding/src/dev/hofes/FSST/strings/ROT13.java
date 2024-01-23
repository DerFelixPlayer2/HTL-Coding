package dev.hofes.FSST.strings;

import org.jetbrains.annotations.NotNull;

public class ROT13 {
    public static String main(@NotNull String str) {
        StringBuilder b = new StringBuilder();
        for (char c : str.toCharArray())
            if (c >= 78) b.append(((char) (((int) c) - 13)));
            else b.append(((char) (((int) c) + 13)));
        return b.toString();
    }
}