package hydraulic;

/**
 * Represents a source of water, i.e. the initial element for the simulation.
 *
 * The status of the source is defined through the method
 * {@link #setFlow(double) setFlow()}.
 */
public class Source extends ElementExt {
	
	private double portata;
	
	public Source(String name) {
		//TODO: complete
		super(name);
	}

	/**
	 * defines the flow produced by the source
	 * 
	 * @param flow
	 */
	public void setFlow(double flow){
		//TODO: complete
		portata = flow;
	}
	
	public double getFlow(){
		return portata;
	}
	
	public void simulate(SimulationObserverExt observer, double inFlow, boolean enableMaxFlowCheck){
		
		observer.notifyFlow(getClass().getSimpleName(), getName(), SimulationObserver.NO_FLOW, getFlow());
		
		if (enableMaxFlowCheck == true) {
			((ElementExt)getOutput()).simulate(observer, getFlow(), enableMaxFlowCheck);
		}
		else {
			getOutput().continua(observer, getFlow());
		}
	}
	
	@Override
	protected StringBuffer stampa(String pad) {
		StringBuffer res = new StringBuffer();
		res.append("[").append(getName()).append("]").append(getClass().getSimpleName()).append(" -> ");
		res.append(getOutput() == null ? "*":getOutput().stampa(blanks(res.length())));
		
		return res;
	}
}
