package diet;

public class Ingrediente {
	
	private NutritionalElement alimento;
	private double quantity;
	
	public Ingrediente(NutritionalElement alimento, double quantity) {
		this.alimento = alimento;
		this.quantity = quantity;
	}

	public NutritionalElement getAlimento() {
		return alimento;
	}
	
	public String getName() {
		return alimento.getName();
	}
	
	public double getQuantity() {
		return quantity;
	}
}
