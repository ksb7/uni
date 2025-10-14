package InterfataGrafica;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.*;
import Inventar.*;

public class FerInserMaterial extends JDialog{

	/* declararea componentelor fereastrei de dialog */
	JPanel panou=new JPanel();
    JLabel lbltipmaterial=new JLabel();
    JLabel lbltitlu=new JLabel();
    JLabel lblautor=new JLabel();
    JLabel lblnrex=new JLabel();
    JTextField txtautor=new JTextField();
    JTextField txttitlu=new JTextField();
    JTextField txttipmaterial=new JTextField();
    JTextField txtnrex=new JTextField();
    JPasswordField parolt= new JPasswordField();
    JButton ok=new JButton();

    /**
     * Constructorul clasei FerMaterial
     *@param frame fereastra-parinte
     *@param title titlul ferestrei de dialog
     *@param modal indica daca ferestra de dialog este modala sau nu  
     */
    public FerInserMaterial(Frame frame,String title,boolean modal) 
    {
        /*apel la constructorul superclasei*/
        super(frame,title,modal);
        try
        {
            initializare();
             /*pozitionam fereastra si ii setam dimensiunile*/
            Dimension marimeEcran=Toolkit.getDefaultToolkit().getScreenSize();
            int pozitie=230;
            setBounds(pozitie,pozitie,400,300);
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
     * ariilor text in care se citesc datele noului material
     */
    void initializare() throws Exception
    {
        /*configurare panou*/
        panou.setMaximumSize(new Dimension(1500,900));
        panou.setPreferredSize(new Dimension(1500,900));
        panou.setLayout(null);
        
        /*configurare etichete*/
        
        lbltipmaterial.setText("Tip material");
        lbltipmaterial.setBounds(new Rectangle(15,10,258,40));
        lbltitlu.setText("Titlu");
        lbltitlu.setBounds(new Rectangle(13,50,258,40));
        lblautor.setText("Autor");
        lblautor.setBounds(new Rectangle(13,90,258,40));
        lblnrex.setText("Nr. Exemplare");
        lblnrex.setBounds(new Rectangle(13,130,258,40));
        
        /*configurare buton*/
        ok.setText("OK");
        ok.setBounds(new Rectangle(120,170,90,28));
        
        /*atasare ascultator*/
        Ascultator asc=new Ascultator();
        ok.addActionListener(asc);
        
        /*configurare arii text*/
        txttipmaterial.setBounds(new Rectangle(130,10,259,25));
        txttitlu.setBounds(new Rectangle(130,50,259,25));
        txtautor.setBounds(new Rectangle(130,90,258,25));
        txtnrex.setBounds(new Rectangle(130,130,100,25));
        
        /*adaugarea componenetlor la panou*/
        panou.add(lbltipmaterial,null);
        panou.add(lbltitlu,null);
        panou.add(lblautor,null);
        panou.add(lblnrex,null);
        panou.add(ok,null);
        panou.add(txttipmaterial,null);
        panou.add(txttitlu,null);
        panou.add(txtautor,null);
        panou.add(txtnrex,null);
        this.getContentPane().add(panou,null);
       }
    
    class Ascultator implements ActionListener
    {
         /** specifica actiunile la apasarea butonului ok
          *  se apeleza constructorul clasei material
          * iar apoi se apeleaza functia se inserare a noului
          * material in baza de date a materialelor*/
         public void actionPerformed(ActionEvent e) 
         {
             if(e.getSource()==ok)
             {
            	Material material=new Material(txttipmaterial.getText(),txttitlu.getText(),
            	                              txtautor.getText(),Integer.parseInt(txtnrex.getText()));
            	material.updateBdMaterial();
            	//fereastra se ascunde
            	setVisible(false);
      }
    }
    }
}
