
public class Contatore {
	
	private int valore;
	
	public Contatore() {
		valore = 0;
	}
	
	public void increment() {
		this.valore++;
	}
	
	public void decrement() {
		this.valore--;
	}
	
	public int getValore() {
		return valore;
	}

}
