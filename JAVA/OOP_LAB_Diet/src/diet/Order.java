package diet;

import java.util.SortedMap;
import java.util.TreeMap;

/**
 * Represents an order in the take-away system
 */
public class Order {
	
	private User user;
	private Restaurant restaurant;
	private int[] orario = new int[2];
	private OrderStatus newStatus = OrderStatus.ORDERED;
	private PaymentMethod method = PaymentMethod.CASH;
	private SortedMap<String,Integer>menu = new TreeMap<String,Integer>();
 
	public Order(User user, Restaurant restaurant, int h, int m) {
		this.user = user;
		this.restaurant = restaurant;
		orario[0] = h;
		orario[1] = m;
	}
	/**
	 * Defines the possible order status
	 */
	public enum OrderStatus {
		ORDERED, READY, DELIVERED;
	}
	/**
	 * Defines the possible valid payment methods
	 */
	public enum PaymentMethod {
		PAID, CASH, CARD;
	}
		
	/**
	 * Total order price
	 * @return order price
	 */
	public double Price() {
		return -1.0;
	}
	
	/**
	 * define payment method
	 * 
	 * @param method payment method
	 */
	public void setPaymentMethod(PaymentMethod method) {
		this.method = method;
	}
	
	/**
	 * get payment method
	 * 
	 * @return payment method
	 */
	public PaymentMethod getPaymentMethod() {
		
		return method;
	}
	
	/**
	 * change order status
	 * @param newStatus order status
	 */
	public void setStatus(OrderStatus newStatus) {
		this.newStatus = newStatus;
	}
	
	/**
	 * get current order status
	 * @return order status
	 */
	public OrderStatus getStatus(){
		
		return newStatus;
	}
	
	/**
	 * Add a new menu with the relative order to the order.
	 * The menu must be defined in the {@link Food} object
	 * associated the restaurant that created the order.
	 * 
	 * @param menu     name of the menu
	 * @param quantity quantity of the menu
	 * @return this order to enable method chaining
	 */
	public Order addMenus(String menu, int quantity) {
		if(this.menu.containsKey(menu)) {												//se esiste la key restituisce vero
//			this.menu.remove(menu);			//oppure usa questa
			this.menu.replace(menu, quantity);											//serve per modificare la value della key messa, se non esiste la key non fa nulla
		}
		else {
			this.menu.put(menu, quantity);
		}

		return this;
	}
	
	/**
	 * Converts to a string as:
	 * <pre>
	 * RESTAURANT_NAME, USER_FIRST_NAME USER_LAST_NAME : DELIVERY(HH:MM):
	 * 	MENU_NAME_1->MENU_QUANTITY_1
	 * 	...
	 * 	MENU_NAME_k->MENU_QUANTITY_k
	 * </pre>
	 */
	@Override
	public String toString() {
		StringBuffer sb = new StringBuffer();
		sb.append(restaurant.getName()).append(", ").append(user.getFirstName()).append(" ").append(user.getLastName()).append(" : ").append("(");
		if(orario[0] < 10) {
			sb.append("0");
		}
		sb.append(orario[0]).append(":");
		if(orario[1] < 10) {
			sb.append("0");
		}
		sb.append(orario[1]).append("):");
		//System.out.println(sb.toString());
		
		for(String men: menu.keySet()) {													//come stampare una mappa
			sb.append("\n\t").append(men).append("->").append(menu.get(men));
		}
		//System.out.println(sb.toString());
		
		return sb.toString();
	}
	
}
