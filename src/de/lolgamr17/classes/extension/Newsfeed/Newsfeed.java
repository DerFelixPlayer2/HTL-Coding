package de.lolgamr17.classes.extension.Newsfeed;

import java.util.ArrayList;

public class Newsfeed {
    private ArrayList<Post> posts = new ArrayList<>();

    public void addPost(Post post) {
        posts.add(post);
    }

    public void show() {
        for (Post post : posts)
            post.display();
    }
}