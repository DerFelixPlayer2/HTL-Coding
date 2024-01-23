package dev.hofes.Recursion;

public class StrCopies {
    public static boolean main(String str, String substr, int amt) {
        if (str.contains(substr)) {
            if (amt > 1) return main(str.replaceFirst(substr, ""), substr, amt - 1);
            return true;
        } else return amt < 1;
    }
}