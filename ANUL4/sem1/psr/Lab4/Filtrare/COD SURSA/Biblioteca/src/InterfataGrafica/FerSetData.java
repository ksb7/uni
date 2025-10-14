package InterfataGrafica;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.*;
import Tranzactii.Data;
import InterfataGrafica.FerCautaDupaTitlu.Ascultator;

public class FerSetData extends JDialog{
	
	JPanel panou=new JPanel();
    JLabel data=new JLabel();
    JTextField datat=new JTextField();
    JPasswordField parolt= new JPasswordField();
    JButton ok=new JButton();
    /**
     * Constructorul clasei FerCautaRevista
     *@param frame fereastra-parinte
     *@param title titlul ferestrei de dialog
     *@param modal indica daca ferestra de dialog este modala sau nu  
     */
    public FerSetData(Frame frame,String title,boolean modal)
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
     * Creeaza componentele ferestrei de dialog
     *un panou care tine eticheta 'Titlu'
     *si o arie text in care utilizatorul sa introduca revista de cautat
     */
    void initializare() throws Exception
    {
        panou.setMaximumSize(new Dimension(1500,900));
        panou.setPreferredSize(new Dimension(1500,900));
        panou.setLayout(null);
       
        /*creare eticheta titlu*/
        data.setText("Data curenta");
        data.setBounds(new Rectangle(10,10,258,40));
        
        /*creare buton*/
        ok.setText("OK");
        ok.setBounds(new Rectangle(90,50,90,28));
        Ascultator asc=new Ascultator();
        /*atasare ascultator*/
        ok.addActionListener(asc);
        
        /*creare arie text*/
        datat.setBounds(new Rectangle(130,10,200,25));
        
        /*urmeaza formatarea butoanelor si a zonelor de text*/
        panou.add(data,null);
        panou.add(ok,null);
        panou.add(datat,null);
        this.getContentPane().add(panou,null);
       }
    
    class Ascultator implements ActionListener
    {
        /**
         * specifica actiunea la apasarea butonului ok:
         * se preia in variabila TitluRev revista cautata
         * de utilizator 
         */
        public void actionPerformed(ActionEvent e) 
        {
            if(e.getSource()==ok)
            {
            	MeniuBibliotecar.DataCurenta=Data.DataCurenta(datat.getText());
                /*fereastra se va ascunde*/
                setVisible(false);
            }
        }
    }

}
