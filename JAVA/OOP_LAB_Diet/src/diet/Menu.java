package diet;

//import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

/**
 * Represents a complete menu.
 * 
 * It can be made up of both packaged products and servings of given recipes.
 *
 */
public class Menu implements NutritionalElement {
	
	private String name;
	private Food food;
//	private ArrayList<NutritionalElement>piatti = new ArrayList<NutritionalElement>();
//	private ArrayList<Double>dosi = new ArrayList<Double>();
	private Map<NutritionalElement,Double>portate = new HashMap<NutritionalElement,Double>();
	
	private double calories;
	private double proteins;
	private double carbs;
	private double fat;
	
	public Menu(String name, Food food) {
		this.name = name;
		this.food = food;
	}
	
	/**
	 * Adds a given serving size of a recipe.
	 * 
	 * The recipe is a name of a recipe defined in the
	 * {@Link Food} in which this menu has been defined.
	 * 
	 * @param recipe the name of the recipe to be used as ingredient
	 * @param quantity the amount in grams of the recipe to be used
	 * @return the same Menu to allow method chaining
	 */
	public Menu addRecipe(String recipe, double quantity) {
		NutritionalElement r = food.getRecipe(recipe);
		
		if(r != null) {
			portate.put(r, quantity);
//			piatti.add(r);
//			dosi.add(quantity);
			this.calories += r.getCalories() * (quantity/100);
			this.proteins += r.getProteins() * (quantity/100);
			this.carbs += r.getCarbs() * (quantity/100);
			this.fat += r.getFat() * (quantity/100);
		}
		
		return this;
	}

	/**
	 * Adds a unit of a packaged product.
	 * The product is a name of a product defined in the
	 * {@Link Food} in which this menu has been defined.
	 * 
	 * @param product the name of the product to be used as ingredient
	 * @return the same Menu to allow method chaining
	 */
	public Menu addProduct(String product) {
		NutritionalElement p = food.getProduct(product);
		
		if(p != null) {
			portate.put(p, null);
//			piatti.add(p);
//			dosi.add((double) -1);
			this.calories += p.getCalories();
			this.proteins += p.getProteins();
			this.carbs += p.getCarbs();
			this.fat += p.getFat();
		}
		
		return this;
	}

	/**
	 * Name of the menu
	 */
	@Override
	public String getName() {
		return name;
	}

	/**
	 * Total KCal in the menu
	 */
	@Override
	public double getCalories() {
		return calories;
	}

	/**
	 * Total proteins in the menu
	 */
	@Override
	public double getProteins() {
		return proteins;
	}

	/**
	 * Total carbs in the menu
	 */
	@Override
	public double getCarbs() {
		return carbs;
	}

	/**
	 * Total fats in the menu
	 */
	@Override
	public double getFat() {
		return fat;
	}

	/**
	 * Indicates whether the nutritional values returned by the other methods
	 * refer to a conventional 100g quantity of nutritional element,
	 * or to a unit of element.
	 * 
	 * For the {@link Menu} class it must always return {@code false}:
	 * nutritional values are provided for the whole menu.
	 * 
	 * @return boolean 	indicator
	 */
	@Override
	public boolean per100g() {
		// nutritional values are provided for the whole menu.
		return false;
	}
}
