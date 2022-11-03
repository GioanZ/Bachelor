package diet;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.SortedMap;
import java.util.TreeMap;

import diet.Order.OrderStatus;

/**
 * Represents a restaurant in the take-away system
 *
 */
public class Restaurant {
	
	private String name;
	private Food food;
	
	private ArrayList<Integer>orari = new ArrayList<Integer>();
	private ArrayList<String>orariS = new ArrayList<String>();

	private Map<String,Menu>menuName = new HashMap<String,Menu>();
	
	private SortedMap<String,Order>order = new TreeMap<String,Order>();
	
	/**
	 * Constructor for a new restaurant.
	 * 
	 * Materials and recipes are taken from
	 * the food object provided as argument.
	 * 
	 * @param name	unique name for the restaurant
	 * @param food	reference food object
	 */
	public Restaurant(String name, Food food) {
		// TODO: implement constructor
		this.name = name;
		this.food = food;
	}
	
	/**
	 * gets the name of the restaurant
	 * 
	 * @return name
	 */
	public String getName() {
		
		return name;
	}
	
	/**
	 * Define opening hours.
	 * 
	 * The opening hours are considered in pairs.
	 * Each pair has the initial time and the final time
	 * of opening intervals.
	 * 
	 * for a restaurant opened from 8:15 until 14:00 and from 19:00 until 00:00, 
	 * is thoud be called as {@code setHours("08:15", "14:00", "19:00", "00:00")}.
	 * 
	 * @param hm a list of opening hours
	 */
	public void setHours(String ... hm) {
		int aperH, chiusH, aperM, chiusM;
		
		for(int i = 0; i < hm.length; i+=2) {
			if(hm.length - i < 2) {
				
				return;
			}
			aperH = Integer.parseInt(hm[i].split(":")[0]);
			aperM = Integer.parseInt(hm[i].split(":")[1]);
			chiusH = Integer.parseInt(hm[i+1].split(":")[0]);
			chiusM = Integer.parseInt(hm[i+1].split(":")[1]);

			if(aperH > 24 || chiusH > 24 || aperM > 60 || chiusM > 60) {
				
				return;
			}
			/*if(aperH > chiusH && chiusH != 0) {

				return;
			}
			if(aperH == chiusH && aperM > chiusM) {

				return;
			}*/
			if(aperH > chiusH) {
				chiusH += 24;
			}
			else if(aperH == chiusH) {
				if(aperM > chiusM) {
					
					return;
				}
			}
			orari.add(aperH);
			orari.add(aperM);
			orari.add(chiusH);
			orari.add(chiusM);
			
			orariS.add(hm[i]);
			orariS.add(hm[i+1]);
		}
	}
	
	public ArrayList<Integer> getOrari() {
		
		return orari;
	}
	
	public ArrayList<String> getOrariS() {
		
		return orariS;
	}
	
	public Menu getMenu(String name) {
		
		return menuName.get(name);
	}
	
	/**
	 * Creates a new menu
	 * 
	 * @param name name of the menu
	 * 
	 * @return the newly created menu
	 */
	public Menu createMenu(String name) {
		Menu m = new Menu(name, food);
		menuName.put(name,m);
		
		return m;
	}
	
	public void addOrderToRestaurant(Order ord, String name) {
		int i = 0;
		
		while(order.get(name) != null) {
			name = name + i++;
		}
		order.put(name, ord);
	}

	/**
	 * Find all orders for this restaurant with 
	 * the given status.
	 * 
	 * The output is a string formatted as:
	 * <pre>
	 * Napoli, Judi Dench : (19:00):
	 * 	M6->1
	 * Napoli, Ralph Fiennes : (19:00):
	 * 	M1->2
	 * 	M6->1
	 * </pre>
	 * 
	 * The orders are sorted by name of restaurant, name of the user, and delivery time.
	 * 
	 * @param status the status of the searched orders
	 * 
	 * @return the description of orders satisfying the criterion
	 */
	public String ordersWithStatus(OrderStatus status) {
		StringBuffer sb = new StringBuffer();
		
		for(String s : order.keySet()) {
			if(order.get(s).getStatus() == status) {
				sb.append(order.get(s).toString()).append("\n");
			}
		}
		
		return sb.toString();
	}
}
