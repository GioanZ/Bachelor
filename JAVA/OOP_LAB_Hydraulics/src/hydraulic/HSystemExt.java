package hydraulic;

import java.util.Arrays;

/**
 * Main class that act as a container of the elements for
 * the simulation of an hydraulics system 
 * 
 */
public class HSystemExt extends HSystem{
	
	/**
	 * Prints the layout of the system starting at each Source
	 */
	public String layout(){
		Element e = searchSource();
		StringBuffer res = new StringBuffer();
		
		res.append(e.stampa(""));
		
		return res.toString();
	}
	
	/**
	 * Deletes a previously added element with the given name from the system
	 */
	public  boolean deleteElement(String name) {
		// TODO: to be implemented
		Element[] outputs, elem;
		Element e = searchSource(), prec;
		
		if(e == null) {
			
			return false;
		}
		
		elem = searchNameDelete(e, null, name);
		if(elem == null) {
			
			return false;
		}
		
		e = elem[0];
		prec = elem[1];
		
		if(prec instanceof Split || prec instanceof Multisplit) {
			outputs = prec.getOutputs();
			for(int i = 0; i < prec.manyOutputs(); i++) {
				if(outputs[i] != null && outputs[i].getName().compareTo(name) == 0) {
					prec.connect(e.getPrimoOutput(), i);
					cancellaDaSistema(name);
					
					return true;
				}
			}
			
			return false;
		}
		
		
		prec.connect(e.getPrimoOutput());
		cancellaDaSistema(name);
		
		return true;
	}
	
	private void cancellaDaSistema(String name) {
		for(int i = 0; i < sizeElem; i++) {
			if(sistema[i] != null && sistema[i].getName().compareTo(name) == 0) {
				sistema[i] = null;
				nElem--;
				
				return;
			}
		}
	}
	
	private Element[] searchNameDelete(Element elem, Element prec, String name) {
		Element[] outputs, ritorna = new Element[2];
		int n = 0;

		if(elem == null) {
			return null;
		}
		
		if(elem.getName().compareTo(name) == 0) {
			if(elem instanceof Source) {
				System.out.println("Bro vuoi cancellare un Source, si sminchia tutto");
				
				return null;
			}
			if(elem.manyOutputs() > 1) {
				outputs = elem.getOutputs();
				for(Element tmp: outputs) {
					if(tmp != null) {
						n++;
						if(n >= 2) {
							return null;
						}
					}
				}
			}
			
			ritorna[0] = elem;
			ritorna[1] = prec;
			
			return ritorna;
		}
		
		if(elem instanceof Split || elem instanceof Multisplit) {
			outputs = elem.getOutputs();

			for(Element tmp: outputs) {
				if(tmp == null) {
					continue;
				}
				ritorna = searchNameDelete(tmp, elem, name);
				if(ritorna != null) {
					
					return ritorna;
				}
			}
		}
		
		return searchNameDelete(elem.getOutput(), elem, name);
	}
	
	@Override
	public Element[] getElements(){
		Element[] sist = new Element[nElem];
		int n = 0;
		
		for(Element e: sistema) {
			if(e != null) {
				sist[n++] = e;
			}
		}
		
		return sist;
	}

	/**
	 * starts the simulation of the system; if enableMaxFlowCheck is true,
	 * checks also the elements maximum flows against the input flow
	 */
	public void simulate(SimulationObserverExt observer, boolean enableMaxFlowCheck) {
		// TODO: to be implemented
		Source e;
		if(enableMaxFlowCheck == false) {
			super.simulate(observer);
		}
		
		e = (Source)searchSource();
		e.simulate(observer, 0, enableMaxFlowCheck);
	}
	
}
