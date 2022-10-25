package hydraulic;

import java.util.Arrays;

/**
 * Represents the generic abstract element of an hydraulics system.
 * It is the base class for all elements.
 *
 * Any element can be connect to a downstream element
 * using the method {@link #connect(Element) connect()}.
 */
public abstract class Element {
	
	/**
	 * Constructor
	 * @param name the name of the element
	 */
	private String name;
	private Element[] sp;
	private int index;
	
	public Element(String name){
		this.name = name;
		sp = new Element[1];
		index = 1;
	}
	
	public Element(String name, int index){
		this.name = name;
		sp = new Element[index];
		this.index = index;
	}
	

	/**
	 * getter method
	 * @return the name of the element
	 */
	public String getName(){
		// TODO: to be implemented
		return name;
	}
	
	/**
	 * Connects this element to a given element.
	 * The given element will be connected downstream of this element
	 * @param elem the element that will be placed downstream
	 */
	public void connect(Element elem){
		// TODO: to be implemented
		
		sp[0] = elem;
	}
	
	public void connect(Element elem, int noutput){
		//TODO: complete
		/*if(noutput == 0 || noutput == 1) {
			sp[noutput] = elem;
		}*/
		sp[noutput] = elem;
	}
	
	/**
	 * Retrieves the element connected downstream of this
	 * @return downstream element
	 */
	public Element getOutput(){
		// TODO: to be implemented
		return sp[0];
	}
	
	public Element[] getOutputs(){
		//TODO: complete
		return sp;
	}
	
	public Element getOutputs(int index){
		//TODO: complete
	
		return sp[index];
	}
	
	public void continua(SimulationObserver observer, double inFlow){
		// TODO: to be implemented 
		double outFlow = 0;
				
		if(this instanceof Source) {
			outFlow = ((Source)this).getFlow();
			observer.notifyFlow(this.getClass().getSimpleName(), this.getName(), SimulationObserver.NO_FLOW, outFlow);
			this.getOutput().continua(observer, outFlow);
		}
		else if(this instanceof Tap) {
			if(((Tap)this).getOpen() == true) {
				outFlow = inFlow;
				observer.notifyFlow(this.getClass().getSimpleName(),this.getName(),inFlow, outFlow);
				this.getOutput().continua(observer, outFlow);
			}
			else {
				outFlow = 0;
				observer.notifyFlow(this.getClass().getSimpleName(),this.getName(),inFlow, outFlow);
				this.getOutput().continua(observer, outFlow);
			}		
		}
		else if(this instanceof Multisplit) {
			((Multisplit)this).simulate(observer, inFlow);
		}
		else if(this instanceof Split) {
			Element[] outputs = this.getOutputs();
			outFlow = inFlow/2;
			
			observer.notifyFlow(this.getClass().getSimpleName(), this.getName(), inFlow, outFlow, outFlow);
			for(Element tmp: outputs) {
				tmp.continua(observer, outFlow);
			}
		}
		else {
			observer.notifyFlow(this.getClass().getSimpleName(), this.getName(), inFlow, SimulationObserver.NO_FLOW);
		}
	}
	
	
	/*public void continua(SimulationObserver observer, Element elem, double inFlow){
		// TODO: to be implemented 
		double outFlow = 0;
				
		if(elem instanceof Source) {
			outFlow = ((Source)elem).getFlow();
			observer.notifyFlow(elem.getClass().getSimpleName(), elem.getName(), SimulationObserver.NO_FLOW, outFlow);
			elem.continua(observer, elem.getOutput(), outFlow);
		}
		else if(elem instanceof Tap) {
			if(((Tap)elem).getOpen() == true) {
				outFlow = inFlow;
				observer.notifyFlow(elem.getClass().getSimpleName(),elem.getName(),inFlow, outFlow);
				elem.continua(observer, elem.getOutput(), outFlow);
			}
			else {
				outFlow = 0;
				observer.notifyFlow(elem.getClass().getSimpleName(),elem.getName(),inFlow, outFlow);
				elem.continua(observer, elem.getOutput(), outFlow);
			}		
		}
		else if(elem instanceof Split || elem instanceof Multisplit) {
			double[] outFlowArray = new double[index];
			Element[] outputs = elem.getOutputs();
			outFlow = inFlow/index;
			for(int i = 0; i < index; i++) {
				outFlowArray[i] = outFlow;
			}
			
			observer.notifyFlow(elem.getClass().getSimpleName(), elem.getName(), inFlow, outFlowArray);
			for(Element tmp: outputs) {
				elem.continua(observer, tmp, outFlow);
			}
		}
		else {
			observer.notifyFlow(elem.getClass().getSimpleName(), elem.getName(), inFlow, SimulationObserver.NO_FLOW);
		}
	}*/
	
	
	public int manyOutputs() {
		
		return index;
	}
	
	public Element getPrimoOutput(){
		// TODO: to be implemented 
				
		if(index > 1) {
			for(int i = 0; i < index; i++) {
				if(sp[i] != null) {
					return sp[i];
				}
			}
		}
		return sp[0];
	}
	
	protected abstract StringBuffer stampa(String padding);
	
	protected static String blanks(int n) {
		char[] res = new char[n];
		Arrays.fill(res, ' ');					//riempie res di soli spazi
		
		return new String(res);					//genera stringa da res
	}
}
