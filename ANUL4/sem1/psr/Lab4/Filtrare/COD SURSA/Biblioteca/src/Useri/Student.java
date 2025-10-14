package Useri;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class Student extends Utilizator{

	//va intoarce daca utilizatorul cu id-ul id are penalizari
	public static boolean verificarePenalizare(int id) {
		String penalizare=new String();
		try
		{
			Connection conexBD= DriverManager.getConnection("jdbc:odbc:Personal_Universitate");
			Statement stare = conexBD.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,
		                                                        ResultSet.CONCUR_UPDATABLE);
		    ResultSet rezultat=stare.executeQuery("Select * from Utilizatori");
		    while(rezultat.next())
		    	{
		        	if(id==rezultat.getInt("Id_utilizator"))
		        	{
		        		penalizare=rezultat.getString("Penalizare").trim();  
			        }
		        }
		        conexBD.close();
		  }
		        catch(SQLException f)
			     {
			       f.printStackTrace();
			     } 
		        if(penalizare.compareTo("Da")==0)
		        	return true;
		        else return false;
	}		
	

	//intoarce numarul de carti imprumutate pentru utilizatorul care are id-ul id
	public static int NrCartiImprumutate(int id){
		int nr=0;
		try
		{
			Connection conexBD= DriverManager.getConnection("jdbc:odbc:Personal_Universitate");
			Statement stare = conexBD.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,
		                                                        ResultSet.CONCUR_UPDATABLE);
		    ResultSet rezultat=stare.executeQuery("Select * from Utilizatori");
		    while(rezultat.next())
		    	{
		        	if(id==rezultat.getInt("Id_utilizator"))
		        	{
		        		nr=rezultat.getInt("Nr_carti_imprumutate");  
			        }
		        }
		        conexBD.close();
		  }
		        catch(SQLException f)
			     {
			       f.printStackTrace();
			     } 
		        return nr;
	}	
	
	public static boolean eStudent(String NumeCit)
	{
		boolean gasit=false;
		try
		   {
			/*stabilire conexiune cu baza de date Studenti */
            Connection conexBD= DriverManager.getConnection("jdbc:odbc:Personal_Universitate");
            Statement stare= conexBD.createStatement();
            ResultSet rezultat=stare.executeQuery("SELECT * From Studenti"); 
            /*parcurgere baza de date Studenti pentru a verifica daca persoana e student,
            caz in care se inregistreaza ca utilizator*/
            while(rezultat.next())
            {
 	         String nume=rezultat.getString("Nume");
	         String prenume=rezultat.getString("Prenume");
	         String sir=nume+prenume;
	         if(NumeCit.compareTo(sir.trim())==0 && rezultat.getString("Observatii").compareTo("")==0){
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
