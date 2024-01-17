package de.lolgamr17.FSST.projects.MagicMarbles.model;

import de.lolgamr17.FSST.projects.MagicMarbles.mvc.MMListener;

import java.io.IOException;
import java.util.EventObject;

/**
 * Definition of a magic marbles game.
 */
public interface MMGame {

	void addListener(MMListener listener);

//	void emit(EventObject e);


	/**
	 * Width of the game board, i.e. the number of columns.
	 * 
	 * @return The width of the game board.
	 */
	int getWidth();

	/**
	 * Height of the game board, i.e. the number of rows.
	 * 
	 * @return The width of the field.
	 */
	int getHeight();

	void reset(int rows, int cols);

	/**
	 * The overall state of the game.
	 * 
	 * @return The game state.
	 */
	MMState getGameState();

	/**
	 * The current number of game points achieved.
	 * 
	 * @return The game points.
	 */
	int getGamePoints();

	MMFieldState[][] getField();
	
	/**
	 * The state of an individual field.
	 * 
	 * @param col
	 *            The column of the field to query.
	 * @param row
	 *            The row of the field to query.
	 * @return The state of the specified field.
	 */
	MMFieldState getFieldState(int row, int col);

	void select(int row, int col) throws MMException;

}