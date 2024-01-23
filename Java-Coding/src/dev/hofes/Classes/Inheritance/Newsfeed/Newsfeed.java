package dev.hofes.Classes.Inheritance.Newsfeed;

import java.util.ArrayList;

public class Newsfeed {
    private final ArrayList<Post> posts = new ArrayList<>();

    public void addPost(Post post) {
        posts.add(post);
    }

    public void show() {
        for (Post post : posts)
            post.display();
    }
}