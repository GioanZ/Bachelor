package polito.OOP.ITA3.StackTestP;

import org.junit.runner.RunWith;
import org.junit.runners.Suite;

//Mi dice che questa classe è una suite di test
//quindi un insieme di classi di test
@RunWith(Suite.class)

//Elenco tutte le classi di test che fanno parte
//di questa suite.
@Suite.SuiteClasses(
		{
			StackTest.class,
			StackTest1.class
		}
		)




public class TestSuite {

}
