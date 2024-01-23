package dev.hofes.FSST.classes.extension.Newsfeed;

public class PhotoPost extends Post {
    private final String filename;
    private final String caption;

    public PhotoPost(String user, String filename, String caption) {
        super(user);
        this.filename = filename;
        this.caption = caption;
    }

    public String getCaption() {
        return caption;
    }

    public String getFilename() {
        return filename;
    }

    @Override
    public void display() {
        super.display();
        System.out.println("Filename: " + filename);
        System.out.println("Caption: " + caption);
    }
}