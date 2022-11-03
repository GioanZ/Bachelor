package gui;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRadioButton;

import joshua.InvalidMoveException;
import joshua.Move;
import joshua.Outcome;
import joshua.Player;
import joshua.TicTacToe;
import joshua.TicTacToeInterface;

public class Controller implements ActionListener{
	private View view;
	private Model model;
	public Controller(Model model) { 
		this.model=model;
	}
	
	public void setView(View view) {
		this.view = view;
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		Object o= e.getSource(); //ci da l'oggetto che ha scatenato l'evento
		// TODO Auto-generated method stub
		if (o instanceof JButton) {	
			
			String[] coord= e.getActionCommand().split(",");
			int i= Integer.valueOf(coord[0]);
			int j= Integer.valueOf(coord[1]);
			System.out.println(i+" "+j); //stampa quello che abbiamo cliccato
			TicTacToeInterface board= model.getBoard(); 
			try {
			
				board.userMove(i, j); 
				view.selectCell(i, j,model.getUserSymbol());  //aggiunge il simbolo
				Outcome out= board.getOutcome(); //ci dice in che situazione siamo
				if(out==Outcome.IN_PROGRESS) {
					Move m= board.cpuMove(); //tocca al computer
					view.selectCell(m.x,m.y,model.getCpuSymbol());
				}
				out= board.getOutcome();
				if(out!= Outcome.IN_PROGRESS) {
					JOptionPane.showMessageDialog(view,out.toString());
					reset();
				}
			} 
			catch (InvalidMoveException e1) {
				// TODO Auto-generated catch block
				System.err.println(e1.getMessage());
			}
		}
		else if(o instanceof JMenuItem) {
			String cmd= e.getActionCommand();
			if(cmd.equals("New Game")) {
				reset();
			}
			else if(cmd.equals("About")) {
				JOptionPane.showMessageDialog(view,"V1.0 lab9");
			}
			else if(cmd.equals("Settings")) { //se clicchiamo sulle impostazioni appare questo
				JPanel panel= new JPanel();
				panel.setLayout(new GridLayout(6,1));
				JLabel l1= new JLabel("Select user symbol: ");	//messaggio che appare
				JRadioButton b1= new JRadioButton(View.cross,View.cross.equals(model.getUserSymbol())); //possibilità
				JRadioButton b2= new JRadioButton(View.circle,View.circle.equals(model.getUserSymbol()));
				ButtonGroup bg1= new ButtonGroup();
				bg1.add(b1);
				bg1.add(b2); //per poterli cliccare
				JLabel l2= new JLabel("Select who starts: ");
				JRadioButton b3= new JRadioButton(Player.CPU.toString(),model.getFirst()==Player.USER);
				JRadioButton b4= new JRadioButton(Player.USER.toString(), model.getFirst()==Player.CPU);
				ButtonGroup bg2= new ButtonGroup();
				bg2.add(b3);
				bg2.add(b4);
				panel.add(l1);
				panel.add(b1);
				panel.add(b2);
				panel.add(l2);
				panel.add(b3);
				panel.add(b4);
				
				JOptionPane.showMessageDialog(view,panel);
				
				if(b1.isSelected()) { //cosa accade quando clicco
					model.setCpuSymbol(View.circle);
					model.setUserSymbol(View.cross);
				}
				else {
					model.setCpuSymbol(View.cross);
					model.setUserSymbol(View.circle);
				}
				if(b3.isSelected()) {
					model.setFirst(Player.CPU);
				}
				else {
					model.setFirst(Player.USER);
				}
				reset();
			}
			else {
				System.err.println("Not implemented");
			}
		}
		else {
			System.err.println("Event not handled");
		}
	}
	
	public void reset() {
		model.reset();
		view.resetView();
		if(model.getFirst()==Player.CPU) {
			try {
				Move m=model.getBoard().cpuMove();
				view.selectCell(m.x,m.y,model.getCpuSymbol());
			}
			catch(InvalidMoveException e){
				System.err.println("Failed to start as CPU");
				model.setFirst(Player.USER);
				reset();
			}
		}
	}
	
	
}
