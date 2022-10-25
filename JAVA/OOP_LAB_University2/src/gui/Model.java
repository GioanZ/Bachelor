package gui;

import joshua.Player;
import joshua.TicTacToe;
import joshua.TicTacToeInterface;

public class Model {
	TicTacToeInterface tris;
	String userSymbol;
	String cpuSymbol;
	Player first;
	public Model(Player player,String userSymbol,String cpuSymbol) {
		tris=new TicTacToe(player);
		this.userSymbol= userSymbol;
		this.cpuSymbol= cpuSymbol;
		this.first=player;
	}
	public TicTacToeInterface getTris() {
		return tris;
	}
	public String getUserSymbol() {
		return userSymbol;
	}
	public String getCpuSymbol() {
		return cpuSymbol;
	}
	public Player getFirst() {
		return first;
	}
	
	public TicTacToeInterface getBoard() {
		return tris;
	}
	public void reset() {
		tris.newGame(first);
	}
	public void setTris(TicTacToeInterface tris) {
		this.tris = tris;
	}
	public void setUserSymbol(String userSymbol) {
		this.userSymbol = userSymbol;
	}
	public void setCpuSymbol(String cpuSymbol) {
		this.cpuSymbol = cpuSymbol;
	}
	public void setFirst(Player first) {
		this.first = first;
	}
	
}
