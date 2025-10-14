package Useri;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import InterfataGrafica.MeniuBibliotecar;
import InterfataGrafica.MeniuUtilizator;
import Tranzactii.Data;

public class Utilizator {
	
	int id_utilizator;
	String facultate;
	String nume;
	String prenume;
	String user;
	String parola;
	String statut;
	String data_inscriere;
	String data_anulare;
	String data_imprumut;
	String data_scadenta;
	int nr_carti_imprumutate;
	String adresa_mail;
	String penalizare;
	String data_reinscriere;
	String observatii;
	

	/**
	 * Constructor implicit
	 */
	public Utilizator()
	{
		
	}
	
	
	/**
	 * Constructorul clasei Utilizator
	 * @param id_u
	 * @param facult
	 * @param num
	 * @param pren
	 * @param us
	 * @param par
	 * @param st
	 * @param dtInscr
	 * @param adrMail
	 * @param dtAnulare
	 */
	public Utilizator(int id_u,String facult,String num,String pren,String us,String par,String st,String dtInscr,String adrMail,String dtAnulare) 
	  {
		id_utilizator=id_u;
		facultate=facult;
		nume=num;
		prenume=pren;
		user=us;
		parola=par;
		statut=st;
		data_inscriere=dtInscr;
		nr_carti_imprumutate=0;
		adresa_mail=adrMail;
		data_anulare=dtAnulare;
	  }
	
	
	/**
	 * Se verifica daca s-a introdus corect numele de user si parola si daca mai e utilizator
	 * @param user numele de user
	 * @param parola 
	 * @return daca a reusit autentificarea sau nu
	 */
	public static boolean Autentificare(String user,String parola)
	{
		boolean flag=false;
		try
		{
		Connection conexBD= DriverManager.getConnection("jdbc:odbc:Personal_Universitate");
		Statement s= conexBD.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,
                                                             ResultSet.CONCUR_UPDATABLE);
        ResultSet rezultat=s.executeQuery("select * from Utilizatori");
        rezultat.first();
        while(rezultat.next() && flag==false)
        {
            String util=rezultat.getString("User");
            String parol=rezultat.getString("Parola");
            MeniuUtilizator.id_u=rezultat.getInt("id_utilizator");
            if((util.compareTo(user)==0 && parol.compareTo(parola)==0))
            	flag=true;
           // if(rezultat.getString("Observatii").compareToIgnoreCase("anulat")==0)
            	//flag=false;
        }
       }
		  catch(SQLException f)
		    {
	                f.printStackTrace();
		    }  
		return flag;		
	}
	
	
	/*intoarce statutul (student/profesor) utilizatorului cu id-ul primit ca parametru*/
    public static String getStatut(int id)
    {
    String status=new String();
	try {
		    Connection conexBD= DriverManager.getConnection("jdbc:odbc:Personal_Universitate");
			Statement s = conexBD.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,
	                                                        ResultSet.CONCUR_UPDATABLE);
			ResultSet rezultat=s.executeQuery("Select * from Utilizatori");
			rezultat.first();
	        
	        while(rezultat.next()){
	        	if(rezultat.getInt("id_utilizator")==id)
	        	{
	        	 status=rezultat.getString("Statut");
	        	}
	         }
	}
	        catch(SQLException f)
		     {
		       f.printStackTrace();
		     } 
	        return status;
		}

    
    /*insereaza in baza de date Utilizatori noul utilizator a carui date au fost citite in fereastra de dialog*/
    public void creareUser() 
	{
		try {
		/*stabilire conexiune cu baza de date Utilizatori*/
		Connection conexBD= DriverManager.getConnection("jdbc:odbc:Personal_Universitate");
		Statement stare = conexBD.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,
                                                        ResultSet.CONCUR_UPDATABLE);
        ResultSet rezultat=stare.executeQuery("Select * from Utilizatori");
        /*introducerea datelor in baza de date*/
        rezultat.last();
        rezultat.updateInt(1,id_utilizator);
        rezultat.updateString(2,facultate);
        rezultat.updateString(3,nume);
        rezultat.updateString(4,prenume);
        rezultat.updateString(5,user);
        rezultat.updateString(6,parola);
        rezultat.updateString(7,statut);
        rezultat.updateString(8,data_inscriere);
        rezultat.updateString(9,data_anulare);
        rezultat.updateString(13,adresa_mail);
        rezultat.insertRow();
        rezultat.updateRow();
	    conexBD.close();//inchidere conexiune
	    }
    
	    catch(SQLException f)
	     {
	       f.printStackTrace();
	     } 
	}
    
    
    /**
     * actualizeaza baza de date utilizatori
     *@param id id-ul utilizatorului care efectueaza imprumutul
     *@param date data in care este efectuat imprumutul
     */
    public static void creareImprumut(int id,String date)
    {
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
		        		rezultat.updateInt(12,Student.NrCartiImprumutate(id)+1);
		        		rezultat.updateString("Data_imprumut",date);
		        		Data dt=new Data(date);
		        		rezultat.updateString("Data_scadenta",Data.addToZi(dt,15).toString());
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
    
    
    /*
     * cauta toti utilizatorii care s-au inscris in aceeasi zi si aceeasi luna cu ziua curenta dar in anul trecut
     * si nu s-au mai reinscris pentru a-i marca cu anulat
     */
    public static void Anulare(Data date)
	{
		try {
			/*stabilire conexiune cu baza de date Utilizatori*/
			Connection conexBD= DriverManager.getConnection("jdbc:odbc:Personal_Universitate");
			Statement stare = conexBD.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,
	                                                        ResultSet.CONCUR_UPDATABLE);
	        ResultSet rezultat=stare.executeQuery("Select * from Utilizatori");
	        while(rezultat.next())
	        {
	        	Data dataexp=new Data(rezultat.getString("Data_anulare").trim());
	        	if(date.ComparaData(dataexp)==1 && rezultat.getString("Data_reinscriere")==null)
	        	{
	        		rezultat.updateString("Observatii","anulat");
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
    
    
    /**
     * Modifica baza de date Utilizatori pentru a marca returnarea materialului dupa ce in prealabil verifica,
     * pentru student daca nu a depasit 15 zile de imprumut
     * @param id_u identifica utilizatorul care returneaza materialul imprumutat
     */
    public static void anulareImprumut(int id_u)
    {
    	//se modifica la fel ca si in Eliberare.eliberareImprumut doar ca BD Utilizatori si coloanele"
    	//nrcarti imprum, se verif dc nu a depasit data imprumut cu 15 zile caz in care se penalizeaza punand in col penalizare da
		try {
			Connection conexBD= DriverManager.getConnection("jdbc:odbc:Personal_Universitate");
			Statement stare = conexBD.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,
		                                                        ResultSet.CONCUR_UPDATABLE);
			ResultSet rezultat=stare.executeQuery("Select * from Utilizatori");
			while(rezultat.next()) {
				if(id_u== rezultat.getInt(1)) {
					rezultat.updateInt(12,rezultat.getInt(12)-1);
					Tranzactii.Data dCurenta = new Tranzactii.Data(InterfataGrafica.MeniuBibliotecar.DataCurenta) ;
					Tranzactii.Data dScadenta = new Tranzactii.Data(rezultat.getString(11));
					if(dCurenta.ComparaData(dScadenta) == 1)
						rezultat.updateString(14, "Da");
					rezultat.updateString(10, "");
					rezultat.updateString(11,"");
					rezultat.updateRow();
		        }
			}
			conexBD.close();
		}
		catch(SQLException f) {
			f.printStackTrace();
		}		
	}
    
    
    /*verifica daca persoana care doreste sa se inscrie nu e deja utilizator, caz in care se face reinscrierea*/
    public static boolean eUtilizator()
    {
    	boolean gasit=false;
    	try
    	{
    		Connection conexBD= DriverManager.getConnection("jdbc:odbc:Personal_Universitate");
	        Statement stare= conexBD.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,
                                                     ResultSet.CONCUR_UPDATABLE);
	        ResultSet rezultat=stare.executeQuery("SELECT * From Utilizatori");
	        /*parcurgere baza de date*/
	        while(rezultat.next())
	        {
	        	String nume=rezultat.getString("Nume");
			    String prenume=rezultat.getString("Prenume");
			    String sir=nume+prenume;
			    if((MeniuBibliotecar.NumeCit).compareTo(sir.trim())==0 && 
			        (Student.eStudent(MeniuBibliotecar.NumeCit) || Profesor.eProfesor(MeniuBibliotecar.NumeCit)))
			    {
			    	rezultat.updateString("Observatii","");
			    	rezultat.updateString("Data_reinscriere",MeniuBibliotecar.DataCurenta);
			    	Data dt=new Data(MeniuBibliotecar.DataCurenta);
			    	Data da=new Data(dt.getZi(),dt.getLuna(),dt.getAn()+1);
			    	rezultat.updateString("Data_anulare",da.toString());
			    	rezultat.updateRow();
			    	gasit=true;
			    }
		    }
	        conexBD.close();//inchidere conexiune
    	}
    	catch(SQLException f)
		   {
			   f.printStackTrace();
	       }      
    	return gasit;
    }
}



