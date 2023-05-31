package de.lolgamr17.FSST.projects.MagicMarbles.gui;

import de.lolgamr17.FSST.projects.MagicMarbles.model.MMFieldState;
import de.lolgamr17.FSST.projects.MagicMarbles.model.MMGame;
import de.lolgamr17.FSST.projects.MagicMarbles.model.MMState;
import de.lolgamr17.FSST.projects.MagicMarbles.mvc.*;
import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import javax.swing.event.MouseInputListener;
import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;

public class GUI {

    private int ROWS;
    private int COLS;
    private int WIDTH;
    private int HEIGHT;
    private static final int MARBLE_SIZE = 35;
    private static final int MARBLE_GAP = 5;
    private static final int MARBLE_OFFSET_LEFT = 25;
    private static final int MARBLE_OFFSET_TOP = 25;

    private JFrame frame;
    private BufferedImage graphicsContext;
    private JPanel contentPanel;
    private JLabel contextRender;
    private JPanel scorePanel;
    private JLabel scoreLabel;
    private final MMModel model;
    private final ModelListener listener;

    public GUI(@NotNull MMModel model, int cols, int rows) {
        this.model = model;
        this.listener = new ModelListener();
        this.model.addListener(this.listener);

        init(cols, rows);
    }

    private void init(int cols, int rows) {
        ROWS = rows;
        COLS = cols;
        WIDTH = cols * (MARBLE_SIZE + MARBLE_GAP) + (2 * MARBLE_OFFSET_LEFT);
        HEIGHT = rows * (MARBLE_SIZE + MARBLE_GAP) + (2 * MARBLE_OFFSET_TOP);

        frame = new JFrame("Magic Marbles");
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.setSize(WIDTH, HEIGHT + 95);
        frame.setResizable(false);

        JMenuBar menuBar = new JMenuBar();
        JMenu fileMenu = new JMenu("File");
        JMenu newGameMenu = new JMenu("New Game");
        JMenuItem size_current = new JMenuItem("Current (n)");
        size_current.addActionListener((ignored) -> model.newGame(-1, -1));
        newGameMenu.add(size_current);
        for (int i = 5; i <= 25; i += 5) {
            JMenuItem item = new JMenuItem("%dx%d".formatted(i, i));
            int finalI = i;
            item.addActionListener((ignored) -> model.newGame(finalI, finalI));
            newGameMenu.add(item);
        }
        JMenuItem size_custom = new JMenuItem("Custom (c)");
        size_custom.addActionListener((ignored) -> newCustomGame());
        newGameMenu.add(size_custom);
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
        scoreLabel.setFont(new Font("Roboto", Font.BOLD, 20));
        scorePanel = new JPanel(new GridLayout(1, 2));
        scorePanel.setBorder(new EmptyBorder(0, 0, 5, 0));
        scorePanel.add(scoreLabel, BorderLayout.WEST);

        contentPanel = new JPanel();
        contentPanel.setLayout(new BorderLayout());
        contentPanel.add(contextRender, BorderLayout.NORTH);
        contentPanel.add(scorePanel, BorderLayout.SOUTH);

        frame.add(contentPanel);
        frame.addKeyListener(new KeyListener());
        frame.setVisible(true);
    }

    private void drawField(@NotNull MMGame field) {
        graphicsContext.getGraphics().fillRect(0, 0, WIDTH, HEIGHT);
        for (int i = 0; i < field.getHeight(); i++) {
            for (int j = 0; j < field.getWidth(); j++) {
                drawFigure(j, i, field.getFieldState(i, j));
            }
        }
        contentPanel.repaint();
    }

    private void updateScorePanel(int score) {
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

    private void newCustomGame() {
        String input = JOptionPane.showInputDialog(frame, "Enter the size of the game board (e.g. 10x10)", "Custom Game", JOptionPane.QUESTION_MESSAGE);
        if (input == null) return;
        String[] split = input.split("x");
        if (split.length != 2) {
            JOptionPane.showMessageDialog(frame, "Invalid input!", "Error", JOptionPane.ERROR_MESSAGE);
            return;
        }
        try {
            int width = Integer.parseInt(split[0]);
            int height = Integer.parseInt(split[1]);
            model.newGame(height, width);
        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(frame, "Invalid input!", "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    private class MouseListener implements MouseInputListener {
        @Override
        public void mouseClicked(MouseEvent e) {
            model.marblePressed((e.getX() - MARBLE_OFFSET_LEFT) / (MARBLE_SIZE + MARBLE_GAP),
                    (e.getY() - MARBLE_OFFSET_TOP) / (MARBLE_SIZE + MARBLE_GAP));
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

    private class KeyListener implements java.awt.event.KeyListener {
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
                model.newGame(-1, -1);
            } else if (e.getKeyChar() == 'c') {
                newCustomGame();
            } else if (key > 0 && key <= 5) {
                model.newGame(key * 5, key * 5);
            }
        }
    }

    private class ModelListener implements MMListener {
        @Override
        public void onUpdateField(MMFieldUpdateEvent evt) {
            drawField(evt.getGame());

            if (evt.getGame().getGameState() == MMState.END) {
                int result = JOptionPane.showConfirmDialog(frame, "Game Over!\nYour score: " + evt.getGame().getGamePoints() +
                                "\nDo you want to start a new game with the same size?", "Game Over", JOptionPane.YES_NO_OPTION,
                        JOptionPane.INFORMATION_MESSAGE);
                if (result == 0) {
                    model.newGame(-1, -1);
                }
            }
        }

        @Override
        public void onUpdateScore(MMScoreUpdateEvent evt) {
            updateScorePanel(evt.getScore());
        }

        @Override
        public void onMarblePressed(MMMarblePressedEvent evt) {

        }

        @Override
        public void onNewGame(MMNewGameEvent evt) {
            if ((ROWS != evt.getRows() || COLS != evt.getCols()) && (evt.getRows() != -1 || evt.getCols() != -1)) {
                frame.dispose();
                init(evt.getCols(), evt.getRows());
            }
        }
    }
}