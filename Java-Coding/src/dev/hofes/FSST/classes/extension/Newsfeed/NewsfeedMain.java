package dev.hofes.FSST.classes.extension.Newsfeed;

public class NewsfeedMain {
    public static void main(String[] args) {
        Newsfeed newsfeed = new Newsfeed();

        Post post = new MessagePost("Dalek", "Seas!");
        newsfeed.addPost(post);

        newsfeed.show();

        post.like();
        post.addComment("Nice one!");

        newsfeed.show();
    }
}