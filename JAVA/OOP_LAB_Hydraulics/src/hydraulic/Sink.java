package hydraulic;

/**
 * Represents the sink, i.e. the terminal element of a system
 *
 */
public class Sink extends ElementExt {

	/**
	 * Constructor
	 * @param name
	 */
	public Sink(String name) {
		super(name);
		//TODO: complete
	}
	
	@Override
	public void connect(Element elem){
		// no effect!
	}
	
	public void simulate(SimulationObserverExt observer, double inFlow, boolean enableMaxFlowCheck){

		if (enableMaxFlowCheck == true && inFlow > getMaxFlow()) {
			observer.notifyFlowError(getClass().getSimpleName(), getName(), inFlow, getMaxFlow());
		}

		observer.notifyFlow(getClass().getSimpleName(), getName(), inFlow, SimulationObserver.NO_FLOW);
	}
	
	@Override
	protected StringBuffer stampa(String pad) {
		StringBuffer res = new StringBuffer();
		res.append("[").append(getName()).append("]").append(getClass().getSimpleName());
		
		return res;
	}
}
