package InterfataGrafica;

import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.SoftBevelBorder;


public class FereastraMea extends JFrame
{   
    /** Constructorul clasei FereastraMea 
     * @param nume
     * un string in care se va retine titlul ferestrei*/
	public FereastraMea(String nume) 
    {
        super(nume);
        /*pozitionam fereastra si ii setam dimensiunile*/
        Toolkit t=this.getToolkit();
        Dimension marimeEcran=Toolkit.getDefaultToolkit().getScreenSize();
        int pozitie=230;
        setBounds(pozitie,pozitie,marimeEcran.width-2*pozitie,marimeEcran.height/2-30);
        this.getContentPane().setLayout(new BorderLayout());
        /*construim partile componente*/
        creeazaContinut();
        creeazaBaraDeStare1();
        creeazaBaraDeStare2();
        /*specificam modul de reactie al ferestrei la inchidere*/
        this.addWindowListener(new WindowAdapter() {
        public void windowClosing(WindowEvent evt) {
              	System.exit(0);  
        }
    });
        
    }
    
    /**Creeaza continutul ferestrei*/
   public void creeazaContinut()
    {
        JPanel continut=new JPanel();
        this.getContentPane().add(continut,BorderLayout.CENTER);
    }
    
   
    /**Creeaza bara de stare din partea de jos a ferestrei*/
   public void creeazaBaraDeStare1()
    {
        /*panoul care va tine eticheta de stare*/
        JPanel ajutor=new JPanel();
        /*punem in evidenta panoul prin bordura*/
        ajutor.setBorder(new SoftBevelBorder(SoftBevelBorder.RAISED));
        ajutor.setLayout(new BorderLayout());
        /*setam textul etichetei*/
        JLabel stare=new JLabel("Bine a\u0163i venit");
        
        ajutor.add(stare,BorderLayout.SOUTH);
        this.getContentPane().add(ajutor,BorderLayout.SOUTH);       
    }
    
    /**Creeaza bara de stare din partea de sus a ferestrei*/
    public void creeazaBaraDeStare2()
    {
        /*panoul care va tine eticheta de stare*/
        JPanel panou2=new JPanel();
        /*punem in evidenta panoul prin bordura*/
        panou2.setBorder(new SoftBevelBorder(SoftBevelBorder.RAISED));
        panou2.setLayout(new BorderLayout());
        /*setam textul etichetei*/
        JLabel stare2=new JLabel("Apasa\u0163i un buton");
        /*adaugam bara de stare*/
        panou2.add(stare2,BorderLayout.NORTH);
        this.getContentPane().add(panou2,BorderLayout.NORTH);       
    }
}
  
