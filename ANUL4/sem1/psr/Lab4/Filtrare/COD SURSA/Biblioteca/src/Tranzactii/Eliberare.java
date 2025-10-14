package Tranzactii;

import Inventar.*;
import Useri.*;

public class Eliberare {
	
	public static void  eliberareImprumut(int cota,int id_u)
	{
		if(Imprumut.cautaTipMaterial(cota).compareTo("carte")==0)
			Carte.anulareImprumut(cota);
		else Revista.anulareImprumut(cota);
		Utilizator.anulareImprumut(id_u);
	}
}
