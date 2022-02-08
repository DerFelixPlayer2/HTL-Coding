package de.lolgamr17.standalone.extension.Newsfeed;

import org.jetbrains.annotations.NotNull;

import java.util.ArrayList;

public abstract class Post {
    private final ArrayList<String> comments = new ArrayList<String>(1);
    private final String username;
    private int likes = 0;
    private final long timestamp;

    public Post(String username) {
        this.username = username;
        this.timestamp = System.currentTimeMillis();
    }

    public void like() {
        likes++;
    }

    public void dislike() {
        if (likes > 0)
            likes--;
    }

    public void addComment(String comment) {
        comments.add(comment);
    }

    public void display() {
        System.out.println(username + " - " + timeString(timestamp) + " - " + likes + " likes - "
                + comments.size() + " " + "comments");
    }

    private static @NotNull String timeString(long timestamp) {
        long currentTime = System.currentTimeMillis();
        long diff = currentTime - timestamp;
        if (diff < 60000)
            return "just now";
        if (diff < 3600000)
            return diff / 60000 + " minutes ago";
        if (diff < 86400000)
            return diff / 3600000 + " hours ago";
        return diff / 86400000 + " days ago";
    }
}