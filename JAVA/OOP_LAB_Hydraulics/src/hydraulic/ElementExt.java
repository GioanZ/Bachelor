package hydraulic;

public abstract class ElementExt extends Element{

	private double maxFlow;
	
	public ElementExt(String name) {
		super(name);
	}
	
	public ElementExt(String name, int index) {
		super(name, index);
	}

	public void setMaxFlow(double maxFlow) {
		// TODO: to be implemented
		if(this instanceof Source) {
			return;
		}
		
		this.maxFlow = maxFlow;
	}
	
	public double getMaxFlow() {
		
		return maxFlow;
	}
	
	abstract void simulate(SimulationObserverExt observer, double inFlow, boolean enableMaxFlowCheck);
}
