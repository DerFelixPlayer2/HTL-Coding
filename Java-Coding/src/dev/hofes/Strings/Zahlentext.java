package dev.hofes.Strings;

import org.jetbrains.annotations.NotNull;

import java.util.Arrays;

public class Zahlentext {
    public static @NotNull String stringToNums(@NotNull String str) {
        StringBuilder b = new StringBuilder();
        for (int i = 0; i < str.length(); i++)
            b.append(((int) str.charAt(i)) - 64).append(" ");
        return b.toString();
    }

    public static @NotNull String numsToString(@NotNull String str) {
        StringBuilder b = new StringBuilder();
        int[] nums = Arrays.stream(str.split(" ")).mapToInt(Integer::parseInt).toArray();
        for (int i : nums)
            b.append(((char) (i + 64)));
        return b.toString();
    }
}