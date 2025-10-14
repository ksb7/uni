package Inventar;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import InterfataGrafica.*;

public  class Material {
	
	/**
	 *  Titlul materialului
	 */
	public String titlu;
	/**
	 *  Autorul materialului
	 */
	public String autor;
	/**
	 *  Numarul de exemplare disponibile
	 */
	public int nrExDisp;	
	/**
	 * Tipul materialulu: carte sau revista 
	 */
	private String tipMaterial; 
	
		
	/**
	 * 
	 * @param titlu Titlul noului material
	 * @param autor Autorul noului material
	 * @param tipmaterial indica daca e carte sau revista
	 * @param nrExDisp Numarul de exemplare disponibile
	 */
	public Material(String tipmaterial,String titlu,String autor,int nrex)
	{
		this.titlu = titlu;
		if(tipmaterial.compareToIgnoreCase("revista")==0)
			this.autor=null;
		else this.autor = autor;
		this.tipMaterial=tipmaterial;
		this.nrExDisp = nrex;
	}
	
	
	/*se actualizeaza baza de date Material apoi se vor actualiza si bazele de date corespunzatoare
	 * noile materiale achizitionate in functie de tipul acestora */
	public  void updateBdMaterial() 
	{
		try
		{
			/*stabilire conexiune cu baza de date Material*/
		    Connection conexBD= DriverManager.getConnection("jdbc:odbc:Personal_Universitate");
		    Statement stare = conexBD.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,
                                                      ResultSet.CONCUR_UPDATABLE);
            ResultSet rezultat=stare.executeQuery("Select * from Material");
            /*introducerea datelor in baza de date*/
            rezultat.last();
            rezultat.updateString("Tip_material",tipMaterial);
            rezultat.updateString("Titlu",titlu);
            rezultat.updateString("Autor",autor);
            rezultat.updateInt("Nr_exemplare",nrExDisp);
            rezultat.insertRow();
            rezultat.updateRow();
	        conexBD.close();//inchidere conexiune
	    }
	    catch(SQLException f)
	     {
	       f.printStackTrace();
	     } 	
		if(tipMaterial.compareToIgnoreCase("carte")==0)
		{
			for (int i=0;i<nrExDisp;i++)
			{
				FerInserCarte f1=new FerInserCarte(null,"Carte Noua",true);
			}		
		}
		else 
		{
			FerInserRevista f2=new FerInserRevista(null,"Revista Noua",true);
		}
	}
	
	/*va verifica starea tuturor cartilor si revistelor pentru a le trimite spre reconditionare sau
	 *a le retrage din uz*/
	public static void cautareStare()
	{
		Carte.cautareStare();
		Revista.cautareStare();
	}
	
}
