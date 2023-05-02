package de.lolgamr17.FSST.projects.MagicMarbles.gui;

import de.lolgamr17.FSST.projects.MagicMarbles.MagicMarblesMain;
import de.lolgamr17.FSST.projects.MagicMarbles.model.MMFieldState;
import de.lolgamr17.FSST.projects.MagicMarbles.model.MMGame;
import de.lolgamr17.FSST.projects.MagicMarbles.model.MMState;
import de.lolgamr17.FSST.projects.MagicMarbles.mvc.MMModel;
import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import javax.swing.event.MouseInputListener;
import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.util.prefs.Preferences;

public class GUI {

    private final int WIDTH;
    private final int HEIGHT;
    private static final int MARBLE_SIZE = 35;
    private static final int MARBLE_GAP = 5;
    private static final int MARBLE_OFFSET_LEFT = 25;
    private static final int MARBLE_OFFSET_TOP = 25;

    private final JFrame frame;
    private final BufferedImage graphicsContext;
    private final JPanel contentPanel;
    private final JLabel contextRender;
    private final JPanel scorePanel;
    private final JLabel scoreLabel;
    private final JLabel highScoreLabel;
    private MMModel model;

    public GUI(@NotNull MMModel model, int cols, int rows) {
        WIDTH = cols * (MARBLE_SIZE + MARBLE_GAP) + (2 * MARBLE_OFFSET_LEFT);
        HEIGHT = rows * (MARBLE_SIZE + MARBLE_GAP) + (2 * MARBLE_OFFSET_TOP);
        setModel(model);

        frame = new JFrame("Magic Marbles");
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.setSize(WIDTH, HEIGHT + 95);
        frame.setResizable(false);

        JMenuBar menuBar = new JMenuBar();
        JMenu fileMenu = new JMenu("File");
        JMenu newGameMenu = new JMenu("New Game");
        JMenuItem size_current = new JMenuItem("Current");
        size_current.addActionListener((ignored) -> MagicMarblesMain.onNewGame(-1, -1));
        newGameMenu.add(size_current);
        for (int i = 5; i <= 25; i += 5) {
            JMenuItem item = new JMenuItem("%dx%d".formatted(i, i));
            int finalI = i;
            item.addActionListener((ignored) -> MagicMarblesMain.onNewGame(finalI, finalI));
            newGameMenu.add(item);
        }
        fileMenu.add(newGameMenu);
        JMenuItem exitMenu = new JMenuItem("Exit");
        exitMenu.addActionListener(e -> System.exit(0));
        fileMenu.add(exitMenu);
        menuBar.add(fileMenu);
        frame.setJMenuBar(menuBar);

        graphicsContext = new BufferedImage(WIDTH, HEIGHT, BufferedImage.TYPE_INT_RGB);
        graphicsContext.getGraphics().fillRect(0, 0, WIDTH, HEIGHT);
        contextRender = new JLabel(new ImageIcon(graphicsContext));
        contextRender.addMouseListener(new MouseListener());

        scoreLabel = new JLabel("Score: 0", SwingConstants.CENTER);
        highScoreLabel = new JLabel("High Score: 0", SwingConstants.LEFT);
        scoreLabel.setFont(new Font("Roboto", Font.BOLD, 20));
        highScoreLabel.setFont(new Font("Roboto", Font.BOLD, 20));
        scorePanel = new JPanel(new GridLayout(1, 2));
        scorePanel.setBorder(new EmptyBorder(0, 0, 5, 0));
        scorePanel.add(scoreLabel, BorderLayout.WEST);
        scorePanel.add(highScoreLabel, BorderLayout.EAST);

        contentPanel = new JPanel();
        contentPanel.setLayout(new BorderLayout());
        contentPanel.add(contextRender, BorderLayout.NORTH);
        contentPanel.add(scorePanel, BorderLayout.SOUTH);

        frame.add(contentPanel);
        frame.addKeyListener(new KeyListener());
        frame.setVisible(true);
    }

    public void close() {
//        frame.setVisible(false);
        frame.dispose();
    }

    public void setModel(@NotNull MMModel model) {
        this.model = model;
        model.addListener(e -> {
            drawField(e.getGame());
            updateScore(e.getGame().getGamePoints());
            if (e.getGame().getGameState() == MMState.END) {
                int result = JOptionPane.showConfirmDialog(frame, "Game Over!\nYour score: " + e.getGame().getGamePoints() +
                                "\nDo you want to start a new game with the same size?", "Game Over", JOptionPane.YES_NO_OPTION,
                        JOptionPane.INFORMATION_MESSAGE);
                if (result == 0) {
                    MagicMarblesMain.onNewGame(-1, -1);
                }
            }

        });
    }

    private void drawField(@NotNull MMGame field) {
        graphicsContext.getGraphics().fillRect(0, 0, WIDTH, HEIGHT);
        for (int i = 0; i < field.getHeight(); i++) {
            for (int j = 0; j < field.getWidth(); j++) {
                drawFigure(i, j, field.getFieldState(j, i));
            }
        }
        contentPanel.repaint();
    }

    private void updateScore(int score) {
        final Preferences preferences = Preferences.userRoot().node(this.getClass().getName());
        final int highScore = Math.max(score, preferences.getInt("highScore", 0));

        preferences.putInt("highScore", highScore);
        highScoreLabel.setText("High Score: " + highScore);
        scoreLabel.setText("Score: " + score);

        scorePanel.repaint();
    }

    private void drawFigure(int x, int y, @NotNull MMFieldState state) {
        Graphics2D g = graphicsContext.createGraphics();
        g.setRenderingHints(new RenderingHints(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON));
        g.setColor(getColor(state));
        g.fillOval(x * (MARBLE_SIZE + MARBLE_GAP) + MARBLE_OFFSET_LEFT, y * (MARBLE_SIZE + MARBLE_GAP) + MARBLE_OFFSET_TOP,
                MARBLE_SIZE,
                MARBLE_SIZE);
        g.dispose();
    }

    @Contract(pure = true)
    private Color getColor(@NotNull MMFieldState state) {
        return switch (state) {
            case GREEN -> Color.GREEN;
            case RED -> Color.RED;
            case BLUE -> Color.BLUE;
            default -> Color.WHITE;
        };
    }

    private static class MouseListener implements MouseInputListener {
        @Override
        public void mouseClicked(MouseEvent e) {
            // TODO: refine
            MagicMarblesMain.onMarblePressed((e.getY() - MARBLE_OFFSET_TOP) / (MARBLE_SIZE + MARBLE_GAP),
                    (e.getX() - MARBLE_OFFSET_LEFT) / (MARBLE_SIZE + MARBLE_GAP));
        }

        @Override
        public void mousePressed(MouseEvent e) {

        }

        @Override
        public void mouseReleased(MouseEvent e) {

        }

        @Override
        public void mouseEntered(MouseEvent e) {

        }

        @Override
        public void mouseExited(MouseEvent e) {

        }

        @Override
        public void mouseDragged(MouseEvent e) {

        }

        @Override
        public void mouseMoved(MouseEvent e) {

        }
    }

    private static class KeyListener implements java.awt.event.KeyListener {
        @Override
        public void keyTyped(KeyEvent e) {

        }

        @Override
        public void keyPressed(KeyEvent e) {

        }

        @Override
        public void keyReleased(KeyEvent e) {
            int key = (int) e.getKeyChar() - (int) '0';

            if (e.getKeyChar() == 'n' || key == 0) {
                MagicMarblesMain.onNewGame(-1, -1);
            } else if (key <= 5) {
                MagicMarblesMain.onNewGame(key * 5, key * 5);
            }
        }
    }
}