package dev.hofes.DesignPatterns.AdapterPattern.DrawingApp;

public class LineAdapter extends Shape {

    private final Line line;

    public LineAdapter(int x1, int y1, int x2, int y2) {
        super(0, 0);
        this.line = new Line(x1, y1, x2, y2);
    }

    @Override
    public void draw() {
        this.line.showFancyLine();
    }
}