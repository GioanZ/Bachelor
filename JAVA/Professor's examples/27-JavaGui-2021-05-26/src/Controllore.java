
public class Controllore {
	
	private Contatore modello;
	private Vista vista;
	
	public Controllore(Contatore modello, Vista vista) {
		this.modello = modello;
		this.vista = vista;
		this.vista.piu.
		addActionListener(e -> eseguiIncremento());
		this.vista.meno.
		addActionListener(e -> eseguiDecremento());
	}
	
	public void eseguiIncremento() {
		this.modello.increment();
		this.vista.update();
		
	}
	
	public void eseguiDecremento() {
		this.modello.decrement();
		this.vista.update();
	}

}
