package joshua;

public interface TicTacToeInterface {	
	
	public void newGame(Player first);
	public void userMove(int x, int y) throws InvalidMoveException;
	public Move cpuMove() throws InvalidMoveException;
	public Outcome getOutcome();
	public Player getCurrentPlayer();
}
