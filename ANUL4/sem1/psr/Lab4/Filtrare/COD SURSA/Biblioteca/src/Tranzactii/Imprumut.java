package Tranzactii;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import Useri.Student;
import Useri.Utilizator;
import InterfataGrafica.*;
import Inventar.*;

public class Imprumut {
	
	
	/*se verifica daca utilizatorul este student sau profesor
	 * daca e student trebuie sa nu aiba penalitati si sa nu aiba mai mult de 3 carti imprumutate
	 * daca se poate efectua imprumutul se verifica carui tip de material apartine cota
	 * apoi sa actualizeaza bazele de date corespunzatoare*/
	public static boolean creareImprumut(int cota,String data)
	{
		if(Utilizator.getStatut(MeniuBibliotecar.id)=="student")
		{
			if(Student.verificarePenalizare(MeniuBibliotecar.id)==true || Student.NrCartiImprumutate(MeniuBibliotecar.id)>=3)
				return false;
				else
				{
					 if(cautaTipMaterial(cota).compareTo("carte")==0)
						 Carte.creareImprumut(cota);
					 else Revista.creareImprumut(cota);
					 Utilizator.creareImprumut(MeniuBibliotecar.id,data);	
					 return true;
				}
		} 
		else {
			if(cautaTipMaterial(cota).compareTo("carte")==0)
				 Carte.creareImprumut(cota);
			 else Revista.creareImprumut(cota);
			 Carte.creareImprumut(cota);
			 Utilizator.creareImprumut(MeniuBibliotecar.id,data);
			 return true;
		}
	}
	
	
	//intoarce tipul de material(carte sau revista) pentru cota data ca parametru
	public static String cautaTipMaterial(int cota)
	{
		String material="revista";
		try
		{
			/*stabilire conexiune cu baza de date Carte*/
		    Connection conexBD= DriverManager.getConnection("jdbc:odbc:Personal_Universitate");
		    Statement stare = conexBD.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,
                                                        ResultSet.CONCUR_UPDATABLE);
            ResultSet rezultat=stare.executeQuery("Select * from Carte");
            while(rezultat.next())
            {
            	if(cota==rezultat.getInt("Cota"))
            		material="carte";
            }
	        conexBD.close();//inchidere conexiune
	    }
	    catch(SQLException f)
	     {
	       f.printStackTrace();
	     } 	
	    return material;
	}

}


	

	
	
	
