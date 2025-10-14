package InterfataGrafica;

import java.awt.*;
import java.awt.event.*;
import java.sql.*;
import Useri.*;

public class MeniuUtilizator extends Panel implements ActionListener{
	/**butoanele meniului utilizatorului*/
	private Button cautareCarte,cautareRevista,autentificare,propune,iesire,ghiseu;
	/**arie text pentru afisare de diferite mesaje*/
	private TextArea text;
	public static boolean autentificat=false;
	public static String optiune;
	/**Variabila ce va lua ca valoare cota unei carti cautate*/
	private int  cotaGasit=-1;
	/** contine autorul de cautat, citit in fereastra de dialog */
    public static String AutorGasit;
    /** contine titlul de cautat, citit in fereastra de dialog */
    public static String TitluGasit,TitluRev;
    public static int id_u;

        
	public void panouPrincipal()
    {        
        /*stabilirea gestionarului de pozitionare*/
		setLayout(new FlowLayout(FlowLayout.CENTER,40,50));
        /*creearea si pesonalizarea butoanelor*/
        autentificare = new Button("   AUTENTIFICARE ");
        
        cautareCarte = new Button(" CAUTARE CARTE ");
        
        cautareRevista = new Button(" CAUTARE REVISTA ");
        
        propune = new Button(" INREGISTRARE PROPUNERE ");
       
        iesire = new Button(" LOGOUT ");
        
        ghiseu = new Button(" GHISEU ");
                     
        /*adaugarea butoanelor*/
        add(autentificare);
        add(cautareCarte);
        add(cautareRevista);
        add(propune);
        add(ghiseu);
        add(iesire);
        
        /*atasarea ascultatorilor*/
        autentificare.addActionListener(this);
        cautareCarte.addActionListener(this);
        cautareRevista.addActionListener(this);
        propune.addActionListener(this);
        ghiseu.addActionListener(this);
        iesire.addActionListener(this);
        
        /*crearea unei arii text needitabila cu 20 randuri si 50 coloane*/
        text = new TextArea(10,50);
        text.setFont(new Font("Serif",Font.BOLD,14));
        text.setBackground(Color.WHITE);
        text.setForeground(Color.BLUE);
        text.setEditable(false);       
        /*adaugarea ariei text*/
        add(text);  
    }
	
	 public void actionPerformed(ActionEvent e){
		 
		 //autentificare utilizator
		 if(e.getSource() == autentificare)
		 {
			 FerAutentificare fer=new FerAutentificare(null,"Autentificare",true);
			 if (autentificat==false)
				 text.setText("Invalid Username/password !");
			 else text.setText("Autenificare reusita");
		 }
		 
		 //cautarea unei carti in catalogul bibliotecii dupa titlu sau autor
		 if(e.getSource()== cautareCarte)
		 {
			 if(autentificat==false)
				 text.setText("Mai intai trebuie sa va autentificati!");
			 else
			 {
			 text.setText("Alegeti un tip de cautare");
			 cotaGasit=-1;
	         text.setText("");
	         try
	         {
	        	 /*stabilire conexiune cu baza de date Carte*/
			     Connection conexBD= DriverManager.getConnection("jdbc:odbc:Personal_Universitate");
			     Statement s= conexBD.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,
	                                                             ResultSet.CONCUR_UPDATABLE);
	             ResultSet rezultat=s.executeQuery("select * from Carte");
	             /*se citeste optiunea de cautare in fereastra de dialog*/
	             FerDialogOptiuneCautare f1=new FerDialogOptiuneCautare(null,"Optiune cautare",true);
	             int optiune1=-1;//retine optiunea utilizatorului
	             if(optiune.compareTo("A")==0)
	            	 optiune1=1;
	             else optiune1=2;
	             /*in functie de optiunea utilizatorului se va face cautarea unei carti*/
	             switch(optiune1)
	             {
	             	case 1:/*cautare dupa numele autorului*/
	             		text.setText("Autor: Nume si Prenume ");
	                    FerCautaDupaAutor f2=new FerCautaDupaAutor(null,"Autor",true); 
	                    text.setText("Cartile existente sunt: ");
	                    int gasit=0;
	                    while(rezultat.next())
	                    	{
	                         String aut=rezultat.getString("Autor");
	                         if (AutorGasit.compareTo(aut)==0) 
	                         {
	                        	 gasit=1;
	                             String unTitlu=rezultat.getString("Titlu");
	                             String disp=rezultat.getString("Disponibilitate");
	                             int cota=rezultat.getInt("Cota");
	                             text.append("Titlu:"+unTitlu+" "+"Cota:"+cota+" "+"Disponibilitate:"+disp+"; ");
	                          }
	                         }
	                           /*daca nu s-a gasit autorul cautat se va afisa un mesaj*/
	                           if(gasit==-1)
	                    	     text.setText("Autorul nu exista in BD!");
	                           break;
	                    case 2:/*cautare dupa titlul cartii*/
	                             FerCautaDupaTitlu f5=new FerCautaDupaTitlu(null,"Titlu",true); 
	                             rezultat.first();
	                             gasit=-1;
	                             while(rezultat.next())
	                             {
	                                 String titlu1=rezultat.getString("Titlu");
	                                 if (TitluGasit.compareTo(titlu1)==0)  
	                                 {
	                                	 gasit=1;
	                                     text.setText(titlu1);
	                                     String aut=rezultat.getString("Autor");
	                                     cotaGasit=rezultat.getInt("Cota");
	                                     String disp=rezultat.getString("Disponibilitate");
	                                     text.setText(titlu1+" Autor: "+aut+" Cota:"+cotaGasit+" Disponibilitate:"+disp);
	                                 }
	                             }
	                             if (gasit==-1)
	                                 text.setText("Nu exista acest titlu in baza de date!");
	                             break;
	                    default: 
	                            break;
	                }
	              conexBD.close();//inchidere conexiune
	            }
	            catch(SQLException f)
	            {
	            	f.printStackTrace();
		        }  
	            
     	 }
	 }
		 
		 //cautarea unei reviste in catalogul bibliotecii
		 if(e.getSource()== cautareRevista)
		 {
			 if(autentificat==false)
				 text.setText("Mai intai trebuie sa va autentificati!");
			 else
			 {
			    cotaGasit=-1;
	            text.setText("");
	            try
	            {
	                /*stabilire conexiune cu baza de date Carte*/
			        Connection conexBD= DriverManager.getConnection("jdbc:odbc:Personal_Universitate");
			        Statement s= conexBD.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,
	                                                             ResultSet.CONCUR_UPDATABLE);
	                ResultSet rezultat=s.executeQuery("select * from Reviste");
	                FerCautaRev f6=new FerCautaRev(null,"Cauta Revista",true); 
                    rezultat.first();
                    while(rezultat.next())
                    {
                        String titlu=rezultat.getString("Titlu");
                        if (TitluRev.compareTo(titlu)==0)  
                        {
                            text.setText(titlu);
                            cotaGasit=rezultat.getInt("Cota");
                            String disp=rezultat.getString("Disponibilitate");
                            int nr=rezultat.getInt("Numar");
                            text.setText("Cota "+cotaGasit+" Disponibilitate:"+disp+"Nr:"+nr);
                        }
                    }
                    if (cotaGasit==-1)
                        text.setText("Nu exista acest titlu in baza de date!");                 
	            }
	            catch(SQLException f)
			    {
		                f.printStackTrace();
			    }  
			 }
		 }
		 
		 //efectuare propunere de nou material, doar daca este profesor
		 if(e.getSource()== propune)
		 {
			 if(autentificat==false)
				 text.setText("Mai intai trebuie sa va autentificati!");
			 else
			 {
				if (Utilizator.getStatut(id_u).compareTo("profesor")==0)
			    {
			     FerPropunere f=new FerPropunere(null,"Propune",true);
			    	
			    }
			    else
			    text.setText("Nu sunteti autorizat sa faceti o propunere!");
			            
			 }		 
		 }
		 
		 //lansarea meniului bibliotecar
		 if(e.getSource() == ghiseu)
		 {
			 FereastraMea fer=new FereastraMea("Meniu Bibliotecar");
		     MeniuBibliotecar meniu = new MeniuBibliotecar(); 
		     fer.add(meniu);
		     meniu.panouPrincipal();
		     /*afisarea ferestrei*/
		     fer.setVisible(true); 
		 }
		
		 //logout utilizatorul nu mai este autentificat
		if (e.getSource()==iesire)
		 {
			 autentificat=false;
		 }
	 }
}
