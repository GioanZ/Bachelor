package diet;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.Map;
//import java.util.Collections;
//import java.util.Comparator;
import java.util.SortedMap;
import java.util.TreeMap;

/**
 * Represents the main class in the
 * take-away system.
 * 
 * It allows adding restaurant, users, and creating orders.
 *
 */
public class Takeaway {

	private Map<String,Restaurant>restaurants = new HashMap<String,Restaurant>();
//	private ArrayList<User>usersA = new ArrayList<User>();
	private SortedMap<String,User>users = new TreeMap<String,User>();
	
	/**
	 * Adds a new restaurant to the take-away system
	 * 
	 * @param r the restaurant to be added
	 */
	public void addRestaurant(Restaurant r) {
		restaurants.put(r.getName(),r);
	}
	
	/**
	 * Returns the collections of restaurants
	 * 
	 * @return collection of added restaurants
	 */
	public Collection<String> restaurants() {
		
		return restaurants.keySet();
	}
	
	/**
	 * Define a new user
	 * 
	 * @param firstName first name of the user
	 * @param lastName  last name of the user
	 * @param email     email
	 * @param phoneNumber telephone number
	 * @return
	 */
	public User registerUser(String firstName, String lastName, String email, String phoneNumber) {
		User user = new User(firstName,lastName,email,phoneNumber);
		users.put(lastName + " " + firstName, user);
//		usersA.add(user);
		
		return user;
	}
	
	/**
	 * Gets the collection of registered users
	 * 
	 * @return the collection of users
	 */
	public Collection<User> users(){
//		Collections.sort(usersA, (u1, u2) -> u1.getLastName().compareTo(u2.getLastName()));				//ordina in ordine alfabetico cognome
//		//OPPURE
//		Collections.sort(usersA, new Comparator<User>(){												//ordina in ordine alfabetico cognome e se serve nome
//			@Override
//			public int compare(User u1, User u2) {
//				if(u1.getLastName().compareTo(u2.getLastName())!=0){
//					return u1.getFirstName().compareTo(u2.getFirstName());
//				}
//				
//				return u1.getLastName().compareTo(u2.getLastName());
//			}
//		});
		
		return users.values();																			//come passare da Map a Collection
	}
	
	/**
	 * Create a new order by a user to a given restaurant.
	 * 
	 * The order is initially empty and is characterized
	 * by a desired delivery time. 
	 * 
	 * @param user				user object
	 * @param restaurantName	restaurant name
	 * @param h					delivery time hour
	 * @param m					delivery time minutes
	 * @return
	 */
	public Order createOrder(User user, String restaurantName, int h, int m) {
		Restaurant r = restaurants.get(restaurantName);
		ArrayList<Integer> orari = r.getOrari();
		int flag = 0, trovato = -100000, tempo = h*60 + m;
		int[] oraStmp = new int[2]; 
		Order ord;
		
		for(int i = 0; i < orari.size(); i+=4) {
			if(flag == 1) {
				flag = 0;
				tempo -= 24*60;
			}
			if(orari.get(i+2) >= 24) {
				tempo += 24*60;
				flag = 1;
			}
			
			if(orari.get(i)*60 + orari.get(i+1) <= tempo && tempo <= orari.get(i+2)*60 + orari.get(i+3)) {//trovato
				oraStmp[0] = h;
				oraStmp[1] = m;
				
				break;
			}
			else if(tempo < orari.get(i)*60 + orari.get(i+1) && trovato < tempo - orari.get(i)*60 + orari.get(i+1)) {//ancora non aperto
				trovato = tempo - orari.get(i)*60 + orari.get(i+1);
				oraStmp[0] = orari.get(i);
				oraStmp[1] = orari.get(i+1);
			}
			else if(orari.get(i+2)*60 + orari.get(i+3) < tempo && trovato < tempo - 24*60 - tempo - (orari.get(i)*60 + orari.get(i+1))) {//già chiuso
				trovato = tempo - 24*60 - (orari.get(i)*60 + orari.get(i+1));
				oraStmp[0] = orari.get(i);
				oraStmp[1] = orari.get(i+1);
			}
			
			if(orari.get(i+2) >= 24) {
				tempo -= 24*60;
				flag = 0;
			}
		}
		
		if(flag == 1) {
			flag = 0;
			tempo -= 24*60;
		}
		
		ord = new Order(user,r,oraStmp[0],oraStmp[1]);
		r.addOrderToRestaurant(ord, user.getFirstName() + " " + user.getLastName() + " : (" + (oraStmp[0] < 10 ? "0":"") + oraStmp[0] + ":" + (oraStmp[1] < 10 ? "0":"") + oraStmp[1] + "):");
				
		return ord;
	}
	
	/**
	 * Retrieves the collection of restaurant that are open
	 * at the given time.
	 * 
	 * @param time time to check open
	 * 
	 * @return collection of restaurants
	 */
	public Collection<Restaurant> openedRestaurants(String time){
		SortedMap<String,Restaurant>rist = new TreeMap<String,Restaurant>();
		
		for(String r : restaurants.keySet()) {
			ArrayList<String> or = restaurants.get(r).getOrariS();
			for(int i = 0; i < or.size(); i+=2) {
				if(or.get(i).compareTo(time) <= 0 &&  or.get(i+1).compareTo(time) > 0) {
					rist.put(r, restaurants.get(r));
					
					break;
				}
			}
		}
		return rist.values();
	}

	
	
}
