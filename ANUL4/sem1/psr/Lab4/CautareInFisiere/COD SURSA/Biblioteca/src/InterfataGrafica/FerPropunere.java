package InterfataGrafica;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.sql.SQLException;

import javax.swing.*;
import Inventar.*;
import Useri.*;

public class FerPropunere extends JDialog{

	/* declararea componentelor fereastrei de dialog */
	JPanel panou=new JPanel();
    JLabel autor=new JLabel();
    JLabel titlu=new JLabel();
    JTextField autort=new JTextField();
    JTextField titlut=new JTextField();
    JPasswordField parolt= new JPasswordField();
    JButton ok=new JButton();

    /**
     * Constructorul clasei FerInserCarte
     *@param frame fereastra-parinte
     *@param title titlul ferestrei de dialog
     *@param modal indica daca ferestra de dialog este modala sau nu  
     */
    public FerPropunere(Frame frame,String title,boolean modal) 
    {
        /*apel la constructorul superclasei*/
        super(frame,title,modal);
        try
        {
            initializare();
             /*pozitionam fereastra si ii setam dimensiunile*/
            Dimension marimeEcran=Toolkit.getDefaultToolkit().getScreenSize();
            int pozitie=230;
            setBounds(pozitie,pozitie,400,200);
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
     /**
     * creeaza componentele ferestrei de dialog
     *un panou care tine etichetele campurilor aferente
     * ariilor text in care se citesc datele noii carti
     */
    void initializare() throws Exception
    {
        /*configurare panou*/
        panou.setMaximumSize(new Dimension(1500,900));
        panou.setPreferredSize(new Dimension(1500,900));
        panou.setLayout(null);
        
        /*configurare etichete*/
        autor.setText("Autor");
        autor.setBounds(new Rectangle(13,10,259,37));
        titlu.setText("Titlu");
        titlu.setBounds(new Rectangle(13,50,258,40));
                
        /*configurare buton*/
        ok.setText("OK");
        ok.setBounds(new Rectangle(120,90,90,28));
        
        /*atasare ascultator*/
        Ascultator asc=new Ascultator();
        ok.addActionListener(asc);
        
        /*configurare arii text*/
        autort.setBounds(new Rectangle(130,10,259,25));
        titlut.setBounds(new Rectangle(130,50,259,25));
               
        /*adaugarea componenetlor la panou*/
       
        panou.add(autor,null);
        panou.add(titlu,null);
        panou.add(ok,null);
        panou.add(autort,null);
        panou.add(titlut,null);
        this.getContentPane().add(panou,null);
       }
    
    class Ascultator implements ActionListener
    {
         /** specifica actiunile la apasarea butonului ok
          * se apeleza constructorul clasei carte
          * iar apoi se apeleaza functia se inserare a noii
          * carti in baza de date a cartilor
         * @throws SQLException */
         public void actionPerformed(ActionEvent e)  
         {
             if(e.getSource()==ok)
             {
            	Profesor.propune(titlut.getText(),autort.getText());     	
                /*fereastra se va ascunde*/
                setVisible(false);
      }
    }
    }
}

