import java.awt.BorderLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.SwingConstants;

public class Vista extends JFrame {

	public JButton piu = new JButton("+"); 
	public JButton meno = new JButton("-");
	public JLabel valore = 
			new JLabel ("",SwingConstants.CENTER);
	private Contatore modello;
	
	
	public Vista(Contatore modello) {
		this.setTitle("Applicazione Contatore");
		this.setSize(400,400);
		this.setLayout(new BorderLayout());
		this.add(piu,BorderLayout.NORTH);
		this.add(meno,BorderLayout.SOUTH);
		this.add(valore,BorderLayout.CENTER);
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		this.setVisible(true);
		this.modello = modello;
		this.update();
	}
	
	public void update() {
		int v = this.modello.getValore();
		this.valore.setText(Integer.toString(v));
		
	}
	
}
