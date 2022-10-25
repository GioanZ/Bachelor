package hydraulic;

/**
 * Represents a split element, a.k.a. T element
 * 
 * During the simulation each downstream element will
 * receive a stream that is half the input stream of the split.
 */

public class Split extends ElementExt {

	/**
	 * Constructor
	 * @param name
	 */
	//private Element[] sp = new Element[2];
	
	public Split(String name) {
		super(name,2);
		//TODO: complete
	}
	
	public Split(String name, int index) {
		super(name,index);
	}
    
	/**
	 * returns the downstream elements
	 * @return array containing the two downstream element
	 */
	/*
    public Element[] getOutputs(){
    	//TODO: complete	
    }*/

    /**
     * connect one of the outputs of this split to a
     * downstream component.
     * 
     * @param elem  the element to be connected downstream
     * @param noutput the output number to be used to connect the element
     */
	/*public void connect(Element elem, int noutput){
		//TODO: complete
		if(noutput == 0 || noutput == 1) {
			sp[noutput] = elem;
		}
	}*//*
	public void connect(Element elem, int noutput){
		//TODO: complete
		
	}*/

	public void simulate(SimulationObserverExt observer, double inFlow, boolean enableMaxFlowCheck){
		ElementExt[] outputs = (ElementExt[])getOutputs();
		double outFlow  = inFlow/2;

		if (enableMaxFlowCheck == true && inFlow > getMaxFlow()) {
			observer.notifyFlowError(getClass().getSimpleName(), getName(), inFlow, getMaxFlow());
			((ElementExt)getOutput()).simulate(observer, inFlow, enableMaxFlowCheck);
		}

		observer.notifyFlow(getClass().getSimpleName(), getName(), inFlow, outFlow, outFlow);
		for(ElementExt tmp: outputs) {
			tmp.simulate(observer, outFlow, enableMaxFlowCheck);
		}
	}
	
	@Override
	protected StringBuffer stampa(String pad) {
		StringBuffer res = new StringBuffer();
		String subPad;
		
		res.append("[").append(getName()).append("]").append(getClass().getSimpleName());
		subPad = pad + blanks(res.length());
		res.append(" +-> ").append(getOutputs()[0] == null ? "*":getOutputs()[0].stampa(subPad + "|    ")).append("\n");
		
		res.append(subPad).append(" |\n");
		
		res.append(subPad + "+-> ").append(getOutputs()[1] == null ? "*":getOutputs()[1].stampa(subPad + "      "));
		
		return res;
	}
}
