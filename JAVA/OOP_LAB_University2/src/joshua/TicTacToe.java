package joshua;

public class TicTacToe implements TicTacToeInterface {
	
	Board board;
	Player currentPlayer;
	Outcome outcome;
	int turn;
	
	public TicTacToe(Player first) {
		newGame(first);
	}

	@Override
	public void newGame(Player first) {
		this.board = new Board();
		this.currentPlayer = first;
		outcome = Outcome.IN_PROGRESS;
		turn = 0;
	}

	@Override
	public void userMove(int x, int y) throws InvalidMoveException {
		checkTurn(Player.USER);
		board.addMark(Player.USER, x, y);
		currentPlayer = Player.CPU;
		turn++;
		updateOutcome();
	}

	@Override
	public Move cpuMove() throws InvalidMoveException {
		checkTurn(Player.CPU);
		Move best = new Move();
		int payoff = negaMax(board, turn, Player.CPU, best);
		board.addMark(Player.CPU, best.x, best.y);
		currentPlayer = Player.USER;
		turn++;
		updateOutcome();
		return best;
	}

	@Override
	public Outcome getOutcome() {
		return outcome;
	}

	@Override
	public Player getCurrentPlayer() {
		return currentPlayer;
	}
	
	private void checkTurn(Player player) throws InvalidMoveException {
		if(turn >= 9 || outcome != Outcome.IN_PROGRESS) {
			throw new InvalidMoveException("Game finished");
		}
		if(currentPlayer != player) {
			throw new InvalidMoveException("Not turn of player: " + player.toString());
		}
	}
	
	private void updateOutcome() {
		Player winner = board.checkWon();
		if(winner == Player.USER) {
			outcome = Outcome.USER_WON;
		}
		else if (winner == Player.CPU) {
			outcome = Outcome.CPU_WON;
		}
		else if(turn < 9) {
			outcome = Outcome.IN_PROGRESS;
		}
		else {
			outcome = Outcome.DRAW;
		}
	}
	
	private int negaMax(Board board, int turn, Player player, Move bestMove) throws InvalidMoveException {
		Player winner = board.checkWon();
		if(winner!= null || turn == 9) {
			if(winner == null) {
				return 0;
			}
			if(winner == player) {
				return -1;
			}
			return 1;
		}
		int bestPayoff = -2;
		for(int x = 0;  x < 3; ++x) {
			for(int y = 0; y < 3; ++y) {
				if(board.getMark(x, y) == null) {
					board.addMark(player, x, y);
					Player nextPlayer = (player == Player.CPU ? Player.USER : Player.CPU);						
					Move newBestMove = new Move();
					int payoff = negaMax(board, turn + 1, nextPlayer, newBestMove);
					if(payoff > bestPayoff) {
						bestMove.x = x;
						bestMove.y = y;
						bestPayoff = payoff;
					}
					board.removeMark(x, y);
				}
			}
		}
		return -bestPayoff;
	}
}
