package dev.hofes.FSST.design_patterns.adapter.drawing_app;

public class AwesomeDrawingApp {

    private final Shape s;

    AwesomeDrawingApp(Shape s) {
        this.s = s;
        Window.open();
    }

    private void show() {
        s.draw();
    }

    public static void main(String[] args) {
        AwesomeDrawingApp app = new AwesomeDrawingApp(new LineAdapter(100, 100, 200, 200));
        app.show();
    }
}