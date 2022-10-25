package hydraulic;

import java.util.Arrays;

/**
 * Represents a multisplit element, an extension of the Split that allows many outputs
 * 
 * During the simulation each downstream element will
 * receive a stream that is determined by the proportions.
 */

public class Multisplit extends Split {

	private int numOutput;
	private double[] proprozioni;
	
	/**
	 * Constructor
	 * @param name
	 * @param numOutput
	 */
	public Multisplit(String name, int numOutput) {
		super(name,numOutput); //you can edit also this line
		// TODO: to be implemented
		this.numOutput = numOutput;
	}
    
	/**
	 * returns the downstream elements
	 * @return array containing the two downstream element
	 */
    /*public Element[] getOutputs(){
    	//TODO: complete
    	
		return connessi;
    }*/

    /**
     * connect one of the outputs of this split to a
     * downstream component.
     * 
     * @param elem  the element to be connected downstream
     * @param noutput the output number to be used to connect the element
     */
	public void connect(Element elem, int noutput){
		//TODO: complete
		if(noutput >=  numOutput) {
			//System.out.println("Error connect");
			
			return;
		}
		
		super.connect(elem, noutput);
	}
	
	/**
	 * Define the proportion of the output flows w.r.t. the input flow.
	 * 
	 * The sum of the proportions should be 1.0 and 
	 * the number of proportions should be equals to the number of outputs.
	 * Otherwise a check would detect an error.
	 * 
	 * @param proportions the proportions of flow for each output
	 */
	public void setProportions(double... proportions) {
		// TODO: to be implemented
		double tmp = 0;
		for(double tmp1: proportions) {
			tmp += tmp1;
		}
		if((tmp < 0.99 && tmp > 1.01)|| proportions.length != numOutput) {
			//System.out.println("Error setProportions");
			
			return;
		}
		
		proprozioni = proportions;
	}
	
	public void simulate(SimulationObserver observer, double inFlow){
		// TODO: to be implemented 
		
		Element[] outputs = getOutputs();
		double[] outFlow  = new double[proprozioni.length];

		for(int i = 0; i < proprozioni.length; i++) {
			outFlow[i] = inFlow * proprozioni[i];
		}
/*		
 * NON PUOI
 * 		int i = 0;
		for(double tmp: outFlow) {
			tmp = inFlow * proprozioni[i];
			i++;
		}
		
		Così si:
		int i = 0;
		for(double tmp: proprozioni) {
			outFlow[i] = inFlow * tmp;
			i++;
		}
*/
		observer.notifyFlow(getClass().getSimpleName(), getName(), inFlow, outFlow);
		int i = 0;
		for(Element tmp: outputs) {
			tmp.continua(observer, outFlow[i]);
			i++;
		}
	}
	
	public void simulate(SimulationObserverExt observer, double inFlow, boolean enableMaxFlowCheck){
		// TODO: to be implemented 
		ElementExt[] outputs = (ElementExt[])getOutputs();
		double[] outFlow  = new double[proprozioni.length];

		if (enableMaxFlowCheck == true && inFlow > getMaxFlow()) {
			observer.notifyFlowError(getClass().getSimpleName(), getName(), inFlow, getMaxFlow());
		}
		
		for(int i = 0; i < proprozioni.length; i++) {
			outFlow[i] = inFlow * proprozioni[i];
		}

		observer.notifyFlow(getClass().getSimpleName(), getName(), inFlow, outFlow);
		int i = 0;
		for(ElementExt tmp: outputs) {
			tmp.simulate(observer, outFlow[i], enableMaxFlowCheck);
			i++;
		}
	}
	
	@Override
	protected StringBuffer stampa(String pad) {
		StringBuffer res = new StringBuffer();
		String subPad;
		
		res.append("[").append(getName()).append("]").append(getClass().getSimpleName());
		subPad = pad + blanks(res.length());
		
		for(int i=0; i < manyOutputs(); i++) {
			if(i>0) {
				res.append("\n");
				res.append(subPad).append(" |\n");
				res.append(subPad);
			}
			res.append(" +-> ");
			if(getOutputs()[i] != null) {
				if(i < manyOutputs()-1) {
					res.append(getOutputs()[i].stampa(subPad + " |    "));
				}
				else {
					res.append(getOutputs()[i].stampa(subPad + "      "));
				}
			}
			else {
				res.append("*"); 
			}
		}

		return res;
	}
}
