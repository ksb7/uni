package Inventar;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import InterfataGrafica.MeniuBibliotecar;
import Tranzactii.Data;

public class Revista {
	//variabilele sunt cele din baza de date
	
	/**
	 *  Cota revistei identificator unic
	 */
	private int cota;
	/**
	 *  Periodicitatea aparitiei revistei
	 */
	private int periodicitate;
	/**
	 *  Numarul revistei
	 */
	private int numar;
	/**
	 *  Tilul revistei
	 */
	private String titlu;
	/**
	 *  Starea revistei:buna/proasta/distrus
	 */
	private String calitate;
	/**
	 *  Disponibilitatea revistei:da/imprumutat/inReparatie/pierdut
	 */
	private String disponibilitate;
	
	/**
	 * Constructorul clasei Revista
	 * @param cota
	 * @param titlu
	 * @param period
	 */
	public Revista(int cota, String titlu, int period, int nr)
	{
		this.cota=cota;
		this.titlu=titlu;
		this.periodicitate=period;
		this.calitate="buna";
		this.disponibilitate="da";
		this.numar=nr;
	}

	/*insereaza in baza de date Reviste o noua revista ale carei atribute au fost citite de la tastatura*/
	public void updateBdRevista()
	{
		try
		{
			/*stabilire conexiune cu baza de date Reviste*/
		    Connection conexBD= DriverManager.getConnection("jdbc:odbc:Personal_Universitate");
		    Statement stare = conexBD.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,
                                                        ResultSet.CONCUR_UPDATABLE);
            ResultSet rezultat=stare.executeQuery("Select * from Reviste");
            /*introducerea datelor in baza de date*/
            rezultat.last();
            rezultat.updateInt(1,cota);
            rezultat.updateString(2,titlu);
            rezultat.updateInt(3,numar);
            rezultat.updateInt(4,periodicitate);
            rezultat.updateString(5,disponibilitate);
            rezultat.updateString(6,calitate);
            rezultat.insertRow();
            rezultat.updateRow();
	        conexBD.close();//inchidere conexiune
	    }
	    catch(SQLException f)
	     {
	       f.printStackTrace();
	     } 	
		
	}
	
	/*Pentru revista ce are cota egala cu cea primita ca parametru se va modifica disponibilitatea in "Da"*/
	public static void anulareImprumut(int cota) {
		try
		{
			Connection conexBD= DriverManager.getConnection("jdbc:odbc:Personal_Universitate");
			Statement stare = conexBD.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,
		                                                        ResultSet.CONCUR_UPDATABLE);
		    ResultSet rezultat=stare.executeQuery("Select * from Reviste");
		    /*parcurgerea bazei de date*/
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
	
	/*Pentru revista ce are cota egala cu cea primita ca parametru se va modifica
	 * disponibilitatea in "Imprumutat"*/
    public static void creareImprumut(int cota)
    {
    	try
		{
			/*stabilire conexiune cu baza de date Carte*/
		    Connection conexBD= DriverManager.getConnection("jdbc:odbc:Personal_Universitate");
		    Statement stare = conexBD.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,
                                                        ResultSet.CONCUR_UPDATABLE);
            ResultSet rezultat=stare.executeQuery("Select * from Reviste");
            /*parcurgerea bazei de date*/
            while(rezultat.next())
            {
            	if(rezultat.getInt("Cota")==cota)
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
    
    /*se cauta in baza de date Reviste cele care sunt intr-o stare proasta
    si se modifica coloana disponibilitate in "inReconditionare" 
    apoi revistele distruse se marcheaza ca "retras"*/	
	public static void cautareStare()
	{
		try
		{
			Connection conexBD= DriverManager.getConnection("jdbc:odbc:Personal_Universitate");
			Statement stare = conexBD.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,
		                                                        ResultSet.CONCUR_UPDATABLE);
		    ResultSet rezultat=stare.executeQuery("Select * from Reviste");
		    while(rezultat.next())
		        {
		        	if(rezultat.getString("Calitate").compareTo("proasta")==0)
		        	{
		        		rezultat.updateString("Disponibilitate","inReconditionare");
		        		rezultat.updateRow();
			        }
		        	if(rezultat.getString("Calitate").compareTo("distrus")==0)
		        	{
		        		rezultat.updateString("Disponibilitate","retras"); 
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
