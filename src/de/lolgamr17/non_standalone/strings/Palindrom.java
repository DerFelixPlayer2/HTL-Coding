package de.lolgamr17.non_standalone.strings;

import org.jetbrains.annotations.NotNull;

public class Palindrom {
    public static @NotNull String reverse(@NotNull String str) {
        StringBuilder b = new StringBuilder();
        for (int i = str.length() - 1; i >= 0; i--)
            b.append(str.charAt(i));
        return b.toString();
    }

    public static boolean isPalindrome(@NotNull String str) {
        for (int i = str.length() / 2; i >= 0; i--)
            if (str.charAt(i) != str.charAt(str.length() - i - 1))
                return false;
        return true;
    }
}