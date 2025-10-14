package Inventar;

import java.sql.*;

import InterfataGrafica.MeniuBibliotecar;
import Tranzactii.Data;

public class Carte {
	/**
	 *  Cota cartii identificator unic
	 */
	int cota;
	/**
	 *  Isbn-ul cartii
	 */
	int isbn;
	/**
	 *  Tilul cartii
	 */
	String titlu;
	/**
	 *  Autorul cartii
	 */
	String autor;
	/**
	 *  Editura cartii
	 */
	String editura;
	/**
	 *  Disponibilitatea revistei:da/imprumutat/inReparatie/pierdut
	 */
	String disponibilitate;
	/**
	 *  Starea revistei:buna/proasta/distrus
	 */
	String calitate;
	
	/**
	 * Constructorul clasei Carte
	 * @param cota
	 * @param isbn
	 * @param titlu
	 * @param autor
	 * @param editura
	 */
	public Carte(int cota,int isbn,String titlu,String autor,String editura)
	{
		this.cota=cota;
		this.isbn=isbn;
		this.titlu=titlu;
		this.autor=autor;
		this.editura=editura;
		this.disponibilitate="Da";
		this.calitate="Buna";		
	}
	
	/*insereaza in baza de date Carte o noua carte ale carei atribute au fost citit de la tastatura*/
	public void updateBdCarte()
	{
		try
		{
			/*stabilire conexiune cu baza de date Carte*/
		    Connection conexBD= DriverManager.getConnection("jdbc:odbc:Personal_Universitate");
		    Statement stare = conexBD.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,
                                                        ResultSet.CONCUR_UPDATABLE);
            ResultSet rezultat=stare.executeQuery("Select * from Carte");
            /*introducerea datelor in baza de date*/
            rezultat.last();
            rezultat.updateInt(1,cota);
            rezultat.updateInt(2,isbn);
            rezultat.updateString(3,titlu);
            rezultat.updateString(4,autor);
            rezultat.updateString(5,editura);
            rezultat.updateString(6,disponibilitate);
            rezultat.updateString(7,calitate);
            rezultat.insertRow();
            rezultat.updateRow();
	        conexBD.close();//inchidere conexiune
	    }
	    catch(SQLException f)
	     {
	       f.printStackTrace();
	     } 	
	}

	/*Pentru cartea ce are cota egala cu cea primita ca parametru se va modifica
	 * disponibilitatea in "Imprumutat"*/
	public static void creareImprumut(int cota)
	{
		try
		{
			/*stabilire conexiune cu baza de date Carte*/
		    Connection conexBD= DriverManager.getConnection("jdbc:odbc:Personal_Universitate");
		    Statement stare = conexBD.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,
                                                        ResultSet.CONCUR_UPDATABLE);
            ResultSet rezultat=stare.executeQuery("Select * from Carte");
            /*parcurgerea bazei de date*/
            while(rezultat.next())
            {
            	if((rezultat.getInt("Cota"))==cota)
            	{
            		rezultat.updateString("Disponibilitate","Imprumutat");
            	    rezultat.updateString("Data_imprumut",MeniuBibliotecar.DataCurenta);
        		    Data dt=new Data(MeniuBibliotecar.DataCurenta);
        		    rezultat.updateString("Data_scadenta",Data.addToZi(dt,15).toString());
        		    rezultat.updateRow();
        		    
            	}
            }
            conexBD.close();//inchidere conexiune
	    }
	    catch(SQLException f)
	     {
	       f.printStackTrace();
	     } 	
	}
	
	/*Pentru cartea ce are cota egala cu cea primita ca parametru se va modifica
	 * disponibilitatea in "Da"*/
	public static void anulareImprumut(int cota) 
	{
		try
		{
			Connection conexBD= DriverManager.getConnection("jdbc:odbc:Personal_Universitate");
			Statement stare = conexBD.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,
		                                                        ResultSet.CONCUR_UPDATABLE);
		    ResultSet rezultat=stare.executeQuery("Select * from Carte");
		    while(rezultat.next())
		        {
		        	if(cota==rezultat.getInt("Cota"))
		        	{
		        		rezultat.updateString("Disponibilitate","Da"); 
		        		rezultat.updateString("Data_imprumut","");
	        		    rezultat.updateString("Data_scadenta","");
	        		    rezultat.updateRow();
			        }
		        }
		        conexBD.close();
		  }
		        catch(SQLException f)
			     {
			       f.printStackTrace();
			     }		
	}
		
	/*se cauta in baza de date Carte ce carte are este intr-o stare proasta
      si se modifica coloana disponibilitate in "inReconditionare" 
      apoi cartile distruse se marcheaza ca "retras"*/	
	public static void cautareStare()
	{
		try
		{
			Connection conexBD= DriverManager.getConnection("jdbc:odbc:Personal_Universitate");
			Statement stare = conexBD.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,
		                                                        ResultSet.CONCUR_UPDATABLE);
		    ResultSet rezultat=stare.executeQuery("Select * from Carte");
		    while(rezultat.next())
		        {
		        	if(rezultat.getString("Calitate").compareToIgnoreCase("proasta")==0)
		        	{
		        		rezultat.updateString("Disponibilitate","inReconditionare");
		        		rezultat.updateRow();
			        }
		        	if(rezultat.getString("Calitate").compareToIgnoreCase("distrus")==0)
		        	{
		        		rezultat.updateString("Disponibilitate","retras"); 
		        		rezultat.updateRow();
			        }
		        	String data=rezultat.getString("Data_scadenta");
		        	if(data!=null)
		        	{
		        		Data dt=new Data(data);
		        		Data dt_c=new Data(MeniuBibliotecar.DataCurenta);
		        		if(dt.ComparaData(dt_c)==-1)
		        		{
		        			rezultat.updateString("Disponibilitate", "pierdut");
		        			rezultat.updateString("Data_scadenta", null);
		        			rezultat.updateString("Data_imprumut", null);
		        			rezultat.updateRow();
		        		}
		        	}
		        	
		        }
		        conexBD.close();
		  }
		        catch(SQLException f)
			     {
			       f.printStackTrace();
			     }		
	}	
}
