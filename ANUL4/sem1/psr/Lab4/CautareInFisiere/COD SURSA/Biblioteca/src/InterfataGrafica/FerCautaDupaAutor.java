package InterfataGrafica;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.*;

public class FerCautaDupaAutor extends JDialog{
	 /* declararea componentelor fereastrei de dialog */
    JPanel panou=new JPanel();
    JLabel autor=new JLabel();
    JTextField autort=new JTextField();
    JPasswordField parolt= new JPasswordField();
    JButton ok=new JButton();
    /**
     * Constructorul clasei FerDialogCautaAutor
     *@param frame fereastra-parinte
     *@param title titlul ferestrei de dialog
     *@param modal indica daca ferestra de dialog este modala sau nu  
     */
    public FerCautaDupaAutor (Frame frame,String title,boolean modal) 
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
     *un panou care va tine eticheta 'Autor'
     *si o arie text in care utilizatorul sa introduca numele autorului de cautat
     */
    void initializare() throws Exception
    {
        panou.setMaximumSize(new Dimension(1500,900));
        panou.setPreferredSize(new Dimension(1500,900));
        panou.setLayout(null);
        
        /*creare eticheta autor*/
        autor.setText("Autor");
        autor.setBounds(new Rectangle(14,25,259,37));
        
        /*creare buton*/
        ok.setText("OK");
        ok.setBounds(new Rectangle(120,80,90,28));
        Ascultator asc=new Ascultator();
        
        /*atasare ascultator*/
        ok.addActionListener(asc);
        
        /*creare arie text*/
        autort.setBounds(new Rectangle(130,30,259,25));
        
        /*urmeaza formatarea butoanelor si a zonelor de text*/
        panou.add(autor,null);
        panou.add(ok,null);
        panou.add(autort,null);
            
        this.getContentPane().add(panou,null);
    }
    
    class Ascultator implements ActionListener
    {
        /**
         *specifica actiunea la apasarea butonului ok:
         * se preia in variabila AutorGasit numele autorului introdus
         * de utilizator in fereastra de dialog
         */
        public void actionPerformed(ActionEvent e) 
        {
            
            if(e.getSource()==ok)
            {
            	MeniuUtilizator.AutorGasit=autort.getText();
                /*fereastra se va ascunde*/
                setVisible(false);
            }
        }
    }

}
