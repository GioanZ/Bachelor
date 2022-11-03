package polito.OOP.ITA3.StackTestP;

import static org.junit.Assert.assertEquals;

import org.junit.Before;
import org.junit.Test;

import polito.OOP.ITA3.JUnitexample.Stack;

public class StackTest1 {
	
	private Stack aStack;
	
	@Before
	public void initialize() {
		aStack = new Stack (10);
	}
	
	@Test
	public void testPop() {
		aStack.push(10);
		assertEquals(10,aStack.pop());
	}

	@Test(expected=ArrayIndexOutOfBoundsException.class)
	public void testPopEmptyStack() {
		aStack.pop();
	}
	
}
