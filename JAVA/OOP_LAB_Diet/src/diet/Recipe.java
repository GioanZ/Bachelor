package diet;

import java.util.ArrayList;

/**
 * Represents a recipe of the diet.
 * 
 * A recipe consists of a a set of ingredients that are given amounts of raw materials.
 * The overall nutritional values of a recipe can be computed
 * on the basis of the ingredients' values and are expressed per 100g
 * 
 *
 */
public class Recipe implements NutritionalElement {
    
	private String name;
	private double calories;
	private double proteins;
	private double carbs;
	private double fat;
	//private boolean per100g;
	private double quantity;
	
	private Food food;
	
	private ArrayList<Ingrediente>ingredienti = new ArrayList<Ingrediente>();

	public Recipe(String name, Food food) {
		this.name = name;
		this.food = food;
	}
	
	/**
	 * Adds a given quantity of an ingredient to the recipe.
	 * The ingredient is a raw material.
	 * 
	 * @param material the name of the raw material to be used as ingredient
	 * @param quantity the amount in grams of the raw material to be used
	 * @return the same Recipe object, it allows method chaining.
	 */
	public Recipe addIngredient(String material, double quantity) {
		NutritionalElement nEl = food.getRawMaterial(material);
		
		ingredienti.add(new Ingrediente(nEl, quantity));
		
		this.calories += nEl.getCalories() * (quantity/100);
		this.proteins += nEl.getProteins() * (quantity/100);
		this.carbs += nEl.getCarbs() * (quantity/100);
		this.fat += nEl.getFat() * (quantity/100);
		this.quantity += quantity;
		
		return this;
	}

	@Override
	public String getName() {
		return name;
	}

	@Override
	public double getCalories() {
		return calories * (100/quantity);
	}

	@Override
	public double getProteins() {
		return proteins * (100/quantity);
	}

	@Override
	public double getCarbs() {
		return carbs * (100/quantity);
	}

	@Override
	public double getFat() {
		return fat * (100/quantity);
	}

	/**
	 * Indicates whether the nutritional values returned by the other methods
	 * refer to a conventional 100g quantity of nutritional element,
	 * or to a unit of element.
	 * 
	 * For the {@link Recipe} class it must always return {@code true}:
	 * a recipe expresses nutritional values per 100g
	 * 
	 * @return boolean indicator
	 */
	@Override
	public boolean per100g() {
		return true;
	}
	
	
	/**
	 * Returns the ingredients composing the recipe.
	 * 
	 * A string that contains all the ingredients, one per per line, 
	 * using the following format:
	 * {@code "Material : ###.#"} where <i>Material</i> is the name of the 
	 * raw material and <i>###.#</i> is the relative quantity. 
	 * 
	 * Lines are all terminated with character {@code '\n'} and the ingredients 
	 * must appear in the same order they have been added to the recipe.
	 */
	@Override
	public String toString() {
		StringBuffer sb = new StringBuffer();
		for(Ingrediente ingr : ingredienti) {
			sb.append(ingr.getName()).append(": ").append(ingr.getQuantity()).append("\n");
		}
		
		return sb.toString();
	}
}
