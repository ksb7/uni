package InterfataGrafica;

import java.awt.*;
import java.awt.event.*;
import java.sql.*;
import java.util.Scanner;
import java.util.StringTokenizer;

import javax.swing.JFrame;
import javax.swing.JRootPane;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import Tranzactii.*;
import Useri.*;
import Inventar.*;

public class MeniuBibliotecar extends Panel implements ActionListener{
	/**butoanele meniului bibliotecarului*/
	private Button adaugareMaterial,inregistrareUtilizator,stergereUtilizator,seteazaData,
	afisareCarti,afisareUseri,cautareCarte,cautareRevista,cautareUser,retragereExemplar,efImprumut,restituire;
    /**arie text pentru afisare de diferite mesaje*/
	private TextArea text;
	/**Variabila ce va lua ca valoare cota unei carti cautate*/
    public int cotaGasit=-1;  
    /**Variabila ce va lua ca valoare cota citita pentru o carte/revista ce este returnata*/
    public static int CotaCitit; 
    /** contine nume persoana cautata, citit in fereastra de dialog */
    public static String NumeCit;
    /** contine id user cautat, citit in fereastra de dialog */
    public static int id = 0;
    /**Variabila ce retine ziua in care ruleaza aplicatia*/
    public static String DataCurenta;
    //initializeaza DataCurenta
    static {
		DataCurenta = new java.util.Date().getDate()+"."+(new java.util.Date().getMonth()+1)+"."+(new java.util.Date().getYear()+1900);
    }
        
   public void panouPrincipal()
   {        
       /*stabilirea gestionarului de pozitionare*/
       setLayout(new FlowLayout(FlowLayout.CENTER,30,50));
       /*creearea si pesonalizarea butoanelor*/
       adaugareMaterial = new Button();//adauga o carte, atat in bd Material cat si in Carte, nou achizitionata
       adaugareMaterial.setLabel(" ADAUGARE MATERIAL ");
           
       inregistrareUtilizator = new Button();//inscriere de nou utilizator
       inregistrareUtilizator.setLabel(" (RE)INSCRIERE UTILIZATOR ");
       
       stergereUtilizator= new Button();//marcare utilizator ca expirat
       stergereUtilizator.setLabel(" STERGE UTILIZATOR ");
                     
       cautareUser = new Button();//cauta utilizator in Bd
       cautareUser.setLabel(" CAUTA UTILIZATOR ");
     
       cautareCarte = new Button();//cauta carte in bd
       cautareCarte.setLabel(" CAUTA CARTE ");
       
       cautareRevista = new Button();//cauta carte in bd
       cautareRevista.setLabel(" CAUTA REVISTA ");
              
       afisareCarti = new Button();//vizualizare bd carti
       afisareCarti.setLabel(" CATALOG ");
       
       afisareUseri = new Button();//vizualizare bd useri
       afisareUseri.setLabel(" BAZA DE DATE UTILIZATORI ");

       retragereExemplar = new Button();//retragere exemplar pt reconditionare/definitiv
       retragereExemplar.setLabel(" RETRAGE EXEMPLAR ");
       
       efImprumut = new Button();//imprumut
       efImprumut.setLabel(" IMPRUMUT ");
       
       restituire = new Button();//restituire carte
       restituire.setLabel(" RESTITUIRE ");
      
       seteazaData = new Button();//restituire carte
       seteazaData.setLabel(" SETARE DATA ");
       
       /*adaugarea butoanelor*/
       add(adaugareMaterial);
       add(inregistrareUtilizator);
       add(stergereUtilizator);
       add(cautareUser);
       add(cautareCarte);
       add(cautareRevista);
       add(afisareCarti);
       add(afisareUseri);
       add(efImprumut);
       add(restituire);
       add(retragereExemplar);
       add(seteazaData);
       
       /*atasarea ascultatorilor*/
       adaugareMaterial.addActionListener(this);
       inregistrareUtilizator.addActionListener(this);
       stergereUtilizator.addActionListener(this);
       afisareCarti.addActionListener(this);
       afisareUseri.addActionListener(this);
       cautareUser.addActionListener(this);
       cautareCarte.addActionListener(this);
       cautareRevista.addActionListener(this);
       efImprumut.addActionListener(this);
       restituire.addActionListener(this);
       retragereExemplar.addActionListener(this);
       seteazaData.addActionListener(this);
       
       /*crearea unei arii text needitabila cu 20 randuri si 50 coloane*/
       text = new TextArea(10,50);
       text.setFont(new Font("Serif",Font.BOLD,14));
       text.setBackground(Color.WHITE);
       text.setForeground(Color.BLUE);
       text.setEditable(false);  
       
       /*adaugarea ariei text*/
       add(text);  
   }
   
   /** stabilirea actiunilor efectuate la un click cu mouse-ul pe butonul dorit*/
   public void actionPerformed(ActionEvent e)
   {
	 
	      //cautare utilizator; se va intoarce id-ul utilizatorului cautat dupa nume si prenume  
	   if(e.getSource()== cautareUser)
	   {
		   try
		   {
			   /*stabilire conexiune cu baza de date Utilizatori*/
    		   Connection conexBD= DriverManager.getConnection("jdbc:odbc:Personal_Universitate");
    		   Statement s= conexBD.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,
                                                               ResultSet.CONCUR_UPDATABLE);
               ResultSet rezultat=s.executeQuery("select * from Utilizatori");
               FerCautaPersoana f1=new FerCautaPersoana(null,"Cauta User",true);
               id=0;
               while(rezultat.next())
               {
            	   String nume=rezultat.getString("Nume").trim();
			       String prenume=rezultat.getString("Prenume").trim();
			       String sir=nume+prenume;
			       if(NumeCit.compareTo(sir)==0)
			        id=rezultat.getInt("Id_utilizator");
                }    
           }
		   catch(SQLException f)
		   {
			   f.printStackTrace();
      	   }
		   System.out.println(id);
        }
	   
	   //(re)inscrierea unui student/profesor ca utilizator al bibliotecii
	   if(e.getSource() == inregistrareUtilizator)
       {
		   FerCautaPersoana f1=new FerCautaPersoana(null,"Cautare Persoana",true);
		   if(Utilizator.eUtilizator()==false)//daca nu e inscrise deja se va face inscrierea
		   { 
			   if(Student.eStudent(NumeCit)==true)
			   {
				   FerInregUser f2=new FerInregUser(null,"Inregistare Utilizator",true);
				   text.setText("Studentul a fost inscris");
			   }
			   else
			   {
   			       /*parcurgere baza de date Profesori pentru a verifica daca persoana e cadru didactic,
   	                 caz in care se inregistreaza ca utilizator*/
   			       if(Profesor.eProfesor(NumeCit)==true)
   			       {
   			    	   FerInregUser f3=new FerInregUser(null,"Inregistare Utilizator",true);
   			    	   text.setText("Profesorul a fost inscris");
   			       }
   			       else text.setText("Nu e nici student, nici cadru didactic");
			   }
  	        }//utilizatorul a fost deja inscris
			else text.setText("Utilizatorul a fost reinscris");
       }

	   
	   //efectuare imprumut
	   if(e.getSource()== efImprumut)
	   {
		   if((cotaGasit == -1) || (id == 0))
			   text.setText(" Mai intai efectuati cautarea materialului si a utilizatorului ");
		   else
			   
		   {
			   if(Imprumut.creareImprumut(cotaGasit,DataCurenta)==true)
				   text.setText("Imprumut realizat cu succes!");
			   else text.setText("Nu se poate realiza imprumutul!Utilizatorul este rugat sa restituie o carte sau sa efectueze plata penalizarii!");
		   }		   
	   }
	   
	   //inserarea unei noi carti in bd
	   if(e.getSource()== adaugareMaterial)
	   {
		   text.setText("");
		   FerInserMaterial fer=new FerInserMaterial(null,"Date Material",true);
		   text.setText("Material adaugat cu succes");
       }
  
	   //vizualizarea catalogului bibliotecii
	   if(e.getSource()==afisareCarti)
       {
           int i=-1;//variabila contor
           int j=-1;//variabila contor
           /* variabila de tip tablou bidimensional in care tinem datele preluate din baza de date */
           Object[][] liniiDate=new Object[100][9];
           /* numele coloanelor tabelului */
           String[] numeColoane={"TIP MATERIAL","TITLU","AUTOR","NUMAR EXEMPLARE"};
           /*stabilire conexiune cu baza de date Material si preluarea datelor in matricea liniiDate*/
           text.setText("Mariti Ferestra ce contine Baza de Date");
           try
           {
        	   /*stabilire conexiune cu baza de date Material*/
               Connection conexBD= DriverManager.getConnection("jdbc:odbc:Personal_Universitate");
   	           Statement stare= conexBD.createStatement();
   	           ResultSet rezultat=stare.executeQuery("SELECT * From Material");
               /*parcurgere baza de date*/
		       while(rezultat.next())
               {
		    	   j=-1;
                   i++;
                   
                   j++;
                   String tip=rezultat.getString("Tip_material");
                   liniiDate[i][j]=tip;
                   
                   j++;
                   String titlu = rezultat.getString("Titlu");
                   liniiDate[i][j]=titlu;
                   
                   j++;
                   String autor= rezultat.getString("Autor");
                   liniiDate[i][j]=autor;
                                           
                   j++;
	               String nr=rezultat.getString("Nr_exemplare");
                   liniiDate[i][j]=nr;
                }
               conexBD.close();//inchidere conexiune
           }
           catch(SQLException f)
	    {
               f.printStackTrace();
	    }  
           /* creare tabela ce va contine inregistrarile bazei de date */
           JFrame f=new JFrame("Catalogul bibliotecii");
           f.setUndecorated(true);
           f.getRootPane().setWindowDecorationStyle(JRootPane.FRAME);
           JTable tabela=new JTable(liniiDate,numeColoane);
           JScrollPane jsp=new JScrollPane(tabela);//coordonate prelucrare fereastra
           f.getContentPane().add(jsp,BorderLayout.CENTER);
           f.setVisible(true); 
       }
	   
	   //vizualizarea bazei de date ce contine userii
	   if(e.getSource()==afisareUseri)
       {
           int i=-1;//variabila contor
           int j=-1;//variabila contor
           /* variabila de tip tablou bidimensional in care tinem datele preluate din baza de date */
           Object[][] liniiDate=new Object[100][16];
           /* numele coloanelor tabelului */
           String[] numeColoane={"ID_UTILIZATOR","FACULTATE","NUME","PRENUME","USER","PAROLA","DATA INSCRIERE",
        		                 "DATA ANULARE","DATA IMPRUMUT","DATA SCADENTA","NR. CARTI IMPRUMUTATE",
        		                 "ADRESA EMAIL","PENALIZARE","DATA REINSCRIERE","OBSERVATII"};
           /*stabilire conexiune cu baza de date Carte si preluarea datelor in matricea liniiDate*/
           text.setText("Mariti Ferestra ce contine Baza de Date");
           try
	    {
               /*stabilire conexiune cu baza de date Utilizatori*/
               Connection conexBD= DriverManager.getConnection("jdbc:odbc:Personal_Universitate");
               Statement stare= conexBD.createStatement();
   	           ResultSet rezultat=stare.executeQuery("SELECT * From Utilizatori");
               /*parcurgere baza de date*/
		       while(rezultat.next())
               {
                   j=-1;
                   i++;
                   j++;
                   String id=rezultat.getString("Id_utilizator");
                   liniiDate[i][j]=id;
               
                   j++;
                   String facultate=rezultat.getString("Facultate");
                   liniiDate[i][j]=facultate;
                   
                   j++;
                   String nume = rezultat.getString("Nume");
                   liniiDate[i][j]=nume;
                   
                   j++;
                   String prenume= rezultat.getString("Prenume");
                   liniiDate[i][j]=prenume;
                           
                   j++;
	               String user=rezultat.getString("User");
                   liniiDate[i][j]=user;
               
                   j++;
                   String  parola= rezultat.getString("Parola");
                   liniiDate[i][j]=parola;
              
                   j++;
	               String data_ins=rezultat.getString("Data_inscriere");
                   liniiDate[i][j]=data_ins;
                   
                   j++;
	               String data_a=rezultat.getString("Data_anulare");
                   liniiDate[i][j]=data_a;
                   j++;
                   String data_i=rezultat.getString("Data_imprumut");
                   liniiDate[i][j]=data_i;
                   
                   j++;
	               String data_s=rezultat.getString("Data_scadenta");
                   liniiDate[i][j]=data_s;
                   
                   j++;
	               String nr=rezultat.getString("Nr_carti_imprumutate");
                   liniiDate[i][j]=nr;
                   
                   j++;
	               String adr=rezultat.getString("Adresa_Email");
                   liniiDate[i][j]=adr;
                   
                   j++;
	               String penalizare=rezultat.getString("Penalizare");
                   liniiDate[i][j]=penalizare;
                   
                   j++;
	               String data_inscriere=rezultat.getString("Data_reinscriere");
                   liniiDate[i][j]=data_inscriere;
                   
                   j++;
	               String obs=rezultat.getString("Observatii");
                   liniiDate[i][j]=obs;
                }
               conexBD.close();//inchidere conexiune
           }
           catch(SQLException f)
           {
               f.printStackTrace();
	       }  
           /* creare tabela ce va contine inregistrarile bazei de date */
           JFrame f=new JFrame("Utilizatori biblioteca");
           f.setUndecorated(true);
           f.getRootPane().setWindowDecorationStyle(JRootPane.FRAME);
           JTable tabela=new JTable(liniiDate,numeColoane);
           JScrollPane jsp=new JScrollPane(tabela);//coordonate prelucrare fereastra
           f.getContentPane().add(jsp,BorderLayout.CENTER);
           f.setVisible(true); 
       }
	   
	   //cautarea unei carti dupa titlu sau autor
	   if(e.getSource()== cautareCarte)
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
	             if(MeniuUtilizator.optiune.compareTo("A")==0)
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
	                         if (MeniuUtilizator.AutorGasit.compareTo(aut)==0) 
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
	                                 if (MeniuUtilizator.TitluGasit.compareTo(titlu1)==0)  
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
		 
		 //cautarea unei reviste in catalogul bibliotecii
		 if(e.getSource()== cautareRevista)
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
                        if (MeniuUtilizator.TitluRev.compareTo(titlu)==0)  
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

   //stergere(marcare) utilizator (ca si expirat)      
   if(e.getSource()==stergereUtilizator)
   {
	   Data date= new Data(DataCurenta);
	   Utilizator.Anulare(date);
	   text.setText("Baza de date a fost reactualizata");
   }
   
  

   //retragere pentru reconditionare
   if(e.getSource()==retragereExemplar)
   {
	  Material.cautareStare(); 
	  text.setText("Baza de date a fost reactualizata");
   }
   
   //restiutuire carte
   if(e.getSource()==restituire)
   {
	   if(id==0)
	   {
		   text.setText("Cautati intai userul care inapoiaza cartea");
	   }
	   else
	   {
		    FerCitesteCota f=new FerCitesteCota(null,"Cota",true);
		    Eliberare.eliberareImprumut(CotaCitit,id);
		    text.setText("Operatie realizata cu succes");
	   }
   }
   
   if(e.getSource()==seteazaData)
   {
	   FerSetData fer=new FerSetData(null,"Seteaza Data",true);
	   text.setText("Data a fost setata");
   }
   
   }
}
       

   
   


