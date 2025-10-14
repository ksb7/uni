package InterfataGrafica;

    import java.awt.*;
	import java.awt.event.ActionEvent;
	import java.awt.event.ActionListener;
	import java.awt.event.WindowAdapter;
	import java.awt.event.WindowEvent;
    import javax.swing.*;
    import Useri.Utilizator;
	
	public class FerAutentificare extends JDialog  {
		
		/* declararea componentelor fereastrei de dialog */
  	    JPanel panou=new JPanel();
  	    JLabel UserName=new JLabel();
	    JTextField unum=new JTextField();
	    JLabel Password=new JLabel();
	    JTextField pword=new JTextField();
	    JButton ok=new JButton();
	    
	    /**
	     * Constructorul clasei FerAutentificare
	     *@param frame fereastra-parinte
	     *@param title titlul ferestrei de dialog
	     *@param modal indica daca ferestra de dialog este modala sau nu  
	     */
	   
	    public FerAutentificare (Frame frame,String title,boolean modal) 
	    {
	        /*apel la constructorul superclasei*/
	    	super(frame,title,modal);
	        try
	        {
	            /*pozitionam fereastra si ii setam dimensiunile*/
	            Dimension marimeEcran=Toolkit.getDefaultToolkit().getScreenSize();
	            int pozitie=230;
	            setBounds(pozitie,pozitie,400,200);
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
	          
	        }
	        catch(Exception ex)
	        {
	            ex.printStackTrace();
	        }
	    }
	    
	    /*Creeaza componentele ferestrei de dialog*/
	    void initializare() throws Exception
	    {
	        panou.setMaximumSize(new Dimension(1500,900));
	        panou.setPreferredSize(new Dimension(1500,900));
	        panou.setLayout(null);
	        
	        /*creare eticheta*/
	        UserName.setText("UserName");
	        UserName.setBounds(new Rectangle(15,10,258,40));
	        
	        Password.setText("Password");
	        Password.setBounds(new Rectangle(14,50,259,37));
	        
	        /*creare buton*/
	        ok.setText("OK");
	        ok.setBounds(new Rectangle(170,100,90,28));
	        Ascultator asc=new Ascultator();
	        
	        /*atasare ascultator*/
	        ok.addActionListener(asc);
	        
	        /*creare arie text*/
	        unum.setBounds(new Rectangle(130,10,260,25));
	        pword.setBounds(new Rectangle(130,50,160,25));
	         
	        /*urmeaza formatarea butoanelor si a zonelor de text*/
	        panou.add(UserName,null);
	        panou.add(Password,null);
	        panou.add(ok,null);
	        panou.add(pword,null);
	        panou.add(unum,null);   
	        this.getContentPane().add(panou,null);
	    }
	    
	    class Ascultator implements ActionListener
	    {
	        /**
	         *specifica actiunea la apasarea butonului ok
	         */
	        public void actionPerformed(ActionEvent e) 
	        {
	            if(e.getSource()==ok)
	            {
	            	MeniuUtilizator.autentificat=Utilizator.Autentificare(unum.getText(),pword.getText());
	            	setVisible(false);
	            }
	        }
	    }
	}
