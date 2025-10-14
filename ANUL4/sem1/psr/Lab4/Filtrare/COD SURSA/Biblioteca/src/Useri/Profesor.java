package Useri;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class Profesor  extends Utilizator{

	public static void propune(String autor,String titlu)
	{
		 int exista=0;
		 try{
		 Connection conexBD= DriverManager.getConnection("jdbc:odbc:Personal_Universitate");
			Statement stare = conexBD.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,
	                                                        ResultSet.CONCUR_UPDATABLE);
	        ResultSet rezultat=stare.executeQuery("Select * from Propuneri");
	        while(rezultat.next())
	        {
	        	if(titlu.compareTo(rezultat.getString(2))==0)
	        		exista=1;
	        }
	        if (exista==0)
	        {
	        rezultat.last();
	        rezultat.updateString(2,autor);
	        rezultat.updateString(3,titlu);
	        rezultat.insertRow();
	        rezultat.updateRow();
	        }
		 }
	        catch(SQLException f)
		     {
		       f.printStackTrace();
		     } 
	 }
	
//propune - verifica dc exista deja cartea in biblioteca
	//dc exista stop dc nu insert cartea in catalog

public static boolean eProfesor(String NumeCit)
{
	boolean gasit=false;
	try
	   {
		/*stabilire conexiune cu bazele de date Studenti si Profesori*/
       Connection conexBD= DriverManager.getConnection("jdbc:odbc:Personal_Universitate");
       Statement stare= conexBD.createStatement();
       ResultSet rezultat=stare.executeQuery("SELECT * From Profesori");
       /*parcurgere baza de date Studenti pentru a verifica daca persoana e student,
        caz in care se inregistreaza ca utilizator*/
        while(rezultat.next())
	    {
        	String nume=rezultat.getString("Nume");
            String prenume=rezultat.getString("Prenume");
            String sir=nume+prenume;
            if(NumeCit.compareTo(sir.trim())==0 && rezultat.getString("Observatii").compareTo("")==0)
    	    { 
            	gasit=true;

    	    }
        }
        conexBD.close();
	   }
	catch(SQLException f)
	   {
		   f.printStackTrace();
       }
	return gasit;
}
}