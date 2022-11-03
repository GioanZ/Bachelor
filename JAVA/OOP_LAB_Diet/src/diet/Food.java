package diet;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;

/**
 * Facade class for the diet management.
 * It allows defining and retrieving raw materials and products.
 *
 */
public class Food {
	
	private ArrayList<NutritionalElement>materiePrime = new ArrayList<NutritionalElement>();
	private ArrayList<NutritionalElement>prodotti = new ArrayList<NutritionalElement>();
	private ArrayList<NutritionalElement>ricette = new ArrayList<NutritionalElement>();
	private ArrayList<NutritionalElement>menu = new ArrayList<NutritionalElement>();
	
	/**
	 * Define a new raw material.
	 * 
	 * The nutritional values are specified for a conventional 100g amount
	 * @param name 		unique name of the raw material
	 * @param calories	calories per 100g
	 * @param proteins	proteins per 100g
	 * @param carbs		carbs per 100g
	 * @param fat 		fats per 100g
	 */
	public void defineRawMaterial(String name, double calories, double proteins, double carbs, double fat){
		materiePrime.add(new Alimento(name, calories, proteins, carbs, fat, true));
		Collections.sort(materiePrime, (al1,al2) 
												-> al1.getName().compareTo(al2.getName()));
	}
	
	/**
	 * Retrieves the collection of all defined raw materials
	 * 
	 * @return collection of raw materials though the {@link NutritionalElement} interface
	 */
	public Collection<NutritionalElement> rawMaterials(){
		
		return materiePrime;
	}
	
	/**
	 * Retrieves a specific raw material, given its name
	 * 
	 * @param name  name of the raw material
	 * 
	 * @return  a raw material though the {@link NutritionalElement} interface
	 */
	public NutritionalElement getRawMaterial(String name){
		for(NutritionalElement mat: materiePrime) {
			if(mat.getName().equals(name)) {											//equal: confronta e se sono uguali "mat" e "name", se sono uguali allora entrs in IF
				
				return mat;
			}
		}
		
		return null;
	}

	/**
	 * Define a new packaged product.
	 * The nutritional values are specified for a unit of the product
	 * 
	 * @param name 		unique name of the product
	 * @param calories	calories for a product unit
	 * @param proteins	proteins for a product unit
	 * @param carbs		carbs for a product unit
	 * @param fat 		fats for a product unit
	 */
	public void defineProduct(String name,  double calories, double proteins, double carbs, double fat){
		prodotti.add(new Alimento(name, calories, proteins, carbs, fat, false));
		Collections.sort(prodotti, (al1,al2) 
											-> al1.getName().compareTo(al2.getName()));
	}
	
	/**
	 * Retrieves the collection of all defined products
	 * 
	 * @return collection of products though the {@link NutritionalElement} interface
	 */
	public Collection<NutritionalElement> products(){
		return prodotti;
	}
	
	/**
	 * Retrieves a specific product, given its name
	 * @param name  name of the product
	 * @return  a product though the {@link NutritionalElement} interface
	 */
	public NutritionalElement getProduct(String name){
		for(NutritionalElement prod: prodotti) {
			if(prod.getName().equals(name)) {											//equal: confronta e se sono uguali "prod" e "name", se sono uguali allora entrs in IF
				
				return prod;
			}
		}
		
		return null;
	}
	
	/**
	 * Creates a new recipe stored in this Food container.
	 *  
	 * @param name name of the recipe
	 * 
	 * @return the newly created Recipe object
	 */
	public Recipe createRecipe(String name) {
		Recipe ric = new Recipe(name, this);
		ricette.add(ric);
		Collections.sort(ricette, (ric1,ric2) 
											-> ric1.getName().compareTo(ric2.getName()));
		
		return ric;
	}
	
	/**
	 * Retrieves the collection of all defined recipes
	 * 
	 * @return collection of recipes though the {@link NutritionalElement} interface
	 */
	public Collection<NutritionalElement> recipes(){
		return ricette;
	}
	
	/**
	 * Retrieves a specific recipe, given its name
	 * 
	 * @param name  name of the recipe
	 * 
	 * @return  a recipe though the {@link NutritionalElement} interface
	 */
	public NutritionalElement getRecipe(String name){	
		for(NutritionalElement ricet: ricette) {
			if(ricet.getName().equals(name)) {											//equal: confronta e se sono uguali "ricet" e "name", se sono uguali allora entrs in IF
				
				return ricet;
			}
		}
		
		return null;
	}
	
	/**
	 * Creates a new menu
	 * 
	 * @param name name of the menu
	 * 
	 * @return the newly created menu
	 */
	public Menu createMenu(String name) {
		Menu men = new Menu(name, this);
		menu.add(men);
		Collections.sort(menu, (men1,men2) 
										-> men1.getName().compareTo(men2.getName()));
		
		return men;
	}
	
}
