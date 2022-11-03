package hydraulic;

/**
 * Represents a tap that can interrupt the flow.
 * 
 * The status of the tap is defined by the method
 * {@link #setOpen(boolean) setOpen()}.
 */

public class Tap extends ElementExt {
	private boolean aperto = false;

	public Tap(String name) {
		super(name);
		//TODO: complete
	}
	
	/**
	 * Defines whether the tap is open or closed.
	 * 
	 * @param open  opening level
	 */
	public void setOpen(boolean open){
		//TODO: complete
		aperto = open;
	}
	
	public boolean getOpen(){
		return aperto;
	}
	
	public void simulate(SimulationObserverExt observer, double inFlow, boolean enableMaxFlowCheck){

		if (enableMaxFlowCheck == true && inFlow > getMaxFlow()) {
			observer.notifyFlowError(getClass().getSimpleName(), getName(), inFlow, getMaxFlow());
			if(getOpen() == true) {
				((ElementExt)getOutput()).simulate(observer, inFlow, enableMaxFlowCheck);
			}
			else {
				((ElementExt)getOutput()).simulate(observer, 0, enableMaxFlowCheck);
			}
		}
		
		if(getOpen() == true) {
			observer.notifyFlow(getClass().getSimpleName(),getName(),inFlow, inFlow);
			getOutput().continua(observer, inFlow);
		}
		else {
			observer.notifyFlow(getClass().getSimpleName(),getName(),inFlow, 0);
			getOutput().continua(observer, 0);
		}
	}
	
	@Override
	protected StringBuffer stampa(String pad) {
		StringBuffer res = new StringBuffer();
		res.append("[").append(getName()).append("]").append(getClass().getSimpleName()).append(" -> ");
		res.append(getOutput() == null ? "*":getOutput().stampa(pad + blanks(res.length())));
		
		return res;
	}
}
