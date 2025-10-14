package InterfataGrafica;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.*;

import InterfataGrafica.FerInregUser.Ascultator;

public class FerCautaPersoana extends JDialog{
	/* declararea componentelor fereastrei de dialog */
	JPanel panou=new JPanel();
    JLabel lblnume=new JLabel();
    JLabel lblprenume=new JLabel();
    JTextField txtnume=new JTextField();
    JTextField txtprenume=new JTextField();
    JPasswordField parolt= new JPasswordField();
    JButton ok=new JButton();
    /**
     * Constructorul clasei FerCautaPersoana
     *@param frame fereastra-parinte
     *@param title titlul ferestrei de dialog
     *@param modal indica daca ferestra de dialog este modala sau nu  
     */
    public FerCautaPersoana(Frame frame,String title,boolean modal) 
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
    void initializare() throws Exception
    {
        /*configurare panou*/
        panou.setMaximumSize(new Dimension(1500,900));
        panou.setPreferredSize(new Dimension(1500,900));
        panou.setLayout(null);
        
        /*configurare etichete*/
        lblnume.setText("Nume");
        lblnume.setBounds(new Rectangle(15,10,258,40));
        lblprenume.setText("Prenume");
        lblprenume.setBounds(new Rectangle(14,50,259,37));
        
        /*configurare buton*/
        ok.setText("OK");
        ok.setBounds(new Rectangle(130,90,90,28));
        
        /*atasare ascultator*/
        Ascultator asc=new Ascultator();
        ok.addActionListener(asc);
        
        /*configurare arii text*/
        txtnume.setBounds(new Rectangle(130,10,250,25));
        txtprenume.setBounds(new Rectangle(130,50,250,25));
        
        /*adaugarea componenetlor la panou*/
        panou.add(lblnume,null);
        panou.add(lblprenume,null);
        panou.add(ok,null);
        panou.add(txtnume,null);
        panou.add(txtprenume,null);
        this.getContentPane().add(panou,null);
       }
    
    class Ascultator implements ActionListener
    {
         /** specifica actiunile la apasarea butonului ok
          * se preia in variabila NumeCitit numele si prenumele
          * persoanei cautate*/
         public void actionPerformed(ActionEvent e) 
         {
             if(e.getSource()==ok)
             {            	
            	MeniuBibliotecar.NumeCit=txtnume.getText()+txtprenume.getText();
            	         	
                 /*fereastra se va ascunde*/
                 setVisible(false);
             }
          }
    }
}

    
    
