package de.lolgamr17.FSST.projects.MagicMarbles.model;

import de.lolgamr17.FSST.projects.MagicMarbles.mvc.*;
import org.jetbrains.annotations.Contract;

import java.util.Random;

/**
 * Implementation of the magic marbles game
 */
public class MMGameImpl implements MMGame {

    private int width, height;
    private MMFieldState[][] field;
    private MMState state;
    private int score;
    private final MMModel model;

    /**
     * Constructor
     *
     * @param width  the width of the game board
     * @param height the height of the game board
     */
    public MMGameImpl(int width, int height, MMModel model) {
        this.model = model;
        this.model.addListener(new Listener());

        reset(height, width);
    }

    public void reset(int rows, int cols) {
        if (rows == -1) rows = this.height;
        if (cols == -1) cols = this.width;

        if (this.height != rows || this.width != cols) {
            this.height = rows;
            this.width = cols;
            field = new MMFieldState[rows][cols];
        }

        final Random r = new Random();
        for (int col = 0; col < width; col++)
            for (int row = 0; row < height; row++)
                field[row][col] = MMFieldState.values()[r.nextInt(3)];

        state = MMState.RUNNING;
        score = 0;

        this.model.updateField(this);
        this.model.updateScore(score);
    }

    @Override
    public int getWidth() {
        return width;
    }

    @Override
    public int getHeight() {
        return height;
    }

    @Override
    public MMState getGameState() {
        return state;
    }

    @Override
    public int getGamePoints() {
        return score;
    }

    @Override
    public MMFieldState getFieldState(int row, int col) {
        return this.field[row][col];
    }

    @Override
    public void select(int row, int col) throws MMException {
        if (row < 0 || row >= height || col < 0 || col >= width)
            throw new MMException("Field must be within bounds.");
        if (field[row][col] == MMFieldState.EMPTY)
            throw new MMException("Field has to contain a marble.");

        final int count = countConnected(row, col);
        if (count < 2) {
            throw new MMException("Field must be connected to at least one other field.");
        }

        removeConnected(row, col);
        score += count * count;

        while (updatePositions()) ;
        while (removeEmptyCols()) ;

        if (isGameOver()) {
            state = MMState.END;

            int c = 0;
            for (int _col = 0; _col < width; _col++)
                for (int _row = 0; _row < height; _row++)
                    c += getFieldState(_row, _col) == MMFieldState.EMPTY ? 0 : 1;
            score -= c;
        }

        model.updateField(this);
        model.updateScore(score);
    }

    @Contract(pure = true)
    private int countConnected(int row, int col) {
        MMFieldState[][] field = new MMFieldState[this.getHeight()][this.getWidth()];
        for (int i = 0; i < this.getWidth(); i++)
            for (int j = 0; j < this.getHeight(); j++)
                field[j][i] = this.getFieldState(j, i);

        return _countConnected(row, col, field);
    }

    private int _countConnected(int row, int col, MMFieldState[][] field) {
        final MMFieldState state = field[row][col];
        field[row][col] = MMFieldState.EMPTY;

        int count = 1;
        if (row > 0 && field[row - 1][col] == state)
            count += _countConnected(row - 1, col, field);
        if (row < height - 1 && field[row + 1][col] == state)
            count += _countConnected(row + 1, col, field);
        if (col > 0 && field[row][col - 1] == state)
            count += _countConnected(row, col - 1, field);
        if (col < width - 1 && field[row][col + 1] == state)
            count += _countConnected(row, col + 1, field);

        return count;
    }

    private void removeConnected(int row, int col) {
        final MMFieldState state = field[row][col];
        field[row][col] = MMFieldState.EMPTY;

        if (row > 0 && field[row - 1][col] == state)
            removeConnected(row - 1, col);
        if (row < height - 1 && field[row + 1][col] == state)
            removeConnected(row + 1, col);
        if (col > 0 && field[row][col - 1] == state)
            removeConnected(row, col - 1);
        if (col < width - 1 && field[row][col + 1] == state)
            removeConnected(row, col + 1);
    }

    private boolean updatePositions() {
        boolean moved = false;
        for (int col = getWidth() - 1; col >= 0; col--) {
            for (int row = getHeight() - 1; row >= 0; row--) {
                if (getFieldState(row, col) == MMFieldState.EMPTY) {
                    for (int _row = row - 1; _row >= 0; _row--) {
                        field[_row + 1][col] = field[_row][col];
                        if (field[_row][col] != MMFieldState.EMPTY) moved = true;
                    }
                    field[0][col] = MMFieldState.EMPTY;
                }
            }
        }
        return moved;
    }

    private boolean removeEmptyCols() {
        boolean moved = false;
        for (int col = getWidth() - 1; col >= 0; col--) {
            if (getFieldState(getHeight() - 1, col) == MMFieldState.EMPTY) {
                for (int _col = col - 1; _col >= 0; _col--) {
                    for (int row = 0; row < getHeight(); row++) {
                        if (field[row][_col] != MMFieldState.EMPTY) moved = true;
                        field[row][_col + 1] = field[row][_col];
                    }
                }
                for (int row = 0; row < getHeight(); row++) {
                    field[row][0] = MMFieldState.EMPTY;
                }
            }
        }
        return moved;
    }

    @Contract(pure = true)
    private boolean isGameOver() {
        for (int row = 0; row < height; row++)
            for (int col = 0; col < width; col++) {
                if (getFieldState(row, col) != MMFieldState.EMPTY) {
                    final int count = countConnected(row, col);
                    if (count >= 2)
                        return false;
                }
            }
        return true;
    }

    private class Listener implements MMListener {
        @Override
        public void onUpdateField(MMFieldUpdateEvent evt) {

        }

        @Override
        public void onUpdateScore(MMScoreUpdateEvent evt) {

        }

        @Override
        public void onMarblePressed(MMMarblePressedEvent evt) {
            try {
                select(evt.getY(), evt.getX());
            } catch (MMException e) {
                System.out.printf(e.getMessage());
            }
        }

        @Override
        public void onNewGame(MMNewGameEvent evt) {
            reset(evt.getRows(), evt.getCols());
        }
    }

}