package dev.hofes.DesignPatterns.CompositePattern.DrawingApp;

public class AwesomeDrawingApp {

    private final Shape s;

    AwesomeDrawingApp(Shape s) {
        this.s = s;
        Window.open();
    }

    private void show() {
        s.draw();
    }

    public static void main(String[] args) throws InterruptedException {
        var s = new Snowman(100, 100, 50, 1.3);
        AwesomeDrawingApp app = new AwesomeDrawingApp(s);
        app.show();

        while(true) {
            Thread.sleep(10);
            s.move(10, 10);
        }
    }
}