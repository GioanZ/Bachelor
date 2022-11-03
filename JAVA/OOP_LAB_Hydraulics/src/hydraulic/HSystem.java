package hydraulic;

import java.util.Arrays;

/**
 * Main class that act as a container of the elements for
 * the simulation of an hydraulics system 
 * 
 */
public class HSystem {
	
	/**
	 * Adds a new element to the system
	 * @param elem
	 */
	protected int nElem = 0;
	protected int sizeElem = 1;
	protected Element[] sistema = new Element[sizeElem];
	
	public void addElement(Element elem){
		// TODO: to be implemented
		if (nElem >= sizeElem) {
			sizeElem=2*sizeElem; 
			sistema = Arrays.copyOf(sistema, sizeElem);
		} 
		sistema[nElem++] = elem;
	}
	
	/**
	 * returns the element added so far to the system.
	 * If no element is present in the system an empty array (length==0) is returned.
	 * 
	 * @return an array of the elements added to the hydraulic system
	 */
	public Element[] getElements(){
		// TODO: to be implemented
		Element[] sist = Arrays.copyOf(sistema, nElem);
		
		return sist;
	}
	
	/**
	 * starts the simulation of the system
	 */
	public void simulate(SimulationObserver observer){
		// TODO: to be implemented 
		Element source = searchSource();
		if(source != null) {
			source.continua(observer, ((Source)source).getFlow());
		}
	}
	
	public Element searchSource() {
		for(int i=0;i<nElem;i++) {
			if(sistema[i] instanceof Source) {
				
				return sistema[i];
			}
		}
		
		return null;
	}
	
}
