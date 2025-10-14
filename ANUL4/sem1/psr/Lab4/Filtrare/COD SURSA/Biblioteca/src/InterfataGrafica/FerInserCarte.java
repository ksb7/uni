package InterfataGrafica;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.*;
import Inventar.*;

public class FerInserCarte extends JDialog{

	/* declararea componentelor fereastrei de dialog */
	JPanel panou=new JPanel();
    JLabel isbn=new JLabel();
    JLabel autor=new JLabel();
    JLabel titlu=new JLabel();
    JLabel editura=new JLabel();
    JLabel cota=new JLabel();
    JTextField isbnt=new JTextField();
    JTextField autort=new JTextField();
    JTextField titlut=new JTextField();
    JTextField editurat=new JTextField();
    JTextField cotat=new JTextField();
    JPasswordField parolt= new JPasswordField();
    JButton ok=new JButton();

    /**
     * Constructorul clasei FerInserCarte
     *@param frame fereastra-parinte
     *@param title titlul ferestrei de dialog
     *@param modal indica daca ferestra de dialog este modala sau nu  
     */
    public FerInserCarte(Frame frame,String title,boolean modal) 
    {
        /*apel la constructorul superclasei*/
        super(frame,title,modal);
        try
        {
            initializare();
             /*pozitionam fereastra si ii setam dimensiunile*/
            Dimension marimeEcran=Toolkit.getDefaultToolkit().getScreenSize();
            int pozitie=200;
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
     * ariilor text in care se citesc datele noii carti
     */
    void initializare() throws Exception
    {
        /*configurare panou*/
        panou.setMaximumSize(new Dimension(1500,900));
        panou.setPreferredSize(new Dimension(1500,900));
        panou.setLayout(null);
        
        /*configurare etichete*/
        cota.setText("Cota");
        cota.setBounds(new Rectangle(15,10,258,40));
        autor.setText("Autor");
        autor.setBounds(new Rectangle(14,50,259,37));
        titlu.setText("Titlu");
        titlu.setBounds(new Rectangle(13,90,258,40));
        editura.setText("Editura");
        editura.setBounds(new Rectangle(13,130,258,40));
        isbn.setText("Isbn");
        isbn.setBounds(new Rectangle(13,170,258,40));
        
        /*configurare buton*/
        ok.setText("OK");
        ok.setBounds(new Rectangle(120,210,90,28));
        
        /*atasare ascultator*/
        Ascultator asc=new Ascultator();
        ok.addActionListener(asc);
        
        /*configurare arii text*/
        cotat.setBounds(new Rectangle(130,10,258,25));
        autort.setBounds(new Rectangle(130,50,258,25));
        titlut.setBounds(new Rectangle(130,90,258,25));
        editurat.setBounds(new Rectangle(130,130,258,25));
        isbnt.setBounds(new Rectangle(130,170,258,25));
        
        /*adaugarea componenetlor la panou*/
        panou.add(isbn,null);
        panou.add(autor,null);
        panou.add(titlu,null);
        panou.add(editura,null);
        panou.add(cota,null);
        panou.add(ok,null);
        panou.add(isbnt,null);
        panou.add(autort,null);
        panou.add(titlut,null);
        panou.add(editurat,null);
        panou.add(cotat,null);
        this.getContentPane().add(panou,null);
       }
    
    class Ascultator implements ActionListener
    {
         /** specifica actiunile la apasarea butonului ok
          * se apeleza constructorul clasei carte
          * iar apoi se apeleaza functia se inserare a noii
          * carti in baza de date a cartilor*/
         public void actionPerformed(ActionEvent e) 
         {
             if(e.getSource()==ok)
             {
            	Carte carte=new Carte(Integer.parseInt(cotat.getText()),Integer.parseInt(isbnt.getText()),
            			              titlut.getText(),autort.getText(),editurat.getText());
            			              //disponibilitatea o sa fie da implicit si calitatea buna
                  carte.updateBdCarte();
                  /*fereastra se va ascunde*/
                 setVisible(false);
      }
    }
    }
}
