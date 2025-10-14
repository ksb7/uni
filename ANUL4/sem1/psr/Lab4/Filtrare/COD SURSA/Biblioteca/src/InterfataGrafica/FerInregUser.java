package InterfataGrafica;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.*;

import Useri.*;

import InterfataGrafica.FerInserCarte.Ascultator;

public class FerInregUser extends JDialog{
	
	/* declararea componentelor fereastrei de dialog */
	JPanel panou=new JPanel();
    JLabel lblnume=new JLabel();
    JLabel lblprenume=new JLabel();
    JLabel lblid=new JLabel();
    JLabel lblfacult=new JLabel();
    JLabel lbldtinscr=new JLabel();
    JLabel lbladremail=new JLabel();
    JLabel lbldtanulare=new JLabel();
    JLabel lblUser=new JLabel();
    JLabel lblParola=new JLabel();
    JLabel lblStatut=new JLabel();
    JTextField txtid=new JTextField();
    JTextField txtnume=new JTextField();
    JTextField txtprenume=new JTextField();
    JTextField txtfacult=new JTextField();
    JTextField txtdtinscr=new JTextField();
    JTextField txtdtanulare=new JTextField();
    JTextField txtemail=new JTextField();
    JTextField txtUser=new JTextField();
    JTextField txtParola=new JTextField();
    JTextField txtStatut=new JTextField();
    JPasswordField parolt= new JPasswordField();
    JButton ok=new JButton();
    
    /**
     * Constructorul clasei FerInregUser
     *@param frame fereastra-parinte
     *@param title titlul ferestrei de dialog
     *@param modal indica daca ferestra de dialog este modala sau nu  
     */
    public FerInregUser(Frame frame,String title,boolean modal) 
    {
        /*apel la constructorul superclasei*/
        super(frame,title,modal);
        try
        {
            initializare();
             /*pozitionam fereastra si ii setam dimensiunile*/
            Dimension marimeEcran=Toolkit.getDefaultToolkit().getScreenSize();
            int pozitie=200;
            setBounds(pozitie,pozitie,400,500);
            /* specificam modul de reactie a ferestrei la inchidere */
            addWindowListener(new WindowAdapter()
            {
                public void windowClosing(WindowEvent e)
                {
                    /*eliberam resursele*/
                    e.getWindow().dispose();
                }
            });
            /*afisarea ferestrei*/
            setVisible(true);
            parolt.requestFocusInWindow();
        }
        catch(Exception ex)
        {
            ex.printStackTrace();
        }
    }
    
    void initializare() throws Exception
    {
        /*configurare panou*/
        panou.setMaximumSize(new Dimension(1500,900));
        panou.setPreferredSize(new Dimension(1500,900));
        panou.setLayout(null);
        /*configurare etichete*/
        lblid.setText("Id ");
        lblid.setBounds(new Rectangle(15,10,258,40));
        lblnume.setText("Nume");
        lblnume.setBounds(new Rectangle(14,50,259,37));
        lblprenume.setText("Prenume");
        lblprenume.setBounds(new Rectangle(13,90,258,40));
        lblfacult.setText("Facultate");
        lblfacult.setBounds(new Rectangle(13,130,258,40));
        lbladremail.setText("Adr email");
        lbladremail.setBounds(new Rectangle(13,170,258,40));
        lbldtinscr.setText("Data inscr");
        lbldtinscr.setBounds(new Rectangle(13,210,258,40));
        lbldtanulare.setText("Data anulare");
        lbldtanulare.setBounds(new Rectangle(13,250,258,40));
        lblUser.setText("User");
        lblUser.setBounds(new Rectangle(13,290,258,40));
        lblParola.setText("Parola");
        lblParola.setBounds(new Rectangle(13,330,258,40));
        lblStatut.setText("Statut");
        lblStatut.setBounds(new Rectangle(13,370,258,40));
        
        /*configurare buton*/
        ok.setText("OK");
        ok.setBounds(new Rectangle(150,420,90,28));
        
        /*atasare ascultator*/
        Ascultator asc=new Ascultator();
        ok.addActionListener(asc);
        
        /*configurare arii text*/
        txtid.setBounds(new Rectangle(130,10,120,25));
        txtnume.setBounds(new Rectangle(130,50,250,25));
        txtprenume.setBounds(new Rectangle(130,90,250,25));
        txtfacult.setBounds(new Rectangle(130,130,250,25));
        txtemail.setBounds(new Rectangle(130,170,250,25));
        txtdtinscr.setBounds(new Rectangle(130,210,250,25));
        txtdtanulare.setBounds(new Rectangle(130,250,250,25));
        txtUser.setBounds(new Rectangle(130,290,250,25));
        txtParola.setBounds(new Rectangle(130,330,250,25));
        txtStatut.setBounds(new Rectangle(130,370,250,25));
        
        /*adaugarea componenetlor la panou*/
        panou.add(lblid,null);
        panou.add(lblnume,null);
        panou.add(lblprenume,null);
        panou.add(lblfacult,null);
        panou.add(lbladremail,null);
        panou.add(lbldtinscr,null);
        panou.add(lbldtanulare,null);
        panou.add(lblUser,null);
        panou.add(lblParola,null);
        panou.add(lblStatut,null);
        panou.add(ok,null);
        panou.add(txtid,null);
        panou.add(txtnume,null);
        panou.add(txtprenume,null);
        panou.add(txtfacult,null);
        panou.add(txtemail,null);
        panou.add(txtdtinscr,null);
        panou.add(txtdtanulare,null);
        panou.add(txtUser,null);
        panou.add(txtParola,null);
        panou.add(txtStatut,null);
        this.getContentPane().add(panou,null);
       }
    
    class Ascultator implements ActionListener
    {
         /** specifica actiunile la apasarea butonului ok
          * se apeleaza constructorul clasei utilizator
          * iar apoi se apeleaza functia se inserare a noului
          * utilizator in baza de date a utilizatorilor*/
         public void actionPerformed(ActionEvent e) 
         {
             if(e.getSource()==ok)
             {
            	Utilizator util=new Utilizator(Integer.parseInt(txtid.getText()),txtfacult.getText(),txtnume.getText(),txtprenume.getText(),
            	                               txtUser.getText(),txtParola.getText(),txtStatut.getText(),
            	                               txtdtinscr.getText(),txtemail.getText(),txtdtanulare.getText());
                 util.creareUser();
            	 //fereastra se va ascunde
                 setVisible(false);
      }
    }
    }
}



