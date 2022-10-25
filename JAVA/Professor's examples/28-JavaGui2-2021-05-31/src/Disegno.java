import java.awt.Color;
import java.awt.Graphics;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class Disegno extends JFrame {
	
	public class MyPanel extends JPanel {
		int x,y =0;
		public void paint (Graphics g) {
			//Disegna una line tra i punti
			//di coordinta (0,0) e (200,200)
			g.drawLine(0,0,200,200);
			//Disegna un rettangolo pieno
			//il cui vertice in alto a sinista
			//è nel punto (200,200) e largo 200
			//altro 200
			g.fillRect(200, 200, 200, 200);
			//Settiamo il colore al blue
			g.setColor(Color.BLUE);
			//Disegno rettangolo con vertice
			//dipendente da x,y
			g.fillRect(x, y, 10, 10);
			x += 10;
			y += 10;
			
		}
	
	}
	
	public Disegno() {
		setTitle("Esempio grafico in Java");
		setSize(400,400);
		MyPanel pannello = new MyPanel();
		add(pannello);
		
		Thread t = new Thread(() -> {
			try {
				while (true) {
					Thread.sleep(300);
					repaint();
				}
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		});
		t.start();
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setVisible(true);
	}

}
