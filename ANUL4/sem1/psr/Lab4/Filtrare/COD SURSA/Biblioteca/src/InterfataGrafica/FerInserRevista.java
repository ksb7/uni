package InterfataGrafica;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.*;
import Inventar.*;

public class FerInserRevista extends JDialog{

	/* declararea componentelor fereastrei de dialog */
	JPanel panou=new JPanel();
    JLabel lblcota=new JLabel();
    JLabel lbltitlu=new JLabel();
    JLabel lblperiodicitate=new JLabel();
    JLabel lblnumar=new JLabel();
    JTextField txttitlu=new JTextField();
    JTextField txtcota=new JTextField();
    JTextField txtperiodicitate=new JTextField();
    JTextField txtnumar=new JTextField();
    JPasswordField parolt= new JPasswordField();
    JButton ok=new JButton();

    /**
     * Constructorul clasei FerInserRevista
     *@param frame fereastra-parinte
     *@param title titlul ferestrei de dialog
     *@param modal indica daca ferestra de dialog este modala sau nu  
     */
    public FerInserRevista(Frame frame,String title,boolean modal) 
    {
        /*apel la constructorul superclasei*/
        super(frame,title,modal);
        try
        {
            initializare();
             /*pozitionam fereastra si ii setam dimensiunile*/
            Dimension marimeEcran=Toolkit.getDefaultToolkit().getScreenSize();
            int pozitie=200;
            setBounds(pozitie,pozitie,400,250);
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
        lblcota.setText("Cota ");
        lblcota.setBounds(new Rectangle(15,10,258,40));
        lblperiodicitate.setText("Periodicitate");
        lblperiodicitate.setBounds(new Rectangle(14,50,259,37));
        lbltitlu.setText("Titlu");
        lbltitlu.setBounds(new Rectangle(13,90,258,40));
        lblnumar.setText("Numar");
        lblnumar.setBounds(new Rectangle(13,130,258,40));       
        /*configurare buton*/
        ok.setText("OK");
        ok.setBounds(new Rectangle(120,170,90,28));
        
        /*atasare ascultator*/
        Ascultator asc=new Ascultator();
        ok.addActionListener(asc);
        
        /*configurare arii text*/
        txtcota.setBounds(new Rectangle(130,10,119,25));
        txtperiodicitate.setBounds(new Rectangle(130,50,259,25));
        txttitlu.setBounds(new Rectangle(130,90,259,25));
        txtnumar.setBounds(new Rectangle(130,130,259,25));  
        
        /*adaugarea componenetlor la panou*/
        panou.add(lblcota,null);
        panou.add(lbltitlu,null);
        panou.add(lblnumar,null);
        panou.add(lblperiodicitate,null);
        panou.add(ok,null);
        panou.add(txtcota,null);
        panou.add(txtnumar,null);
        panou.add(txtperiodicitate,null);
        panou.add(txttitlu,null);
                
        this.getContentPane().add(panou,null);
       }
    
    class Ascultator implements ActionListener
    {
         /** specifica actiunile la apasarea butonului ok
          *  se apeleza constructorul clasei Revista
          * iar apoi se apeleaza functia se inserare a noii
          * reviste in baza de date a revistelor*/
         public void actionPerformed(ActionEvent e) 
         {
             if(e.getSource()==ok)
             {
            	 Revista rev=new Revista(Integer.parseInt(txtcota.getText()),txttitlu.getText(),
            			                 Integer.parseInt(txtperiodicitate.getText()),Integer.parseInt(txtnumar.getText()));
            	 rev.updateBdRevista();                 
                 /*fereastra se va ascunde*/
                 setVisible(false);
             }
         }
    }
}
