package de.lolgamr17.non_standalone.strings;

public class StringSplit {
    private String str;
    private final int len;

    public StringSplit(String str, int len) {
        this.str = str;
        this.len = len;
    }

    public boolean hasMoreChunks() {
        return !str.trim().isEmpty();
    }

    public String nextChunk() {
        String s = str.substring(0, Math.min(str.length(), len));
        str = str.substring(Math.min(str.length(), len));
        return s;
    }
}