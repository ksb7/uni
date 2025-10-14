package InterfataGrafica;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.*;

public class FerCitesteCota extends JDialog 
{
    /* declararea componentelor fereastrei de dialog */
    JPanel panou=new JPanel();
    JLabel lblcota=new JLabel();
    JTextField txtcota=new JTextField();
    JPasswordField parolt= new JPasswordField();
    JButton ok=new JButton();
    
    /**
     * Constructorul clasei FerDialogOptiune
     **@param frame fereastra-parinte
     *@param title titlul ferestrei de dialog
     *@param modal indica daca ferestra de dialog este modala sau nu  
     */
    
    public FerCitesteCota(Frame frame,String title,boolean modal) 
    {
        /*apel la constructorul superclasei*/
         super(frame,title,modal);
        try
        {
            /*pozitionam fereastra si ii setam dimensiunile*/
            Dimension marimeEcran=Toolkit.getDefaultToolkit().getScreenSize();
            int pozitie=230;
            setBounds(pozitie,pozitie,400,150);
            /*construim partile componente*/
            initializare();
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
     *Creeaza componentele ferestrei de dialog
     *prin care se cere utilizatorului sa introduca cota
     *materialului ce sa doreste a fi returnat
     */
    void initializare() throws Exception
    {
        panou.setMaximumSize(new Dimension(1500,900));
        panou.setPreferredSize(new Dimension(1500,900));
        panou.setLayout(null);
        
        /*creare eticheta */
        lblcota.setText("Cota");
        lblcota.setBounds(new Rectangle(15,15,300,40));
        
        /*creare buton*/
        ok.setText("OK");
        ok.setBounds(new Rectangle(90,80,90,28));
        Ascultator asc=new Ascultator();
        /*atasare ascultator*/
        ok.addActionListener(asc);
        
        /*creare arie text*/
        txtcota.setBounds(new Rectangle(100,45,150,25));
        
       /*urmeaza formatarea butoanelor si a zonelor de text*/
        panou.add(lblcota,null);
        panou.add(ok,null);
        panou.add(txtcota,null);
        this.getContentPane().add(panou,null);
       }
    
    class Ascultator implements ActionListener
    {
         /** specifica actiunea la apasarea butonului ok */
        public void actionPerformed(ActionEvent e) 
        {
            if(e.getSource()==ok)
            {
                MeniuBibliotecar.CotaCitit =Integer.parseInt(txtcota.getText());
                /*fereastra se va ascunde*/
                setVisible(false);
            }
        }
    }
}

