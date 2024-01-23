package dev.hofes.FSST.strings;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

public class Genetik {
    @Contract(pure = true)
    public static int main(@NotNull String str) {
        return str.split("cggta").length - 1;
    }
}