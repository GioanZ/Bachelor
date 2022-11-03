package gui;

import java.awt.GridLayout;

import javax.swing.*;
import joshua.Player;

public class View extends JFrame{
	private Model model;
	private Controller ctr;
	private JButton[][] buttons;
	public static final String cross="x";
	public static final String circle="O";
	public static void main(String arg[]) {
		Model model= new Model(Player.USER,cross,circle); 
		Controller ctr= new Controller(model);
		View view= new View(model,ctr);
		ctr.setView(view);
		view.setVisible(true);
	}
	public View(Model model, Controller ctr) {
		this.model=model;
		this.ctr=ctr;
		setTitle("TicTacToe"); //titolo schermata 
		setSize(300,300); // dimensione schermata
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setLayout(new GridLayout(3,3)); 
		
		buttons= new JButton[3][3]; //griglia di pulsanti
		for(int i=0;i<3;i++) { //itera sulla griglia
			for(int j=0;j<3;j++) {
				JButton b= new JButton(""); //scritta sul pulsante
				b.setActionCommand(i+","+j); //stampa la posizione che clicco
				b.addActionListener(ctr); //controllo da far partire
				this.add(b);
				buttons[i][j]=b;
				
			}
		}
	
		JMenuItem newGame= new JMenuItem("New Game"); //tendina menu
		JMenuItem settings= new JMenuItem("Settings");
		JMenuItem about= new JMenuItem("About");
		newGame.addActionListener(ctr);
		settings.addActionListener(ctr); //azione dopo che digito
		about.addActionListener(ctr);
		JMenu file= new JMenu("File");
		JMenu help= new JMenu("Help");
		file.add(newGame); //menu con newgame e settings
		file.add(settings);
		help.add(about);
		
		JMenuBar bar= new JMenuBar();
		bar.add(file);
		bar.add(help);
		setJMenuBar(bar); //bara sopra con file e help
	}
	public void selectCell(int i,int j,String symbol) {
		JButton b= buttons[i][j];
		b.setText(symbol);
		b.setEnabled(false);
	}
	public void resetView() {
		for(int i=0;i<3;i++) { //itera sulla griglia
			for(int j=0;j<3;j++) {
				buttons[i][j].setText("");
				buttons[i][j].setEnabled(true);
			}
		}
	}

	
}
	
	
	
	
