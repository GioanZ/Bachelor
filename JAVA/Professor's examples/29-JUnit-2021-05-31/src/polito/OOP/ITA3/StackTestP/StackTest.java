package polito.OOP.ITA3.StackTestP;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import polito.OOP.ITA3.JUnitexample.Stack;

public class StackTest {
	
	private Stack aStack;
	
	@Before
	public void initialize() {
		aStack = new Stack(10);
	}
	
	@Test
	public void testPush() {
		assertTrue("Lo stack dovrebbe essere vuoto all'inizio",aStack.isEmpty());
		aStack.push(10);
		assertFalse("Lo stack non dovrebbe essere vuoto dopo un push",aStack.isEmpty());
		aStack.push(4);
		assertEquals(4,aStack.pop());
		assertEquals(10,aStack.pop());
	}

	@Test 
	public void testUpperLimit() {
		assertTrue(aStack.push(1));
		assertTrue(aStack.push(2));
		assertTrue(aStack.push(3));
		assertTrue(aStack.push(4));
		assertTrue(aStack.push(5));
		assertTrue(aStack.push(6));
		assertTrue(aStack.push(7));
		assertTrue(aStack.push(8));
		assertTrue(aStack.push(9));
		assertTrue(aStack.push(10));
		assertFalse(aStack.push(11));
	}
	
	@After
	public void after() {
		
	}

}
