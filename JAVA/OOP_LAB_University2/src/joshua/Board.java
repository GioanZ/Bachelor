package joshua;

public class Board {
	
	Player[][] board;
	
	public Board() {
		board = new Player[3][3];
	}
	
	public void addMark(Player mark, int x, int y) throws InvalidMoveException {
		checkPosition(x, y);
		if(board[x][y] != null) {
			throw new InvalidMoveException("Cell occupied: [" + x + "," + y + "]");
		}
		board[x][y] = mark;
	}
	
	public Player getMark(int x, int y) throws InvalidMoveException {
		checkPosition(x,y);
		return board[x][y];
	}
	
	public void removeMark(int x, int y) throws InvalidMoveException {
		checkPosition(x,y);
		board[x][y] = null;
	}
	
	public Player checkWon() {
		for(Player[] row : board) {
			if(row[0] == row[1] && row[1] == row[2] && row[0]!= null) {
				return row[0];
			}
		}
		for(int y = 0; y < 3; ++y) {
			if(board[0][y] == board[1][y] && board[1][y] == board[2][y] && board[2][y]!= null) {
				return board[0][y];
			}
		}
		if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board [0][0]!= null) {
			return board[0][0];
		}
		if(board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2]!= null) {
			return board[0][2];
		}
		return null;
	}
	
	private void checkPosition(int x, int y) throws InvalidMoveException{
		if(x > 2 | x < 0 | y > 2 | y < 0) {
			throw new InvalidMoveException("Invalid position: [" + x + "," + y + "]");			
		}
	}
}
