package mountainhuts;

import static java.util.stream.Collectors.toList;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.TreeMap;
import java.util.stream.Collector;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/**
 * Class {@code Region} represents the main facade
 * class for the mountains hut system.
 * 
 * It allows defining and retrieving information about
 * municipalities and mountain huts.
 *
 */
public class Region {

	private String name;
	
	private ArrayList<Value>value = new ArrayList<Value>();
	
	private Map<String,Municipality>municipi = new HashMap<>();
	private Map<String,MountainHut>mountainHut = new HashMap<>();
	
	
	/**
	 * Create a region with the given name.
	 * 
	 * @param name
	 *            the name of the region
	 */
	public Region(String name) {
		this.name = name;
	}

	/**
	 * Return the name of the region.
	 * 
	 * @return the name of the region
	 */
	public String getName() {
		return name;
	}

	/**
	 * Create the ranges given their textual representation in the format
	 * "[minValue]-[maxValue]".
	 * 
	 * @param ranges
	 *            an array of textual ranges
	 */
	public void setAltitudeRanges(String... ranges) {
		for(String range: ranges) {
			value.add(new Value(range));
		}
	}

	/**
	 * Return the textual representation in the format "[minValue]-[maxValue]" of
	 * the range including the given altitude or return the default range "0-INF".
	 * 
	 * @param altitude
	 *            the geographical altitude
	 * @return a string representing the range
	 */
	public String getAltitudeRange(Integer altitude) {
		String alt;
		
		for(Value v: value) {
			if((alt=v.cercaIntervallo(altitude)) != null){
				return  alt;
			}
		}
		
		return "0-INF";
	}

	/**
	 * Create a new municipality if it is not already available or find it.
	 * Duplicates must be detected by comparing the municipality names.
	 * 
	 * @param name
	 *            the municipality name
	 * @param province
	 *            the municipality province
	 * @param altitude
	 *            the municipality altitude
	 * @return the municipality
	 */
	public Municipality createOrGetMunicipality(String name, String province, Integer altitude) {
		Municipality mun = municipi.get(name);
		
		if(mun == null) {
			mun = new Municipality(name, province, altitude);
			municipi.put(name, mun);
		}
		
		return mun;
	}

	/**
	 * Return all the municipalities available.
	 * 
	 * @return a collection of municipalities
	 */
	public Collection<Municipality> getMunicipalities() {
		
		return municipi.values();
	}

	/**
	 * Create a new mountain hut if it is not already available or find it.
	 * Duplicates must be detected by comparing the mountain hut names.
	 *
	 * @param name
	 *            the mountain hut name
	 * @param category
	 *            the mountain hut category
	 * @param bedsNumber
	 *            the number of beds in the mountain hut
	 * @param municipality
	 *            the municipality in which the mountain hut is located
	 * @return the mountain hut
	 */
	public MountainHut createOrGetMountainHut(String name, String category, Integer bedsNumber,Municipality municipality) {
		MountainHut mon = mountainHut.get(name);
		
		if(mon == null) {
			mon = new MountainHut(name, null, category, bedsNumber, municipality);
			mountainHut.put(name, mon);
		}
		
		return mon;
	}

	/**
	 * Create a new mountain hut if it is not already available or find it.
	 * Duplicates must be detected by comparing the mountain hut names.
	 * 
	 * @param name
	 *            the mountain hut name
	 * @param altitude
	 *            the mountain hut altitude
	 * @param category
	 *            the mountain hut category
	 * @param bedsNumber
	 *            the number of beds in the mountain hut
	 * @param municipality
	 *            the municipality in which the mountain hut is located
	 * @return a mountain hut
	 */
	public MountainHut createOrGetMountainHut(String name, Integer altitude, String category, Integer bedsNumber, Municipality municipality) {
		MountainHut mon = mountainHut.get(name);
		
		if(mon == null) {
			mon = new MountainHut(name, altitude, category, bedsNumber, municipality);
			mountainHut.put(name, mon);
		}
		
		return mon;
	}

	/**
	 * Return all the mountain huts available.
	 * 
	 * @return a collection of mountain huts
	 */
	public Collection<MountainHut> getMountainHuts() {
		
		return mountainHut.values();
	}

	/**
	 * Factory methods that creates a new region by loadomg its data from a file.
	 * 
	 * The file must be a CSV file and it must contain the following fields:
	 * <ul>
	 * <li>{@code "Province"},
	 * <li>{@code "Municipality"},
	 * <li>{@code "MunicipalityAltitude"},
	 * <li>{@code "Name"},
	 * <li>{@code "Altitude"},
	 * <li>{@code "Category"},
	 * <li>{@code "BedsNumber"}
	 * </ul>
	 * 
	 * The fields are separated by a semicolon (';'). The field {@code "Altitude"}
	 * may be empty.
	 * 
	 * @param name
	 *            the name of the region
	 * @param file
	 *            the path of the file
	 */
	public static Region fromFile(String name, String file) {
		Region r = new Region(name);
		List<String> l = Region.readData(file);												//metto Region davanti perché è static e chiama se stesso
//		Municipality mun;
//		String[] parole;
//		
//		for(int i = 1; i < l.size(); i++) {
//			parole = l.get(i).split(";");
//			mun = r.createOrGetMunicipality(parole[1], parole[0],Integer.parseInt(parole[2]));
//			
//			//System.out.println(parole[1] + " " +  parole[0] +" " +  Integer.parseInt(parole[2]) + " " + parole[3] +" " +  parole[5] +" " +  Integer.parseInt(parole[6]));
//			
//			if(parole[4].isEmpty() == true) {
//				r.createOrGetMountainHut(parole[3], parole[5], Integer.parseInt(parole[6]), mun);
//			}
//			else {
//				r.createOrGetMountainHut(parole[3], Integer.parseInt(parole[4]), parole[5], Integer.parseInt(parole[6]), mun);
//			}
//		}
		
		String[] head = l.remove(0).split(";"); 											//remove(0) restituisce la prima riga
		Map<String,Integer> h2 = new HashMap<>();
		for(int i=0; i<head.length;i++) {
			h2.put(head[i], i);
		}
		l.forEach(row->{
			String[] cells = row.split(";");
			
			String municipalityName = cells[h2.get("Municipality")];
			String municipalityProvince = cells[h2.get("Province")];
			Integer municipalityAltitude = Integer.parseInt(cells[h2.get("MunicipalityAltitude")]);
			
			Municipality municipality = r.createOrGetMunicipality(municipalityName,municipalityProvince,municipalityAltitude);
			
			String hutName = cells[h2.get("Name")];
			String altitude = cells[h2.get("Altitude")];
			String category = cells[h2.get("Category")];
			Integer bedsNumber = Integer.parseInt(cells[h2.get("BedsNumber")]);
			
			if(altitude.equals("")) {
				r.createOrGetMountainHut(hutName, category, bedsNumber, municipality);
			}
			else {
				r.createOrGetMountainHut(hutName, Integer.parseInt(altitude),category, bedsNumber, municipality);
			}
			
		});
		
		
		return r;
	}

	/**
	 * Internal class that can be used to read the lines of
	 * a text file into a list of strings.
	 * 
	 * When reading a CSV file remember that the first line
	 * contains the headers, while the real data is contained
	 * in the following lines.
	 * 
	 * @param file the file name
	 * @return a list containing the lines of the file
	 */
	@SuppressWarnings("unused")
	private static List<String> readData(String file) {
		try (BufferedReader in = new BufferedReader(new FileReader(file))) {				//il .close() del file lo fa in automatico la try 
			return in.lines().collect(toList());											//.lines() restituisce uno stream in cui ogni riga è un pezzo
		} catch (IOException e) {
			System.err.println(e.getMessage());
			return null;
		}
	}

	/**
	 * Count the number of municipalities with at least a mountain hut per each
	 * province.
	 * 
	 * @return a map with the province as key and the number of municipalities as
	 *         value
	 */
	public Map<String, Long> countMunicipalitiesPerProvince() {
		return municipi.values().stream()
				.collect(
						Collectors.groupingBy(
								Municipality::getProvince,//classifaier						//voglio raggruppare per province
								Collectors.counting()//downqualcosa
								)
						);
	}

	/**
	 * Count the number of mountain huts per each municipality within each province.
	 * 
	 * @return a map with the province as key and, as value, a map with the
	 *         municipality as key and the number of mountain huts as value
	 */
	public Map<String, Map<String, Long>> countMountainHutsPerMunicipalityPerProvince() {
		return mountainHut.values().stream()
				.collect(Collectors.groupingBy(
									(x) -> x.getMunicipality().getProvince(),//classifier esterno
									Collectors.groupingBy(//downstream collector esterno
											(x) -> x.getMunicipality().getName(),//classifier interno
											Collectors.counting()//downstream collector interno
											)
									
									)
						);
	}

	/**
	 * Count the number of mountain huts per altitude range. If the altitude of the
	 * mountain hut is not available, use the altitude of its municipality.
	 * 
	 * @return a map with the altitude range as key and the number of mountain huts
	 *         as value
	 */
	
	public Map<String, Long> countMountainHutsPerAltitudeRange() {
		Map<String,Long> res = mountainHut.values().stream()
				.collect(
						Collectors.groupingBy(
								x -> getAltitudeRange(x), //classifier
								Collectors.counting()//downstream collector
								)	
						);
		//e i range senza rifugi?
		value.stream()
			.map(Value::toString)
			.forEach(range -> res.putIfAbsent(range, 0L));									//per convertirlo in long
		
		return res;
	}
	
	private String getAltitudeRange(MountainHut x) {
		if(x.getAltitude().isPresent())
			return getAltitudeRange(x.getAltitude().get());
		else
			return getAltitudeRange(x.getMunicipality().getAltitude());
	}

	/**
	 * Compute the total number of beds available in the mountain huts per each
	 * province.
	 * 
	 * @return a map with the province as key and the total number of beds as value
	 */
	public Map<String, Integer> totalBedsNumberPerProvince() {
		return mountainHut.values().stream()
								.collect(Collectors.groupingBy(
											x -> x.getMunicipality().getProvince(),
											Collectors.summingInt(MountainHut::getBedsNumber)	//prende gli stream li metti in interi e li somma
									));
	}

	/**
	 * Compute the maximum number of beds available in a single mountain hut per
	 * altitude range. If the altitude of the mountain hut is not available, use the
	 * altitude of its municipality.
	 * 
	 * @return a map with the altitude range as key and the maximum number of beds
	 *         as value
	 */
	public Map<String, Optional<Integer>> maximumBedsNumberPerAltitudeRange() {
		Map<String,Optional<Integer>> res = mountainHut.values().stream()
							.collect(
									Collectors.groupingBy(
											x -> getAltitudeRange(x), //classifier
											Collectors.mapping(//downstream
													MountainHut::getBedsNumber,//mapper 
													Collectors.maxBy(
															Comparator.naturalOrder()
															))
											)	
									);
		
		value.stream()
				.map(Value::toString)
				.forEach(range -> res.putIfAbsent(range, Optional.of(0)));
		
		return res;
	}

	/**
	 * Compute the municipality names per number of mountain huts in a municipality.
	 * The lists of municipality names must be in alphabetical order.
	 * 
	 * @return a map with the number of mountain huts in a municipality as key and a
	 *         list of municipality names as value
	 */
	public Map<Long, List<String>> municipalityNamesPerCountOfMountainHuts() {
		return mountainHut.values().stream()
				.map(x->x.getMunicipality().getName())
				.collect(Collectors.groupingBy(
						x->x, //classifier cioè come devi ordinarli
						TreeMap::new ,//map factory
						Collectors.counting()//downstream collector
						))
				.entrySet().stream()
					.collect(Collectors.groupingBy(
							Map.Entry::getValue,
							Collectors.mapping(
									Map.Entry::getKey, 
									Collectors.toList())
							)
							)
				;
	}

}
