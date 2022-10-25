package polito.OOP.ITA3.JUnitexample;

public class Stack {
	//Vettore in cui salviamo gli elementi dello stack
	private int[] stack;
	//Indice della prima locazione libera in testa allo stack
	private int next;
	
	public Stack(int size) {
		stack = new int[size];
	}
	
	public int pop() {
		return stack[--next];
	}
	
	public boolean push (int i) {
			if (next == stack.length) {
				return false;
			} else {
				stack[next++] = i; 
				return true;
			}
	}	
	
	public boolean isEmpty() {
		return next == 0;
	}
}
